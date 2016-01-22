#ifndef DATAPROC_H
#define DATAPROC_H

#include <iostream>
#include <string>
#include <cmath>
#include "MatrixIO.h"
#include "CreatSignal.h"
#include "TestCSAlgorithm.h"

namespace kl1p
{
    klab::DoubleReal CalcMSE(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
    klab::DoubleReal CalcSuccess(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Calculate the MSE between two Vectors(arma::Col)
 *
 * @param vectorA
 * @param vectorB
 *
 * @return
 */
klab::DoubleReal kl1p::CalcMSE(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB)
{
    // MSE = 1/N * sum(N, (x1 - x2)^2)

    klab::DoubleReal mse = 0;

    klab::UInt32 num_element = vectorA.n_rows;

    for(klab::UInt32 i=0; i<num_element; i++) {
        mse = mse+ pow(vectorA.at(i) - vectorB.at(i), 2);
    }

    mse = mse / num_element;

    return mse;
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Calculate the success rate between two vectors
 *
 * @param vectorA
 * @param vectorB
 *
 * @return
 */
klab::DoubleReal kl1p::CalcSuccess(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB)
{
    klab::DoubleReal success = 0;

    klab::UInt32 num_element = vectorA.n_rows;

    for(klab::UInt32 i=0; i<num_element; i++) {
        if(vectorA.at(i) == 0 && vectorB.at(i) == 0)
            success += 1;
        if(vectorA.at(i) != 0 && vectorB.at(i) != 0)
            success += 1;
    }

    success = success / num_element;

    return success;
}

// ---------------------------------------------------------------------------------------------------- //

#endif /* DATAPROC_H */