#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*!
Niblack binarization algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image.
@param windowSize [in] int, window size for calculation, 3 as default.
@param k [in] int, parameter for local threshold, -0.2 as default.
@return int, 0x0000 = Success.
*/
int Niblack(InputArray src, OutputArray dst, int windowSize = 3, float k = -0.2);
