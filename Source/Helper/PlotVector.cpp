#include "PlotVector.h"

/*!
Plot the vector (like a histogram).

@param src [in] Mat, input vector, its rows or cols should equal to 1.
@param dst [out] Mat, output single channel image.
@param size [in] Size, output image size.
@return int, 0x0000 = Success.
*/
int PlotVector(InputArray src, OutputArray dst, Size size)
{
	CV_Assert((src.size().height == 1 || src.size().width == 1) && !src.empty() && (src.type() == CV_8UC1 || src.type() == CV_32FC1));	/*!< should be a vector */

	int rows = size.height, cols = size.width;

	/*! convert to row vector and type = CV_32FC1 */
	Mat source = src.getMat();
	Mat sourceFloat;
	source.convertTo(sourceFloat, CV_32F);
	if (sourceFloat.cols == 1)
		sourceFloat = sourceFloat.t();

	resize(sourceFloat, sourceFloat, Size(cols, 1));
	
	double minValue, maxValue;
	Point minLoc, maxLoc;
	minMaxLoc(sourceFloat, &minValue, &maxValue, &minLoc, &maxLoc);

	dst.create(size, CV_8UC1);
	Mat destination = dst.getMat();
	destination = Mat::zeros(size, CV_8UC1);

	for (int i = 0; i < cols; i++)
	{
		int maxRow = static_cast<int>(sourceFloat.at<float>(i) / maxValue * rows);
		for (int j = 0; j < maxRow; j++)
		{
			destination.at<uchar>(j, i) = 255;
		}
	}
	
	return 0x0000;
}