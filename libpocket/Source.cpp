#include <vector>
#include <opencv2/opencv.hpp>
#include "Segmentation/Segmentation.h"
#include "Binarization/Binarization.h"
#include "Helper/Helper.h"
#include "Resize/Resize.h"
#include "Saliency/Saliency.h"
#include "Hist/Hist.h"
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
	string imgPath = "C:\\Users\\Nigel\\Desktop\\Source.png";
	imgPath = "E:\\OneDrive\\2015_MPS\\10_Logo_Standard\\中国银联.jpg";
	imgPath = "E:\\20_DataSet\\Result_MPS_Logo_Catch_Version_0.0.0.0\\MPS_LOGO_DETECTION_Right\\中国银联_0001.jpg";
	imgPath = "E:\\20_DataSet\\Detection\\中国农业银行_0001.jpg";
	imgPath = "E:\\20_DataSet\\Detection\\中国工商银行_0017.jpg";


	Mat source = imread(imgPath, IMREAD_COLOR);

	Mat hc, hist, plot;
	GetHC(source, hc);
	BasicHist(hc, hist);
	PlotVector(hist, plot);

	Mat imgcanny;
	Canny(hc, imgcanny, 50, 130);
	
	Mat area;
	SegmentationBySaliencyPeak(hc, area);

	string imgList = "E:\\20_DataSet\\DatasetLogoBasicEx\\ImageList.txt";
	imgList = "E:\\20_DataSet\\Result_MPS_Logo_Catch_Version_0.0.0.0\\MPS_LOGO_DETECTION_Right\\ImageList.txt";
	imgList = "E:\\20_DataSet\\Detection\\ImageList.txt";
	imgList = "E:\\20_DataSet\\10_MPS_LOGO_TEST_201511061000\\ImageList.txt";
	//imgList = "E:\\10_Project\\logoDetectAndRecog\\SourceCode\\Result.txt";
	//imgList = "E:\\OneDrive\\2015_MPS\\10_Logo_Standard\\ImageList.txt";
	fstream f = fstream(imgList, ios::in);
	fstream fOut = fstream("Error.txt", ios::out);
	string outputFolder = "E:\\20_DataSet\\Detection\\";

	int errorCounts = 0;
	int totalCounts = 0;

	while (!f.eof())
	{

		string imgLocation;
		f >> imgLocation;

		Mat img, hc;
		img = imread(imgLocation, IMREAD_COLOR);
		GetHC(img, hc);

		Mat re;
		SegmentationBySaliencyPeak(hc, re);
	}
	//BasicHist(hc, hist);
	//PlotVector(hist, plot, Size(256, 600));
	//
	//vector<PeakRegion> peaks;
	//FindPeak(hist, peaks);

	//for (int i = 0; i < static_cast<int>(peaks.size()); i++)
	//{
	//	Mat target = (hc >= peaks[i].minIndex) & (hc <= peaks[i].maxIndex);

	//	imshow("Result", target);
	//	waitKey(0);
	//}

	//destroyAllWindows();

	return 0x0000;
}