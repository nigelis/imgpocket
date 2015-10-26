#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*!
Project horizontally.
count nonzero pixel in every line.

@param src [in] Mat, single channel uchar image
@param result [out] Mat, projection result, type = CV_32FC1, size = 1 * source height.
*/
int Projection(InputArray src, OutputArray dst);
