// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// Modified : Xiang, Zuo
// Date     : 2016-01-19 10:34:23
// About    : Using sensing matrix from a CSV file and test CS-algorithms
// --------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "../CompressedSensingExample.h"

using namespace kl1p;
using std::string;


void testCSAlgorithm(klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed);

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
		std::cout<<"Start compressed algorithm test..."<<std::endl;

        // Init parameters
		klab::UInt32 n = 250;	 // Size of the original signal x0.
		klab::UInt32 m = 125;	 // Number of cs-measurements.
		klab::UInt32 k = 10;     // Sparsity of the signal x0 (number of non-zero elements).
		klab::UInt64 seed = 0;	 // Seed used for random number generation (0 if regenerate random numbers on each launch).

        // Print signal informations
		std::cout<<"=============================="<<std::endl;
		std::cout<<"N="<<n<<" (signal size)"<<std::endl;
		std::cout<<"M="<<m<<"(number of measurements)"<<std::endl;
		std::cout<<"K="<<k<<"(signal sparsity)"<<std::endl;
		std::cout<<"Random Seed="<<klab::KRandom::Instance().seed()<<std::endl;
		std::cout<<"=============================="<<std::endl;

        // Loop for test with different parameters
        for(m=1 ; m<=125 ; m++) {
            // Run test functions
            testCSAlgorithm(m, n, k, 0);
        }

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
void testCSAlgorithm(klab::UInt32 m, klab::UInt32 n, klab::UInt32 k, klab::UInt64 seed)
{
    // Initialize strings
    string OriginalSignalFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/OriginalSignal.csv");
    string OMPSignalFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/OMP-Signal.csv");
    string orginalMatrixFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/sensingMatrixOriginal.csv");
    string resizedMatrixFile("/home/steve/src/cpp_src/kl1p_dev/csv_matrix/sensingMatrixResized.csv");

    // Initialize random seed if needed.
    if(seed > 0)
    	klab::KRandom::Instance().setSeed(seed);

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
}
