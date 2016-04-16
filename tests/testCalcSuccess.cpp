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
    A << 1 << 0 << 0 << 1 << 0 << 0 << arma::endr;
    arma::Col<klab::DoubleReal> B;
    B << 1 << 0 << 1 << 0.006 << 0 << 0 << arma::endr;
    klab::UInt32 success;
    success = kl1p::CalcSuccessSupport(A, B);
    std::cout<<success<<std::endl;
    return 0;
}
