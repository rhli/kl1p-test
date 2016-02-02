// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Functions for testing different CS-algorithms
// Date   : 2016-01-19 10:34:23
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#ifndef TESTCSALGORITHM_H
#define TESTCSALGORITHM_H

#include <KL1pInclude.h>

#include "Constants.h"
#include "CreatSignal.h"
#include "MatrixIO.h"
#include "DataProc.h"

// Init struct to return results
struct resultStruct {
    klab::DoubleReal run_time_mean;
    klab::DoubleReal run_time_std;
    klab::DoubleReal mse_mean;
    klab::DoubleReal mse_std;
    klab::DoubleReal success_mean;
    klab::DoubleReal success_std;
};

namespace kl1p
{
    resultStruct testCSAlgorithm(klab::UInt32 flag, klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed, klab::DoubleReal snr);
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Test different CS Algorithms using different parameters
 *
 * @param flag
 * @param i
 * @param m
 * @param n
 * @param k
 * @param seed
 */
resultStruct kl1p::testCSAlgorithm(klab::UInt32 flag, klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed, klab::DoubleReal snr)
{

    // --- Init variables ---
    // ------------------------------------------
    // random seed if needed.
    if(seed > 0)
        klab::KRandom::Instance().setSeed(seed);

    // struct for return results
    resultStruct resultArray;

    // vector for saving temp result
    arma::Col<klab::DoubleReal> runTimeTemp(i);
    arma::Col<klab::DoubleReal> mseTemp(i);
    arma::Col<klab::DoubleReal> successTemp(i);

    // snr and correct factor
    klab::DoubleReal snr_before, snr_after;
    klab::DoubleReal k_factor;
    // ------------------------------------------

    // Round Loop: j as round-index
    for(klab::UInt32 j=0 ; j<i ; j++) {
        // Generate original signals
        arma::Col<klab::DoubleReal> x0;
        // Create original gauss random signal with mean=0, sigma=1 and sparsity=k, length=n
        kl1p::CreateGaussianSignal(n, k, 0.0, 1.0, x0);

        // Get sensing matrix from CSV file
        // --------------------------------------------------------------------------------
        // 1. resize the original sensingMatrix
        // get orginal sensing matrix
        arma::Mat<klab::DoubleReal> originalSenMatrix;
        originalSenMatrix.load(sensingMatrixOriginalFile, arma::csv_ascii);
        // resize matrix and save as resized matrix
        originalSenMatrix.resize(m, n);
        originalSenMatrix.save(sensingMatrixResizedFile, arma::csv_ascii);
        // 2. load matrix using TMatrixFromCSV(rows, cols, resizedMatrixFile)
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > A = new kl1p::TMatrixFromCSV<klab::DoubleReal>(m, n, sensingMatrixResizedFile);
        // --------------------------------------------------------------------------------

        // Perform CS-measurements of size m.
        arma::Col<klab::DoubleReal> y;      // y is the result after compressed sensing
        A->apply(x0, y);

        // Add noise(AWGN) -> using normal random number generator in lib armadillo
        if(snr != 0) {
            // Generate vector with normal distribution
            arma::Col<klab::DoubleReal> noise(y.n_rows);
            noise.randn();  // normal distribution with mean = 0 and sigma = 1

            // Correct noise to given SNR mit k_factor
            snr_before = kl1p::CalcDiscreteSNR(y, noise);  // calc the snr before correction
            // std::cout<<"SNR before: "<<snr_before<<std::endl;

            k_factor = sqrt(pow(10, (snr_before - snr) / 10.0));

            for(klab::UInt32 i=0; i<noise.n_rows; i++) {
                noise.at(i) = noise.at(i) * k_factor;
            }
            // Test for SNR correction
            // snr_after = kl1p::CalcDiscreteSNR(y, noise);
            // std::cout<<"SNR after: "<<snr_after<<std::endl;

        }

        klab::DoubleReal tolerance = 1e-6;	// Tolerance of the solution. Default: 1e-6
        arma::Col<klab::DoubleReal> x;		// the solution of the reconstruction.

        klab::KTimer timer;                 // Timer to get run time

        // Use flag to run different Algorithms
        switch(flag) {

            // 1. Apply OMP
            case 1: {
                try {
                    timer.start();
                    // Create a Solver to get the result of OMP(giving tolerance)
                    kl1p::TOMPSolver<klab::DoubleReal> omp(tolerance);
                    omp.solve(y, A, k, x);
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                // handle with exception when problem by solving matrix
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

            // 2. Apply ROMP
            case 2: {
                try {
                    timer.start();
                    // Create a Solver to get the result of ROMP(giving tolerance)
                    kl1p::TROMPSolver<klab::DoubleReal> romp(tolerance);
                    romp.solve(y, A, k, x);
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

            // 3. Apply CoSaMP
            case 3: {
                try {
                    timer.start();
                    kl1p::TCoSaMPSolver<klab::DoubleReal> cosamp(tolerance);
                    cosamp.solve(y, A, k, x);
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

            // 4. Apply Subspace-Pursuit
            case 4: {
                try {
                     timer.start();
                     kl1p::TSubspacePursuitSolver<klab::DoubleReal> sp(tolerance);
                     sp.solve(y, A, k, x);
                     timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

            // 5. Apply SL0
            case 5: {
                try {
                    timer.start();
                    kl1p::TSL0Solver<klab::DoubleReal> sl0(tolerance);
                    sl0.solve(y, A, x);
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

            // 6. Apply AMP
            case 6: {
                try {
                    timer.start();
                    kl1p::TAMPSolver<klab::DoubleReal> amp(tolerance);
                    amp.solve(y, A, x);
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;
                    runTimeTemp[j] = 0;
                    mseTemp[j] = 1;
                    successTemp[j] = 0;
                    break;
                }
            }

            // 7. Apply EMBP
            case 7: {
                try {
                    timer.start();
                    kl1p::TEMBPSolver<klab::DoubleReal> embp(tolerance);
                    embp.enableHomogeneous(true);
                    embp.solve(y, A, k, x);
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
                catch(klab::KZeroNormLeastSquareException) {
                    std::cout<<"KZeroNormLeastSquareException catched..."<<std::endl;  // print exception
                    timer.stop();
                    // Add result to temp vector
                    runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                    mseTemp[j] = kl1p::CalcMSE(x, x0);
                    successTemp[j] = kl1p::CalcSuccess(x, x0);
                    break;
                }
            }

        }  // End switch
    }  // End round loop

    // Calc Mean and Std
    // ----------------------------------------------------------------------------------
    // run time
    klab::DoubleReal runTimeMean = arma::mean(runTimeTemp);
    klab::DoubleReal runTimeStd = arma::stddev(runTimeTemp);

    // mse
    klab::DoubleReal mseMean = arma::mean(mseTemp);
    klab::DoubleReal mseStd = arma::stddev(mseTemp);

    // success
    klab::DoubleReal successMean = arma::mean(successTemp);
    klab::DoubleReal successStd = arma::stddev(successTemp);
    // ----------------------------------------------------------------------------------

    // Save results in Struct and return
    resultArray.run_time_mean = runTimeMean;
    resultArray.run_time_std = runTimeStd;
    resultArray.mse_mean = mseMean;
    resultArray.mse_std = mseStd;
    resultArray.success_mean = successMean;
    resultArray.success_std = successStd;

    return resultArray;
}

#endif /* TESTCSALGORITHM_H */
