#ifndef CONSTANTS_H
#define CONSTANTS_H
// --------------------------------------------------------------------------------------
// About  : Definitions of Constants
// Date   : 2016-01-25 14:07:20
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------

/* Initialize Constants */

#include <iostream>
#include <string>
#include <KL1pInclude.h>

// Array of algorithms
string algorithms [] = {"OMP", "ROMP"};

// File path for sensing matrix and statistish results

// sensing matrix
string sensingMatrixOriginalFile("./csv_matrix/sensingMatrixOriginal.csv");
string sensingMatrixResizedFile("./csv_matrix/sensingMatrixResized.csv");

// results files
string RunTimeMeanMatrixFile("./csv_matrix/RunTimeMean_");
string RunTimeStdMatrixFile("./csv_matrix/RunTimeStd_");

string MSEMeanMatrixFile("./csv_matrix/MSEMean_");
string MSEStdMatrixFile("./csv_matrix/MSEStd_");

string SuccessMeanMatrixFile("./csv_matrix/SuccessMean_");
string SuccessStdMatrixFile("./csv_matrix/SuccessStd_");

string CSVEndName(".csv");

// --------------------------------------------------------------------------------------

#endif /* CONSTANTS_H */
