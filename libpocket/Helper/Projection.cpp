#include "Projection.h"

/*!
Project horizontally.
count nonzero pixel in every line.

@param src [in] Mat, single channel uchar image
@param result [out] Mat, projection result, type = CV_32FC1, size = 1 * source height.
*/
int Projection(InputArray src, OutputArray dst)
{
	Mat source, destination;
	source = src.getMat();
	CV_Assert(source.type() == CV_8UC1 && !source.empty());

	dst.create(1, source.size().height, CV_32FC1);
	destination = dst.getMat();
	for (auto i = 0; i < source.size().height; i++)
	{
		destination.at<float>(i) = static_cast<float>(countNonZero(source.row(i)));
	}

	return 0x0000;
}