#include "Niblack.h"


/*!
Niblack二值化算法.

@param src [in] Mat,原图像,灰度图CV_8UC1
@param dst [out] Mat,二值化后的图像,调用时可为空
@param filter_size [in] int,Niblack算法参数,表示模板大小
@param k [in] int, Niblack算法参数,局部阈值计算参数
*/
int Niblack(InputArray src, OutputArray dst, int filter_size, float k)
{
	assert(src.type() == CV_8UC1);

	/*! 更新模板大小(应为奇数) */
	int half_size = int(floor(0.5 * filter_size));
	int full_size = 2 * half_size + 1;
	assert(half_size > 0);

	Mat source_uchar = src.getMat();
	Mat source, destination;

	source_uchar.convertTo(source, CV_32FC1);

	/*! 根据 D(x) = E(x^2) - (Ex)^2 的方法计算均值和方差 */
	Mat avg, power, avg_power, power_avg;
	Mat standard;
	boxFilter(source, avg, -1, Size(full_size, full_size));
	pow(avg, 2, avg_power);
	pow(source, 2, power);
	boxFilter(power, power_avg, -1, Size(full_size, full_size));
	sqrt(power_avg - avg_power, standard);

	/*! 计算得到局部阈值 */
	Mat threshold, threshold_uchar;
	threshold = avg + k * standard;

	/*! 输出结果 */
	dst.create(source_uchar.size(), CV_8UC1);
	destination = dst.getMat();
	destination = source > threshold;

	return 0;
}