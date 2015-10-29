#include "DrawLine.h"

/*!
Draw line between two points.
pixel in line will be marked as white.

@param src [in/out] Mat, singel channel uchar image.
@param p1 [in] Point2f, point.
@param p2 [in] Point2f, point.
*/
int DrawEdgeLine(InputOutputArray src, Point2f p1, Point2f p2)
{
	Mat source = src.getMat();

	/*! if vertical line */
	if (static_cast<int>(p1.x) == static_cast<int>(p2.x))
	{
		Point start = Point(static_cast<int>(p1.x), static_cast<int>(p1.y));
		Point end = Point(static_cast<int>(p2.x), static_cast<int>(p2.y));

		line(source, start, end, Scalar(255));
		return 0x0000;
	}

	/*!< ensure p1 left of p2 */
	if (p1.x > p2.x) swap(p1, p2);

	/*!< calculate slope */
	float k = (p1.y - p2.y) / (p1.x - p2.x);	
	float x, y, step = 1 / k;

	if (k >= 0)
	{
		if (k >= 1)	/*!< k >= 1 */
		{
			float endY = static_cast<int>(p2.y) + 0.5F;
			x = p1.x; y = p1.y;

			while(true)
			{
				source.at<uchar>(static_cast<int>(x), static_cast<int>(y)) = 255;
				x += step;
				y += 1;
				if (y >= endY) break;
			}
		}
		else		/*!< 0 <= k < 1 */
		{
			float endX = static_cast<int>(p2.x) + 0.5F;
			x = p1.x; y = p1.y;

			while(true)
			{
				source.at<uchar>(static_cast<int>(x), static_cast<int>(y)) = 255;
				x += 1;
				y += k;
				if (x >= endX) break;
			}
		}
	}
	else
	{
		if (k <= -1)	/*!< k <= -1 */
		{
			float endY = static_cast<int>(p2.y) - 0.5F;
			x = p1.x; y = p1.y;

			while (true)
			{
				source.at<uchar>(static_cast<int>(x), static_cast<int>(y)) = 255;
				x -= step;
				y -= 1;
				if (y <= endY) break;
			}
		}
		else		/*!< -1 < k <= 0 */
		{
			float endX = static_cast<int>(p2.x) + 0.5F;
			x = p1.x; y = p1.y;

			while (true)
			{
				source.at<uchar>(static_cast<int>(x), static_cast<int>(y)) = 255;
				x += 1;
				y += k;
				if (x >= endX) break;
			}
		}
	}

	return 0x0000;
}