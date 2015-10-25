#include "Niblack.h"

/*!
Niblack binarization algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image.
@param windowSize [in] int, window size for calculation.
@param k [in] int, parameter for local threshold.
@return int, 0x0000 = Success.
*/
int Niblack(InputArray src, OutputArray dst, int windowSize, float k)
{
	if (src.type() != CV_8UC1 || src.empty())	
		return 0x0001;	/*!< source image type not supported. */

	/*! update window size, which should be odd. */
	if (windowSize < 2)	
		return 0x0002;	/*!< window size not supported. */
	if (windowSize / 2 == 0)
		windowSize++;

	Mat source, destination;
	Mat sourceUchar = src.getMat();
	sourceUchar.convertTo(source, CV_32FC1);

	/*! calcalte mean and variance via
	D(x) = E(x^2) - (Ex)^2 */
	Mat avg, power, avg_power, power_avg;
	Mat standard;
	boxFilter(source, avg, -1, Size(windowSize, windowSize));
	pow(avg, 2, avg_power);
	pow(source, 2, power);
	boxFilter(power, power_avg, -1, Size(windowSize, windowSize));
	sqrt(power_avg - power_avg, standard);

	/*! calculate local threshold */
	Mat threshold = avg + k * standard;

	/*! Output result */
	dst.create(sourceUchar.size(), CV_8UC1);
	destination = dst.getMat();
	destination = source > threshold;

	return 0x0000;
}