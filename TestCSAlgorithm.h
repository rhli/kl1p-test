// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Functions for testing different CS-algorithms
// Date   : 2016-01-19 10:34:23
// Author : Xiang, Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#ifndef TESTCSALGORITHM_H
#define TESTCSALGORITHM_H

#include <KL1pInclude.h>
#include "CreatSignal.h"
#include "MatrixIO.h"

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
    resultStruct testCSAlgorithm(klab::UInt32 flag, klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed);
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
resultStruct kl1p::testCSAlgorithm(klab::UInt32 flag, klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed)
{

    // Initialize random seed if needed.
    if(seed > 0)
        klab::KRandom::Instance().setSeed(seed);

    // Init struct for results
    resultStruct resultArray;

    // Init vector for saving temp result
    arma::Col<klab::DoubleReal> runTimeTemp(i);
    arma::Col<klab::DoubleReal> mseTemp(i);
    arma::Col<klab::DoubleReal> successTemp(i);

    // Round Loop: j as round-index
    for(klab::UInt32 j=0 ; j<i ; j++) {
        // Generate original signals
        arma::Col<klab::DoubleReal> x0;
        // Create original gauss random signal with mean=0, sigma=1 and sparsity=k, length=n
        kl1p::CreateGaussianSignal(n, k, 0.0, 1.0, x0);
        // Save signal to a CSV file
        kl1p::WriteColToCSVFile(x0, OriginalSignalFile);

        // Get sensing matrix from CSV file
        // --------------------------------------------------------------------------------

        // 1. resize the original sensingMatrix
        // get orginal sensing matrix
        arma::Mat<klab::DoubleReal> originalSenMatrix;
        originalSenMatrix.load(orginalMatrixFile, arma::csv_ascii);
        // resize matrix and save as resized matrix
        originalSenMatrix.resize(m, n);
        originalSenMatrix.save(resizedMatrixFile, arma::csv_ascii);

        // 2. load matrix using TMatrixFromCSV(rows, cols, resizedMatrixFile)
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > A = new kl1p::TMatrixFromCSV<klab::DoubleReal>(m, n, resizedMatrixFile);
        // --------------------------------------------------------------------------------

        // Perform CS-measurements of size m.
        arma::Col<klab::DoubleReal> y;      // y is the result after compressed sensing
        A->apply(x0, y);

        klab::DoubleReal tolerance = 1e-6;	// Tolerance of the solution. Default: 1e-6
        arma::Col<klab::DoubleReal> x;		// the solution of the reconstruction.

        klab::KTimer timer;                 // Timer to get run time

        // Use flag to run different Algorithms
        switch(flag) {
            case 1: {
                // Apply OMP-Algorithm
                // --------------------------------------------------------------------------------
                std::cout<<"------------------------------"<<std::endl;
                std::cout<<"[OMP] start..."<<std::endl;
                timer.start();
                // Create a Solver to get the result of OMP(giving tolerance)
                kl1p::TOMPSolver<klab::DoubleReal> omp(tolerance);
                omp.solve(y, A, k, x);
                timer.stop();
                // Print results
                std::cout<<"[OMP] Done - SNR="<<std::setprecision(5)<<klab::SNR(x, x0)<<" - "
                          <<"Time="<<klab::UInt32(timer.durationInMilliseconds())<<"ms"<<" - "
                          <<"Iterations="<<omp.iterations()<<std::endl;
                std::cout<<"------------------------------"<<std::endl;
                kl1p::WriteColToCSVFile(x, OMPSignalFile);

                // Add result to Vector
                runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
                break;
            }
        }  // End switch
    }  // End round loop

    // Calc Mean and Std
    klab::DoubleReal runTimeMean = arma::mean(runTimeTemp);
    klab::DoubleReal runTimeStd = arma::stddev(runTimeTemp);

    std::cout<<"the mean of run time is:" <<runTimeMean<<std::endl;

    // Save results in Struct and return
    resultArray.run_time_mean = runTimeMean;
    resultArray.run_time_std = runTimeStd;

    return resultArray;
}

#endif /* TESTCSALGORITHM_H */
