// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 Ren� Gebel
//
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY of fitness for any purpose.
//
// This library is free software; You can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License (LGPL)
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "../CompressedSensingExample.h"

using namespace kl1p;

// ---------------------------------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    try
    {
		std::cout<<"Start compressed algorithm test..."<<std::endl;

        // Init parameters
		klab::UInt32 n = 250;					 // Size of the original signal x0.
		klab::DoubleReal alpha = 0.5;			 // Ratio of the cs-measurements.
		klab::DoubleReal rho = 0.1;				 // Ratio of the sparsity of the signal x0. here 10%
		klab::UInt32 m = klab::UInt32(alpha*n);	 // Number of cs-measurements.
		klab::UInt32 k = klab::UInt32(rho*n);	 // Sparsity of the signal x0 (number of non-zero elements).
		klab::UInt64 seed = 0;					 // Seed used for random number generation (0 if regenerate random numbers on each launch).
		bool bWrite = true;					     // Write signals to files

		// Initialize random seed if needed.
		if(seed > 0)
			klab::KRandom::Instance().setSeed(seed);

		std::cout<<"=============================="<<std::endl;
		std::cout<<"N="<<n<<" (signal size)"<<std::endl;
		std::cout<<"M="<<m<<"="<<std::setprecision(5)<<(alpha*100.0)<<"% (number of measurements)"<<std::endl;
		std::cout<<"K="<<k<<"="<<std::setprecision(5)<<(rho*100.0)<<"% (signal sparsity)"<<std::endl;
		std::cout<<"Random Seed="<<klab::KRandom::Instance().seed()<<std::endl;
		std::cout<<"=============================="<<std::endl;

        // Generate original signals
		arma::Col<klab::DoubleReal> x0;
        // Create original signal with mean=0 and sigma=1
		kl1p::CreateGaussianSignal(n, k, 0.0, 1.0, x0);

        if(bWrite)
            kl1p::WriteToCSVFile(x0, "/home/steve/src/cpp_src/kl1p_dev/csv_matrix/OriginalSignal.csv");

        // TODO: Get sensing matrix from csv file

		// Create random gaussian i.i.d matrix A of size (m,n).
        // Create Solver-Matrix
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > A = new kl1p::TNormalRandomMatrixOperator<klab::DoubleReal>(m, n, 0.0, 1.0);
		// A  = new kl1p::TScalingOperator<klab::DoubleReal>(A, 1.0/klab::Sqrt(klab::DoubleReal(m)));	// Pseudo-normalization of the matrix (required for AMP and EMBP solvers).

		// Perform CS-measurements of size m.
		arma::Col<klab::DoubleReal> y;  // y is the result after compressed sensing
		A->apply(x0, y);

		klab::DoubleReal tolerance = 1e-5;	// Tolerance of the solution.
		arma::Col<klab::DoubleReal> x;		// Will contain the solution of the reconstruction.

		klab::KTimer timer;

        /*
         * y = Ax ist the sensing equation
         * omp.solve(y, A, k, x)
         *   k: sparsity of the original signal
         *   x: the solution of reconstruction using omp
         * */

		// compute OMP.
		std::cout<<"------------------------------"<<std::endl;
		std::cout<<"[OMP] start."<<std::endl;
		timer.start();  // use timer to get run-time
        // create a Solver to get the result of OMP
		kl1p::TOMPSolver<klab::DoubleReal> omp(tolerance);
		omp.solve(y, A, k, x);
		timer.stop();
		std::cout<<"[OMP] Done - SNR="<<std::setprecision(5)<<klab::SNR(x, x0)<<" - "
			      <<"Time="<<klab::UInt32(timer.durationInMilliseconds())<<"ms"<<" - "
				  <<"Iterations="<<omp.iterations()<<std::endl;
		std::cout<<"------------------------------"<<std::endl;
    }

	catch(klab::KException& e)
	{
		std::cout<<"ERROR! KLab exception : "<<klab::FormatExceptionToString(e)<<std::endl;
	}
	catch(std::exception& e)
	{
		std::cout<<"ERROR! Standard exception : "<<klab::FormatExceptionToString(e)<<std::endl;
	}
	catch(...)
	{
		std::cout<<"ERROR! Unknown exception !"<<std::endl;
	}
	return 0;
}

// ---------------------------------------------------------------------------------------------------- //

