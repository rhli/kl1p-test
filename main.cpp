// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Test for different CS-algorithms
// Date   : 2016-01-22 09:10:38
// Author : Xiang, Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "MatrixIO.h"
#include "CreatSignal.h"
#include "TestCSAlgorithm.h"

using namespace kl1p;
using std::string;

// Init parameters
klab::UInt32 n = 250;	 // Size of the original signal x0.
klab::UInt32 m = 125;	 // Number of cs-measurements.
klab::UInt32 k = 25;     // Sparsity of the signal x0 (number of non-zero elements).
klab::UInt64 seed = 0;	 // Seed used for random number generation (0 if regenerate random numbers on each launch).

// Init matrix for results
arma::Mat<klab::DoubleReal> runTimeMat(m, k);
arma::Mat<klab::DoubleReal> mseMat(m, k);
arma::Mat<klab::DoubleReal> successMat(m, k);

// Main function
// -------------------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    try
    {
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
        klab::UInt32 i = 20;

        // Loop for test with different parameters
        for(m=125 ; m<=125 ; m++) {
            // Run test functions
            kl1p::testCSAlgorithm(1, i, m, n, k, 0);
            // TODO add result to matrix
        }
        std::cout<<"the current m is: "<<m<<std::endl;
        std::cout<<"the number of round is: "<<i<<std::endl;

        programmTimer.stop();
        programmRuntime = klab::DoubleReal(programmTimer.durationInMilliseconds());
        std::cout<<"the rutime of programm is: "<<programmRuntime<<" ms"<<std::endl;
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
