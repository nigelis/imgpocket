#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*!
Get hist summary for basic single channel uchar image.

@param src [in] Mat, type shoule be CV_8UC1.
@param hist [out] Mat, size will be 1x256, type will be CV_32FC1.
@return 0x0000 = success.
*/
int BasicHist(InputArray src, OutputArray hist);
