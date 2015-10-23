#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Niblack(InputArray src, OutputArray dst, int filter_size, float k = 0.1);

