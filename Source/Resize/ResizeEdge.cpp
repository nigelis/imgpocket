#include "ResizeEdge.h"

int ResizeEdge(InputArray src, OutputArray dst)
{


	return 0x0000;
}

/*! 
Resize edge by interpolation.

@param src [in] Mat, singel channel uchar image, nonzero pixel will be regarded as edge.
@param size [in] Size, expected size.
@param dst [out] Mat, result image.
*/
int ResizeEdgeByInterpolation(InputArray src, Size size, OutputArray dst)
{
	CV_Assert(src.type() == CV_8UC1 && !src.empty());

	Mat srcInput = src.getMat();
	Mat source;
	srcInput.copyTo(source);
	
	/*!< nonzero pixel will be regarded as edge */
	vector<vector<Point>> contours;
	findContours(source, contours, RETR_LIST, CHAIN_APPROX_NONE);

	float ratioX = static_cast<float>(size.width) / source.size().width;
	float ratioY = static_cast<float>(size.height) / source.size().height;
	vector<vector<Point2f>> contoursResize;
	for (int i = 0; i < contours.size(); i++)
	{
		vector<Point> pointSrc = contours[i];
		vector<Point2f> pointDst;

		for (int j = 0; j < pointSrc.size(); j++)
			pointDst.push_back(Point2f(pointSrc[j].x*ratioX, pointSrc[j].y * ratioY));
		contoursResize.push_back(pointDst);
	}

	return 0x0000;
}