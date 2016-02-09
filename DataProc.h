// --------------------------------------------------------------------------------------
// About  : Functions to processing simulation results
// Date   : 2016-01-19 10:34:23
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#ifndef DATAPROC_H
#define DATAPROC_H

#include <KL1pInclude.h>
#include "Constants.h"

namespace kl1p
{
    klab::DoubleReal CalcMSE(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
    klab::DoubleReal CalcSuccess(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
    klab::DoubleReal CalcDiscreteSignalPower(arma::Col<klab::DoubleReal> vector);
    klab::DoubleReal CalcDiscreteSNR(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
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
 * @brief Calculate the success rate between two vectors(using a tolerance as epsilon)
 *
 * @param vectorA
 * @param vectorB
 *
 * @return
 */
klab::DoubleReal kl1p::CalcSuccess(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB)
{
    // init success = 1
    klab::DoubleReal success = 1;
    klab::UInt32 num_element = vectorA.n_rows;

    // due to the accuracy of computing, the value should be worked with tolerance(here as epsilon)
    for(klab::UInt32 i=0; i<num_element; i++) {
        if( abs( vectorA.at(i) - vectorB.at(i) ) > epsilon )
            success = 0;  // when there is a significant difference
    }

    return success;
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Calculate the power of a discrete vector signal
 *
 * @param vector
 *
 * @return
 */
klab::DoubleReal kl1p::CalcDiscreteSignalPower(arma::Col<klab::DoubleReal> vector)
{
    klab::DoubleReal power = 0.0;
    klab::DoubleReal energie = 0.0;

    klab::UInt32 num_element = vector.n_rows;

    for(klab::UInt32 i=0; i<num_element; i++) {
        energie += vector.at(i) * vector.at(i);
    }

    power = energie / num_element;
    return power;
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Calculate the SNR of two discrete signals
 *
 * @param vectorA
 * @param vectorB
 *
 * @return
 */
klab::DoubleReal kl1p::CalcDiscreteSNR(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB)
{
    klab::UInt32 num_elementA = vectorA.n_rows;
    klab::UInt32 num_elementB = vectorB.n_rows;

    // hier len(vectorA) should be same with len(vectorB)
    if(num_elementA != num_elementB) {
        std::cout<<"the length of two vectors is different!"<<std::endl;
        return 1;
    }

    else {
        klab::DoubleReal snr = 0.0;
        klab::DoubleReal energieA = 0.0;
        klab::DoubleReal energieB = 0.0;

        for(klab::UInt32 i=0; i<num_elementA; i++) {
            energieA += vectorA.at(i) * vectorA.at(i);
            energieB += vectorB.at(i) * vectorB.at(i);
        }
        snr = energieA / energieB;
        snr = 10 * log10(snr);  // convert snr to dB
        return snr;
    }
}

// ---------------------------------------------------------------------------------------------------- //

#endif /* DATAPROC_H */
