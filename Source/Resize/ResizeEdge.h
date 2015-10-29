#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int ResizeEdge(InputArray src, OutputArray dst);

int ResizeEdgeByInterpolation(InputArray src, Size size, OutputArray dst);

int ResizeEdgeByInterpolation2(InputArray src, Size size, OutputArray dst);
