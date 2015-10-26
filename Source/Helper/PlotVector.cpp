#include "PlotVector.h"

#include <windows.h>
#include <fstream>
#include <string>


/*!
ˮƽ�����ͶӰ.
����άͼ����ˮƽ����ͶӰ,ͳ��ÿ�з������صĸ���

@param src [in] Դͼ��,ӦΪ��ͨ����ֵͼ��
@param result [out] ͶӰ���,������,CV_32FC1
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