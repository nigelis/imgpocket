#include <vector>
#include <opencv2/opencv.hpp>
#include "Segmentation/Segmentation.h"
#include "Binarization/Binarization.h"
#include "Helper/Helper.h"
#include "Resize/Resize.h"

using namespace std;
using namespace cv;

int main()
{
	string imgPath = "C:\\Users\\Nigel\\Desktop\\Source.png";
	Mat source = imread(imgPath, IMREAD_COLOR);

	Mat gray, resized;
	cvtColor(source, gray, CV_BGR2GRAY);

	Mat cannySource, cannyResize, cannyInter;
	Canny(gray, cannySource, 50, 130);

	ResizeEdgeByInterpolation(cannySource, Size(320, 320), cannyInter);

	resize(source, resized, Size(320, 320));
	cvtColor(resized, gray, CV_BGR2GRAY);
	Canny(gray, cannyResize, 50, 130);
	

	return 0x0000;
}