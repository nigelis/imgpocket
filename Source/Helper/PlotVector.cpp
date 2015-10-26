#include "PlotVector.h"

#include <windows.h>
#include <fstream>
#include <string>


/*!
水平方向的投影.
将二维图像沿水平方向投影,统计每行非零像素的个数

@param src [in] 源图像,应为单通道二值图像
@param result [out] 投影结果,行向量,CV_32FC1
*/
void Projection(InputArray src, OutputArray result)
{
	Mat source, destination;
	source = src.getMat();

	result.create(1, source.size().height, CV_32FC1);
	destination = result.getMat();
	for (auto i = 0; i < source.size().height; i++)
	{
		destination.at<float>(i) = static_cast<float>(countNonZero(source.row(i)));
	}
}