// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 Ren� Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "ComplexProxyOperatorUnitTest.h"
#include "../include/ComplexProxyOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/ZeroOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KComplexProxyOperatorUnitTest::KComplexProxyOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KComplexProxyOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KComplexProxyOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KComplexProxyOperatorUnitTest::testOp)
    TEST_ADD(KComplexProxyOperatorUnitTest::testIsZero)
    TEST_ADD(KComplexProxyOperatorUnitTest::testSum)
    TEST_ADD(KComplexProxyOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KComplexProxyOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KComplexProxyOperatorUnitTest::testMean)
    TEST_ADD(KComplexProxyOperatorUnitTest::testVariance)
    TEST_ADD(KComplexProxyOperatorUnitTest::testApply)
    TEST_ADD(KComplexProxyOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KComplexProxyOperatorUnitTest::testColumn)
    TEST_ADD(KComplexProxyOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KComplexProxyOperatorUnitTest::~KComplexProxyOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testOpConstructor()
{
    try
    {
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > matrixOp = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8));

        TComplexProxyOperator<klab::DoubleReal> op(matrixOp);
        TEST_ASSERT(op.op() == matrixOp)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > matrixOp = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8));

        TComplexProxyOperator<klab::DoubleReal> op(matrixOp);
        TEST_ASSERT(op.op() == matrixOp)

        TComplexProxyOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.op() == matrixOp)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testOp()
{
    try
    {
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > matrixOp = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8));

        TComplexProxyOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.op() == 0)

        TComplexProxyOperator<klab::DoubleReal> op(matrixOp);
        TEST_ASSERT(op.op() == matrixOp)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testIsZero()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        TComplexProxyOperator<klab::DoubleReal> op(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix));
        TEST_ASSERT(op.isZero() == false)

        TComplexProxyOperator<klab::DoubleReal> op2(new TZeroOperator<std::complex<klab::DoubleReal> >(4, 8));
        TEST_ASSERT(op2.isZero())
       

        // Limit cases.
        TComplexProxyOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testSum()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TComplexProxyOperator<klab::DoubleReal> op(copMat);
        TEST_ASSERT(klab::Equals(op.sum(), std::norm(copMat->sum())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testNormFrobenius()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TComplexProxyOperator<klab::DoubleReal> op(copMat);
        TEST_ASSERT(klab::Equals(op.normFrobenius(), copMat->normFrobenius().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TComplexProxyOperator<klab::DoubleReal> op(copMat);
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), copMat->squaredNormFrobenius().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testMean()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TComplexProxyOperator<klab::DoubleReal> op(copMat);
        TEST_ASSERT(klab::Equals(op.mean(), std::norm(copMat->mean())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testVariance()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TComplexProxyOperator<klab::DoubleReal> op(copMat);
        TEST_ASSERT(klab::Equals(op.variance(), copMat->variance().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<klab::DoubleReal> rx(n<<1);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<klab::DoubleReal> ry;
        x[0]  = std::complex<klab::DoubleReal>(1.0, 9.0);
        x[1]  = std::complex<klab::DoubleReal>(2.0, 10.0);
        x[2]  = std::complex<klab::DoubleReal>(3.0, 11.0);
        x[3]  = std::complex<klab::DoubleReal>(4.0, 12.0);
        x[4]  = std::complex<klab::DoubleReal>(5.0, 13.0);
        x[5]  = std::complex<klab::DoubleReal>(6.0, 14.0);
        x[6]  = std::complex<klab::DoubleReal>(7.0, 15.0);
        x[7]  = std::complex<klab::DoubleReal>(8.0, 16.0);

        rx[0]  = x[0].real();
        rx[1]  = x[1].real();
        rx[2]  = x[2].real();
        rx[3]  = x[3].real();
        rx[4]  = x[4].real();
        rx[5]  = x[5].real();
        rx[6]  = x[6].real();
        rx[7]  = x[7].real();
        rx[8]  = x[0].imag();
        rx[9]  = x[1].imag();
        rx[10] = x[2].imag();
        rx[11] = x[3].imag();
        rx[12] = x[4].imag();
        rx[13] = x[5].imag();
        rx[14] = x[6].imag();
        rx[15] = x[7].imag();

        y = matrix * x;


        TComplexProxyOperator<klab::DoubleReal> op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix));
        TEST_ASSERT(op.op() != 0)

        op.apply(rx, ry);

        TEST_ASSERT(ry.n_rows == m<<1)
        TEST_ASSERT(klab::Equals(ry[0], y[0].real()))
        TEST_ASSERT(klab::Equals(ry[1], y[1].real()))
        TEST_ASSERT(klab::Equals(ry[2], y[2].real()))
        TEST_ASSERT(klab::Equals(ry[3], y[3].real()))
        TEST_ASSERT(klab::Equals(ry[4], y[0].imag()))
        TEST_ASSERT(klab::Equals(ry[5], y[1].imag()))
        TEST_ASSERT(klab::Equals(ry[6], y[2].imag()))
        TEST_ASSERT(klab::Equals(ry[7], y[3].imag()))


        // Limit cases.
        TComplexProxyOperator<klab::DoubleReal> op0(0);
        try                             {op0.apply(rx, ry); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > xr;
        arma::Col<klab::DoubleReal> rx(n<<1);
        arma::Col<klab::DoubleReal> rxr;
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<klab::DoubleReal> ry;

        x[0]  = std::complex<klab::DoubleReal>(1.0, 9.0);
        x[1]  = std::complex<klab::DoubleReal>(2.0, 10.0);
        x[2]  = std::complex<klab::DoubleReal>(3.0, 11.0);
        x[3]  = std::complex<klab::DoubleReal>(4.0, 12.0);
        x[4]  = std::complex<klab::DoubleReal>(5.0, 13.0);
        x[5]  = std::complex<klab::DoubleReal>(6.0, 14.0);
        x[6]  = std::complex<klab::DoubleReal>(7.0, 15.0);
        x[7]  = std::complex<klab::DoubleReal>(8.0, 16.0);

        rx[0]  = x[0].real();
        rx[1]  = x[1].real();
        rx[2]  = x[2].real();
        rx[3]  = x[3].real();
        rx[4]  = x[4].real();
        rx[5]  = x[5].real();
        rx[6]  = x[6].real();
        rx[7]  = x[7].real();
        rx[8]  = x[0].imag();
        rx[9]  = x[1].imag();
        rx[10] = x[2].imag();
        rx[11] = x[3].imag();
        rx[12] = x[4].imag();
        rx[13] = x[5].imag();
        rx[14] = x[6].imag();
        rx[15] = x[7].imag();

        y  = matrix * x;
        xr = arma::trans(matrix) * y;


        TComplexProxyOperator<klab::DoubleReal> op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix));
        TEST_ASSERT(op.op() != 0)

        op.apply(rx, ry);
        op.applyAdjoint(ry, rxr);

        TEST_ASSERT(rxr.n_rows == n<<1)
        TEST_ASSERT(klab::Equals(rxr[0], xr[0].real()))
        TEST_ASSERT(klab::Equals(rxr[1], xr[1].real()))
        TEST_ASSERT(klab::Equals(rxr[2], xr[2].real()))
        TEST_ASSERT(klab::Equals(rxr[3], xr[3].real()))
        TEST_ASSERT(klab::Equals(rxr[4], xr[4].real()))
        TEST_ASSERT(klab::Equals(rxr[5], xr[5].real()))
        TEST_ASSERT(klab::Equals(rxr[6], xr[6].real()))
        TEST_ASSERT(klab::Equals(rxr[7], xr[7].real()))
        TEST_ASSERT(klab::Equals(rxr[8], xr[0].imag()))
        TEST_ASSERT(klab::Equals(rxr[9], xr[1].imag()))
        TEST_ASSERT(klab::Equals(rxr[10], xr[2].imag()))
        TEST_ASSERT(klab::Equals(rxr[11], xr[3].imag()))
        TEST_ASSERT(klab::Equals(rxr[12], xr[4].imag()))
        TEST_ASSERT(klab::Equals(rxr[13], xr[5].imag()))
        TEST_ASSERT(klab::Equals(rxr[14], xr[6].imag()))
        TEST_ASSERT(klab::Equals(rxr[15], xr[7].imag()))


        // Limit cases.
        TComplexProxyOperator<klab::DoubleReal> op0(0);
        try                             {op0.applyAdjoint(ry, rxr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 16;

        klab::DoubleReal precision = 1e-12; 


        arma::Mat<std::complex<klab::DoubleReal> > matrix(m>>1, n>>1);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);


        TComplexProxyOperator<klab::DoubleReal> op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix));
        TEST_ASSERT(op.op() != 0)

        arma::Mat<klab::DoubleReal> A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.column(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
        {
            for(klab::UInt32 j=0; j<n && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.column(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TComplexProxyOperator<klab::DoubleReal> op0(0);
        try                             {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 16;

        klab::DoubleReal precision = 1e-12; 


        arma::Mat<std::complex<klab::DoubleReal> > matrix(m>>1, n>>1);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);


        TComplexProxyOperator<klab::DoubleReal> op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix));
        TEST_ASSERT(op.op() != 0)

        arma::Mat<klab::DoubleReal> A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.columnAdjoint(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<n && equals; ++i)
        {
            for(klab::UInt32 j=0; j<m && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.columnAdjoint(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TComplexProxyOperator<klab::DoubleReal> op0(0);
        try                             {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
