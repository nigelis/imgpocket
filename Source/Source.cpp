#include <vector>
#include <opencv2/opencv.hpp>
#include "Segmentation/Segmentation.h"

using namespace std;
using namespace cv;

int main()
{
	string imgPath = "E:\\20_DATASET\\RESULT_MPS_LOGO_CATCH_VERSION_0.0.0.0\\MPS_LOGO_DETECTION_RIGHT\\中国工商银行_0002.JPG";
	Mat img = imread(imgPath, IMREAD_COLOR);
	vector<Mat> imgHSV;
	split(img, imgHSV);
	Mat source = imgHSV[2];

	Mat result;
	Point center = Point(img.size().width / 2, img.size().height / 2);
	RegionGrow(source, result, center, 2);


	return 0x0000;
}