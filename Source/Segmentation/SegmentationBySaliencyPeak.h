#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*!
Segmentation by saliency peaks.

@param saliency [in], Mat, saliency image, CV_8UC1.
@param area [out] Mat, segmentation result according to saliency analysis, foreground will be marked as white.
*/
int SegmentationBySaliencyPeak(InputArray saliency, OutputArray area);
