// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Test for different CS-algorithms
// Date   : 2016-01-19 10:34:23
// Author : Xiang, Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <time.h>
#include "CompressedSensingExample.h"

using namespace kl1p;
using std::string;

/* Global Variables*/
/* ------------------------------------------------------------------------------------------------ */
// File locations
string OriginalSignalFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/OriginalSignal.csv");
string OMPSignalFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/OMP-Signal.csv");
string orginalMatrixFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/sensingMatrixOriginal.csv");
string resizedMatrixFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/sensingMatrixResized.csv");
string runTimeMatrixFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/runTime.csv");

// Init parameters
klab::UInt32 n = 250;	 // Size of the original signal x0.
klab::UInt32 m = 125;	 // Number of cs-measurements.
klab::UInt32 k = 25;     // Sparsity of the signal x0 (number of non-zero elements).
klab::UInt64 seed = 0;	 // Seed used for random number generation (0 if regenerate random numbers on each launch).

// Matrix of results
arma::Mat<klab::DoubleReal> runTimeMat(m, k);
arma::Mat<klab::DoubleReal> mseMat(m, k);
arma::Mat<klab::DoubleReal> successMat(m, k);

/* ------------------------------------------------------------------------------------------------ */

void testCSAlgorithm(klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed);
void writeMatrixToCSVFile(arma::mat m, string file_name);

/**
 * @brief main
 *
 * @param argc
 * @param argv[]
 *
 * @return
 */
int main(int argc, char* argv[])
{
    try
    {
        // measure runTime of programm
        clock_t tStart = clock();

        std::cout<<"Start compressed algorithm test..."<<std::endl;

        // Print signal informations
		std::cout<<"=============================="<<std::endl;
		std::cout<<"N="<<n<<" (signal size)"<<std::endl;
		std::cout<<"M="<<m<<"(number of measurements)"<<std::endl;
		std::cout<<"K="<<k<<"(signal sparsity)"<<std::endl;
		std::cout<<"Random Seed="<<klab::KRandom::Instance().seed()<<std::endl;
		std::cout<<"=============================="<<std::endl;

        // number of each round
        klab::UInt32 i = 30;

        // Loop for test with different parameters
        for(m=125 ; m<=125 ; m++) {
            // Run test functions
            testCSAlgorithm(i, m, n, k, 0);
            // TODO: Calc Statistics
        }
        std::cout<<"the current m is: "<<m<<std::endl;
        std::cout<<"the number of round is: "<<i<<std::endl;
        klab::DoubleReal runTimeProgramm =klab::DoubleReal((clock() - tStart)/CLOCKS_PER_SEC);
        std::cout<<"the run time of the programm is: "<<runTimeProgramm<<"s"<<std::endl;
    }

    // Catch Exception
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

/**
 * @brief testCSAlgorithm
 * Test CS Algorithm using different parameters
 *
 * @param m
 * @param n
 * @param k
 */
void testCSAlgorithm(klab::UInt32 i, klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed)
{

    // Initialize random seed if needed.
    if(seed > 0)
    	klab::KRandom::Instance().setSeed(seed);

    // Init vector for saving temp result
    arma::Col<klab::DoubleReal> runTimeTemp(i);
    arma::Col<klab::DoubleReal> mseTemp(i);
    arma::Col<klab::DoubleReal> successTemp(i);

    // Round Loop: j as round-index
    for(klab::UInt32 j=0 ; j<i ; j++) {
        // Generate original signals
	    arma::Col<klab::DoubleReal> x0;
        // Create original gauss random signal with mean=0, sigma=1 and sparsity=k
	    kl1p::CreateGaussianSignal(n, k, 0.0, 1.0, x0);
        // Save signal to a CSV file
        kl1p::WriteToCSVFile(x0, OriginalSignalFile);

        // Get sensing matrix from CSV file
        // --------------------------------------------------------------------------------
        // 1. resize the original sensingMatrix
        std::cout<<"the orginalMatrixFile is:"<<orginalMatrixFile<<std::endl;
        std::cout<<"the resizedMatrixFile is:"<<resizedMatrixFile<<std::endl;
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

        /*
         * y = Ax ist the sensing equation
         * omp.solve(y, A, k, x)
         *   k: sparsity of the original signal
         *   x: the solution of reconstruction using omp
         * */

	    // Apply OMP-Algorithm
        // --------------------------------------------------------------------------------
	    std::cout<<"------------------------------"<<std::endl;
	    std::cout<<"[OMP] start..."<<std::endl;
	    timer.start();
        // Create a Solver to get the result of OMP(giving tolerance)
	    kl1p::TOMPSolver<klab::DoubleReal> omp(tolerance);
        /*
         * function omp.solve()
         * */
	    omp.solve(y, A, k, x);
	    timer.stop();
        // Print results
	    std::cout<<"[OMP] Done - SNR="<<std::setprecision(5)<<klab::SNR(x, x0)<<" - "
	    	      <<"Time="<<klab::UInt32(timer.durationInMilliseconds())<<"ms"<<" - "
	    		  <<"Iterations="<<omp.iterations()<<std::endl;
	    std::cout<<"------------------------------"<<std::endl;
        kl1p::WriteToCSVFile(x, OMPSignalFile);

        // Add result to Vector
        runTimeTemp[j] = klab::DoubleReal(timer.durationInMilliseconds());
    }

    // Calc Mean and Std
    klab::DoubleReal runTimeMean = arma::mean(runTimeTemp);
    std::cout<<"the mean of run time is:" <<runTimeMean<<std::endl;
    kl1p::WriteToCSVFile(runTimeTemp, runTimeMatrixFile);
}


/**
 * @brief Write a arma::Mat to a CSV File
 *
 * @param writeMatrix
 * @param file_name
 */
void writeMatrixToCSVFile(arma::mat writeMatrix, string file_name)
{
    // get of stream
	std::ofstream of(file_name.c_str(), std::ofstream::out | std::ofstream::trunc);

	if(of.is_open())
	{
		for(klab::UInt32 i=0; i<writeMatrix.n_rows; i++) {
            for(klab::UInt32 j=0; j<writeMatrix.n_cols; j++) {
                if(j == (writeMatrix.n_cols - 1))
                    of<<writeMatrix.at(i, j);
                else
                    of<<writeMatrix.at(i, j)<<",";
            }
            of<<std::endl;
        }

		of.close();
	}
	else
	{
		std::cout<<"ERROR! Unable to open file \""<<file_name<<"\" !"<<std::endl;
	}
}
