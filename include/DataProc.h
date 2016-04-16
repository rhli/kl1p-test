// --------------------------------------------------------------------------------------
// About  : Functions to processing simulation results
// Date   : 2016-01-19
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
    klab::UInt32 CalcSuccessSupport(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB);
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
 *        success = 1 if the abs(vectorA(i) - vectorB(i)) <= epsilon for all i in the vector
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
        if( std::abs( vectorA.at(i) - vectorB.at(i) ) > epsilon )
            success = 0;  // when there is a significant difference
            break;
    }

    return success;
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief return success = 1 if supp(vectorA) is a subset of supp(vectorB)
 *        supp(vector) ist the positions of non-zero element in the vector
 *        due to the accuracy of computing, the value should be worked with tolerance
 *
 * @param vectorA
 * @param vectorB
 *
 * @return
 */
klab::UInt32 kl1p::CalcSuccessSupport(arma::Col<klab::DoubleReal> vectorA, arma::Col<klab::DoubleReal> vectorB)
{
    klab::UInt32 success = 1;  // init with success = 1
    klab::UInt32 num_element_A = vectorA.n_rows;
    klab::UInt32 num_element_B = vectorB.n_rows;
    if (num_element_A != num_element_B) {
        std::cout<<"two vectors should have same length"<<std::endl;
        exit(1);
    }

    // loop for all elements
    for (klab::UInt32 i = 0; i < num_element_A; ++i) {
        // if element with index i is non-zero
        if(std::abs(vectorA(i) - 0) >= epsilon) {
            if(std::abs(vectorB(i) - 0) <= epsilon) {
                success = 0;  // if vectorB(i) is zero at the same position
            }
        }
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
