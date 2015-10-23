#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int Sauvola(InputArray src, OutputArray dst, int filter_size, float k = 0.1, int R = 128);
