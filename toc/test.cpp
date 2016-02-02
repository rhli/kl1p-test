// --------------------------------------------------------------------------------------
// About  : Tests for libs and units
// Date   : 2016-02-01 13:52:13
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <armadillo>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Constants.h"
#include "CreatSignal.h"
#include "TestCSAlgorithm.h"
#include "DataProc.h"
#include "MatrixIO.h"

int main(int argc, const char *argv[])
{
    arma::Col<klab::DoubleReal> vec1(100);
    vec1.randn();
    vec1.save("./random_vector.csv", arma::csv_ascii);
    return 0;
}
