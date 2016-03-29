#include "ResizeEdge.h"
#include "../Draw/Draw.h"

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

	dst.create(size, CV_8UC1);
	Mat destination = dst.getMat();
	destination = Mat::zeros(size, CV_8UC1);
	
	/*!< nonzero pixel will be regarded as edge */
	vector<vector<Point>> contours;
	findContours(source, contours, RETR_LIST, CHAIN_APPROX_NONE);

	float ratioX = static_cast<float>(size.width) / source.size().width;
	float ratioY = static_cast<float>(size.height) / source.size().height;
	for (int i = 0; i < contours.size(); i++)
	{
		vector<Point> points = contours[i];

		/*! filter contours, only contours with more than 5 pixel will be kept */
		if (points.size() <= 5) continue;

		int length = static_cast<int>(points.size());
		bool closed = false;
		if (abs(points[0].x - points[length - 1].x) + abs(points[0].y - points[length - 1].y) <= 2) closed = true;

		Point2f lineStart, lineEnd, start;
		start = Point2f(points[0].x * ratioX, points[0].y * ratioY);
		lineStart = start;

		for (int j = 1; j < points.size(); j++)
		{
			lineEnd = Point2f(points[j].x * ratioX, points[j].y * ratioY);
			if (lineStart == lineEnd) continue;

			DrawEdgeLine(destination, lineStart, lineEnd);
			swap(lineStart, lineEnd);
		}
		if (closed) DrawEdgeLine(destination, lineStart, start);
	}

	return 0x0000;
}


/*!
Resize edge by interpolation.

@param src [in] Mat, singel channel uchar image, nonzero pixel will be regarded as edge.
@param size [in] Size, expected size.
@param dst [out] Mat, result image.
*/
int ResizeEdgeByInterpolation2(InputArray src, Size size, OutputArray dst)
{
	CV_Assert(src.type() == CV_8UC1 && !src.empty());

	Mat srcInput = src.getMat();
	Mat source;
	srcInput.copyTo(source);

	dst.create(size, CV_8UC1);
	Mat destination = dst.getMat();
	destination = Mat::zeros(size, CV_8UC1);

	/*!< nonzero pixel will be regarded as edge */
	vector<vector<Point>> contours;
	findContours(source, contours, RETR_LIST, CHAIN_APPROX_NONE);

	float ratioX = static_cast<float>(size.width) / source.size().width;
	float ratioY = static_cast<float>(size.height) / source.size().height;
	for (int i = 0; i < contours.size(); i++)
	{
		vector<Point> points = contours[i];

		/*! filter contours, only contours with more than 5 pixel will be kept */
		if (points.size() <= 5) continue;

		Point lineStart, lineEnd, start;
		start = Point(static_cast<int>(points[0].x*ratioX), static_cast<int>(points[0].y * ratioY));
		lineStart = start;

		for (int j = 1; j < points.size(); j++)
		{
			lineEnd = Point(static_cast<int>(points[j].x*ratioX), static_cast<int>(points[j].y * ratioY));
			if (lineStart == lineEnd) continue;

			line(destination, lineStart, lineEnd, Scalar(255));
			swap(lineStart, lineEnd);
		}
		line(destination, lineStart, start, Scalar(255));
	}

	return 0x0000;
}