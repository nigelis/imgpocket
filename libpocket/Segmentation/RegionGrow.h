#pragma once

#include <opencv2/opencv.hpp>
#include <stack>

using namespace std;
using namespace cv;

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seeds [in] stack<Point>, seed points.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, stack<Point>& seeds, int threshold);

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seed [in] Point, seed point.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, Point seed, int threshold);

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seedMap [in] Mat, points with nonzero value in seedMap will be seed points when initialized.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, InputArray seedMap, int threshold);