#include "PlotVector.h"

/*!
Plot the vector (like a histogram).

@param src [in] Mat, input vector, neither its rows or cols should equal to 1.
@param dst [out] Mat, output single channel image.
@param size [in] Size, output image size.
@return int, 0x0000 = Success.
*/
int PlotVector(InputArray src, OutputArray dst, Size size)
{
	CV_Assert((src.size().height == 1 || src.size().width == 1) && !src.empty() && src.channels() == 1);	/*!< should be a vector */

	int rows = size.height, cols = size.width;

	/*! convert to row vector and type = CV_32FC1 */
	Mat source = src.getMat();
	Mat sourceDouble;
	source.convertTo(sourceDouble, CV_64F);
	if (sourceDouble.cols == 1)
		sourceDouble = sourceDouble.t();

	resize(sourceDouble, sourceDouble, Size(cols, 1));
	
	double minValue, maxValue;
	Point minLoc, maxLoc;
	minMaxLoc(sourceDouble, &minValue, &maxValue, &minLoc, &maxLoc);

	dst.create(size, CV_8UC1);
	Mat destination = dst.getMat();
	destination = Mat::zeros(size, CV_8UC1);

	for (int i = 0; i < cols; i++)
	{
		int maxRow = rows - static_cast<int>(sourceDouble.at<double>(i) / maxValue * rows);
		for (int j = maxRow; j < rows; j++)
		{
			destination.at<uchar>(j, i) = 255;
		}
	}
	
	return 0x0000;
}