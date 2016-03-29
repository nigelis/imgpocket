#include "Otsu.h"


/*!
Otsu阈值化算法.

@param src [in] 输入图像,应为CV_8UC1类型
@param dst [out] 输出图像
*/
int Otsu(InputArray src, OutputArray dst)
{
	Mat source;

	source = src.getMat();
	assert(!source.empty());
	int source_size = source.size().width * source.size().height;

	const auto GRAY_LEVEL = 256;

	/*! 计算source图像的直方图 */
	int channels[] = { 0 };
	int dims = 1;
	int hist_size[] = { GRAY_LEVEL };
	float granges[] = { 0, GRAY_LEVEL };
	const float* ranges[] = { granges };
	MatND hist;

	calcHist(&source, 1, channels, Mat(), hist, dims, hist_size, ranges, true, false);

	/*! 统计概率分布 */
	Mat p = Mat::zeros(1, GRAY_LEVEL, CV_32FC1);
	Mat ip = Mat::zeros(1, GRAY_LEVEL, CV_32FC1);

	p = hist / source_size;
	for (int i = 0; i < GRAY_LEVEL; i++)
	{
		ip.at<float>(i) = p.at<float>(i) * i;
	}

	/*! 计算Delta_B序列 */
	float w_k = p.at<float>(0);
	float mu_k = ip.at<float>(0);
	float mu_t = static_cast<float>(sum(ip).val[0]);
	Mat delta_b = Mat::zeros(1, GRAY_LEVEL, CV_32FC1);
	for (int i = 1; i < GRAY_LEVEL - 1; i++)
	{
		w_k += p.at<float>(i);
		mu_k += ip.at<float>(i);
		delta_b.at<float>(i) = pow(mu_t * w_k - mu_k, 2) / (w_k * (1 - w_k));
	}

	/*! 查找极值点,确定阈值 */
	Point locate_max;
	minMaxLoc(delta_b, nullptr, nullptr, nullptr, &locate_max);

	threshold(source, dst, locate_max.x, GRAY_LEVEL - 1, THRESH_BINARY);

	return 0;
}