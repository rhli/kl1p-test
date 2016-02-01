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

#ifndef KL1P_SUBTRACTIONOPERATORUNITTEST_H
#define KL1P_SUBTRACTIONOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KSubtractionOperatorUnitTest : public Test::Suite
{
public:
    
    KSubtractionOperatorUnitTest();
    virtual ~KSubtractionOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testLeftRightConstructor(); 
    void    testCopyConstructor();

    // Operators tests.
    void    testSubtractionOperator();

    // Methods tests.
    void    testLeft();
    void    testRight();
    void    testApply();
    void    testApplyAdjoint();
    void    testColumn();
    void    testColumnAdjoint();


private:

    KSubtractionOperatorUnitTest(const KSubtractionOperatorUnitTest& test);
    KSubtractionOperatorUnitTest&   operator=(const KSubtractionOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
