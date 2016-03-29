#include "RegionGrow.h"

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seeds [in] stack<Point>, seed points.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, stack<Point>& seeds, int threshold)
{
	CV_Assert(src.type() == CV_8UC1 && !src.empty());

	Mat source = src.getMat();
	int height = source.size().height;
	int width = source.size().width;
	auto step = source.step;

	dst.create(Size(width, height), CV_8UC1);
	Mat destination = dst.getMat();
	destination = Mat::zeros(Size(width, height), CV_8UC1);

	while (!seeds.empty())
	{
		Point seed = seeds.top();
		seeds.pop();

		if (seed.x < 0 || seed.x >= width || seed.y < 0 || seed.y >= height)
			continue;	/*!< seed point out of boundary */

		unsigned center = step[0] * seed.y + step[1] * seed.x;
		*(destination.data + center) = 255;
		uchar val = *(source.data + center);

		vector<Point> offset;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0) continue;	/*!< ignore center point itself */

				int x = seed.x + i;
				int y = seed.y + j;
				if (x < 0 || x >= width || y < 0 || y >= height) continue;	/*!< ignore surrounding point out of boundary */
				
				offset.push_back(Point(x, y));
			}
		}

		int length = offset.size();
		for (int i = 0; i < length; i++)
		{
			unsigned pos = step[0] * offset[i].y + step[1] * offset[i].x;
			if (*(destination.data + pos) == 255)	
				continue;	/*!< already be marked as seed point before */
			
			uchar value = *(source.data + pos);
			if (abs(value - val) > threshold)
				continue;	/*!< point with difference over threshold cannot grow */
			seeds.push(offset[i]);
		}
	}

	return 0x0000;
}

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seed [in] Point, seed point.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, Point seed, int threshold)
{
	stack<Point> seeds;
	seeds.push(seed);

	return RegionGrow(src, dst, seeds, threshold);
}

/*!
Region grow algorithm.

@param src [in] Mat, single channel uchar image.
@param dst [out] Mat, result image, same type as src.
@param seedMap [in] Mat, points with nonzero value in seedMap will be seed points when initialized.
@param threshold [in] int, point with difference above threshold cannot be grown as seed point.
*/
int RegionGrow(InputArray src, OutputArray dst, InputArray seedMap, int threshold)
{
	CV_Assert(src.size() == seedMap.size() && !seedMap.empty() && seedMap.type() == CV_8UC1);

	Mat map = seedMap.getMat();
	int rows = map.rows, cols = map.cols, idx = 0;

	stack<Point> seeds;
	auto start = map.begin<uchar>();
	auto end = map.end<uchar>();

	while(start != end)
	{
		if (*start != 0)
		{
			int row = idx / cols;
			int col = idx - row * cols;
			seeds.push(Point(col, row));
		}

		++idx;
		++start;
	}

	if (seeds.empty())	return 0x0001;	/*!< no seed points */
	return RegionGrow(src, dst, seeds, threshold);
}