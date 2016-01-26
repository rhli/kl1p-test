// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 Ren� Gebel
// --------------------------------------------------------------------------------------
// About  : Main function for tests
// Date   : 2016-01-22 09:10:38
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdlib.h>

#include "Constants.h"
#include "CreatSignal.h"
#include "TestCSAlgorithm.h"
#include "DataProc.h"
#include "MatrixIO.h"

using namespace kl1p;
using std::string;

// Init parameters
klab::UInt32 n = 250;	 // Size of the original signal x0.
klab::UInt32 m = 125;	 // Number of cs-measurements.
klab::UInt32 k = 30;     // Sparsity of the signal x0 (number of non-zero elements).
klab::UInt64 seed = 0;	 // Seed used for random number generation (0 if regenerate random numbers on each launch).
klab::UInt32 flag = 1;   // Flag for using different Algorithms, default: OMP
                         // 1 -> OMP, 2 -> ROMP

// Init struct and matrix for results
resultStruct resultArray;

arma::Mat<klab::DoubleReal> runTimeMeanMat(m, k);
arma::Mat<klab::DoubleReal> mseMeanMat(m, k);
arma::Mat<klab::DoubleReal> successMeanMat(m, k);

arma::Mat<klab::DoubleReal> runTimeStdMat(m, k);
arma::Mat<klab::DoubleReal> mseStdMat(m, k);
arma::Mat<klab::DoubleReal> successStdMat(m, k);

// Main function
// -------------------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    try {
        // Choose algorithm using CLI
        flag = atoi(argv[1]);
        std::cout<<"Using algorithm: "<<algorithms[flag-1]<<std::endl;

        // Get output CSV file names
        RunTimeMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        RunTimeStdMatrixFile += algorithms[flag-1] + CSVEndName;

        MSEMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        MSEStdMatrixFile += algorithms[flag-1] + CSVEndName;

        SuccessMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        SuccessStdMatrixFile += algorithms[flag-1] + CSVEndName;

        // Measure runTime of programm
        klab::DoubleReal programmRuntime = 0;
        klab::KTimer programmTimer;
        programmTimer.start();

        std::cout<<"Start compressed algorithm test..."<<std::endl;

        // Print signal informations
		std::cout<<"=============================="<<std::endl;
		std::cout<<"N="<<n<<" (signal size)"<<std::endl;
		std::cout<<"M="<<m<<"(number of measurements)"<<std::endl;
		std::cout<<"K="<<k<<"(signal sparsity)"<<std::endl;
		std::cout<<"Random Seed="<<klab::KRandom::Instance().seed()<<std::endl;
		std::cout<<"=============================="<<std::endl;

        // number of each round
        klab::UInt32 i = 1;

        // Loop for test with different parameters
        for(klab::UInt32 a=1; a<=k; a++) {
            for(klab::UInt32 b=1; b<=m; b++) {
                // Run test functions
                resultArray = kl1p::testCSAlgorithm(flag, i, b, n, a, 0);

                // Add result in results matrix
                runTimeMeanMat.at(b-1, a-1) = resultArray.run_time_mean;
                runTimeStdMat.at(b-1, a-1) = resultArray.run_time_std;

                mseMeanMat.at(b-1, a-1) = resultArray.mse_mean;
                mseStdMat.at(b-1, a-1) = resultArray.mse_std;

                successMeanMat.at(b-1, a-1) = resultArray.success_mean;
                successStdMat.at(b-1, a-1) = resultArray.success_std;
            }  // end m loop
        }  //end k loop

        // Write results matrix to CSV file
        kl1p::WriteMatrixToCSVFile(runTimeMeanMat, RunTimeMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(runTimeStdMat, RunTimeStdMatrixFile);

        kl1p::WriteMatrixToCSVFile(mseMeanMat, MSEMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(mseStdMat, MSEStdMatrixFile);

        kl1p::WriteMatrixToCSVFile(successMeanMat, SuccessMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(successStdMat, SuccessStdMatrixFile);

        programmTimer.stop();
        programmRuntime = klab::DoubleReal(programmTimer.durationInMilliseconds());
        std::cout<<"Tests finished..."<<std::endl;
        std::cout<<"The runtime of test programm is: "<<programmRuntime<<" ms"<<std::endl;
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

// -------------------------------------------------------------------------------------- //
