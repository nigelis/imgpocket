#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*!
Plot the vector (like a histogram).

@param src [in] Mat, input vector, its rows or cols should equal to 1.
@param dst [out] Mat, output single channel image.
@param size [in] Size, output image size, 800w and 600h as default.
@return int, 0x0000 = Success.
*/
int PlotVector(InputArray src,OutputArray dst, Size size = Size(800, 600));
