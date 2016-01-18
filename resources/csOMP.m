%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%	diploma thesis Carsten Herrmann - simulation environment
%	Copyright (C) 2013 by Carsten Herrmann
%
%	OMP CS solver (Orthogonal Matching Pursuit)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [X, S, info] = csOMP(Y, A, sparsity, settings = struct())

	% set default control parameters
	control.residualNorm		= 2;
	control.residualThreshold	= 1e-9 * sqrt(columns(A));
	control.rowNorm 			= 2;
	control.rowThreshold		= 1e-9;
	control.maxRelaxation		= 1;
	control.getTimeFunction		= @() 0;

	% merge with explicit settings
	control = mergeConfigData(control, settings);
	if (isempty(control))
		error('settings data is invalid (not a struct?)');
		return;
	endif

	% init runtime data
	maxNumIterations = sparsity * control.maxRelaxation;
	AH = A';	% could be precomputed in case of a static system
  	R = Y;
  	L = [];
  	AL = [];

	% main loop
	startTime = control.getTimeFunction();
  	for i = 1 : maxNumIterations

		% select the column of A which has highest correlation to residual
		% notice: by using AH (instead of R' * A) we avoid the need of transposing R on every iteration
		C = AH * R;
		[t, k] = max(norm(C, control.rowNorm, 'rows'));

		% theoretically, R is orthogonal to already selected columns,
		% so meeting the following condition implies R = 0.
		% in practice, R could have some small value (-> limited machine precision)
		% both cases mean that we are done.
		% typical example: true solution is < maxNumIterations sparse.
		% notice: if we wouldn't stop here, the following calculations could get stuck
		if (ismember(k, L))
		  break;
		endif

		% extend support
		L = [L k];
		AL = [AL A(:,k)];

		% calculate solution, update residual
		% notice: kind of solving is unimportant as long as the solution is unique
		XL = AL \ Y;
		R = Y - AL * XL;

		% if residual threshold reached: done
		if (max(norm(R, control.residualNorm, 'columns')) <= control.residualThreshold)
			break;
		endif

  	endfor
	info.time = control.getTimeFunction() - startTime;

	% assemble full solution
	X = zeros(columns(A), columns(Y));
	S = [];
	for i = 1 : length(L)
		if (norm(XL(i,:), control.rowNorm) >= control.rowThreshold)
			X(L(i),:) = XL(i,:);
			S = [S L(i)];
		endif
	endfor

	% complete info structure
	if (nargout >= 3)

		info.R = R;
		info.error = 0;
		info.warnings = {};
		info.danger = false;

		if (length(S) > sparsity)
			r = rows(info.warnings) + 1;
			info.warnings{r,1} = 1;
			info.warnings{r,2} = 'length(S) > sparsity';
			info.danger = true;
		endif

		if (norm(R, control.residualNorm) > control.residualThreshold)
			r = rows(info.warnings) + 1;
			info.warnings{r,1} = 2;
			info.warnings{r,2} = 'residual > threshold';
			info.danger = true;
		endif

	endif

endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
