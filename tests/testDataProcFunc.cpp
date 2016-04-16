// --------------------------------------------------------------------------------------
// About  : Test CalcSuccessSupport function
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <iostream>

#include <KL1pInclude.h>
#include "DataProc.h"

int main(int argc, char *argv[])
{
    arma::Col<klab::DoubleReal> A;
    A << 1 << 0 << 1 << 0.5 << 1 << 0 << arma::endr;
    arma::Col<klab::DoubleReal> B;
    B << 1 << 0 << 1 << 0 << 0 << 0 << arma::endr;

    // test mse
    klab::DoubleReal mse;
    mse = kl1p::CalcMSE(A, B);
    std::cout<<mse<<std::endl;

    // test success
    // -- abs difference ---
    klab::UInt32 success;
    success = kl1p::CalcSuccess(A, B);
    std::cout<<"abs diff: "<<success<<std::endl;

    // --- support ---
    success = kl1p::CalcSuccessSupport(A, B);
    std::cout<<"test for support: "<<success<<std::endl;

    // --- snr ---
    klab::DoubleReal snr;
    snr = kl1p::CalcDiscreteSNR(A, B);
    std::cout<<"SNR:" <<snr<<std::endl;

    return 0;
}
