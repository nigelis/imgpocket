#include "FindPeak.h"

#ifndef FIND_PEAK_PARAMETER
#define FIND_PEAK_PARAMETER

#define PEAK_REGION_WIDTH_MAX 5
#define PEAK_REGION_WIDTH_HALF 2
#define PEAK_REGION_COUNT_MAX 5
#define PEAK_POINT_COUNT_MAX 25

#endif

int FindPeak(InputArray src, vector<PeakRegion>& peaks)
{
	Mat source = src.getMat();
	CV_Assert(!source.empty() && source.channels() == 1 && (source.cols == 1 || source.rows == 1));

	if (source.cols == 1) source = source.t();
	source.convertTo(source, CV_64F);

	vector<PeakPoint> unsort, sort;
	for (int i = 0; i < source.cols; i++)
	{
		PeakPoint point;
		point.index = i;
		point.value = source.at<double>(i);
		unsort.push_back(point);
		sort.push_back(point);
	}

	/*! Bubble sort to get 25 PeakPoint with greater value. */
	for (int i = 0; i < PEAK_POINT_COUNT_MAX; i++)
	{
		for (int j = source.cols - 1; j > 0; j--)
		{
			if (sort[j].value > sort[j - 1].value)
				swap(sort[j], sort[j - 1]);
		}
	}


	/*! Get region peak. */
	peaks.clear();
	vector<PeakRegion> regions;

	/*! Assuimg region is not connected to each other, i.e. no common peak point. */
	for (int i = 0; i < PEAK_POINT_COUNT_MAX; i++)
	{
		PeakPoint point = sort[i];
		bool connected = false;

		for (int j = 0; j < static_cast<int>(regions.size()); j++)
		{
			if (abs(regions[j].peak.index - point.index) <= PEAK_REGION_WIDTH_HALF)
			{
				connected = true;
				break;
			}
		}

		if (connected) continue;
		PeakRegion region;
		region.peak = point;
		region.region.push_back(point);
		regions.push_back(region);

		if (regions.size() >= PEAK_REGION_COUNT_MAX) break;
	}

	/*! Ignore regions whose peak value is below threshold */
	double PeakAmplitudeThreshold = max(regions[0].peak.value*0.1, regions[1].peak.value * 0.2);
	for (int i = 0; i < PEAK_REGION_COUNT_MAX; i++)
	{
		if (regions[i].peak.value >= PeakAmplitudeThreshold) peaks.push_back(regions[i]);
	}

	/*! Expand the region of peak by threshold amplitude threshold and slope threshold. */
	for (int i = 0; i < static_cast<int>(peaks.size()); i++)
	{
		PeakRegion region = peaks[i];
		double amplitudeThreshold = region.peak.value * 0.2;
		double slopeThreshold = region.peak.value * 0.5;

		for (int j = -1 * PEAK_REGION_WIDTH_HALF; j <= PEAK_REGION_WIDTH_HALF; j++)
		{
			int index = region.peak.index + j;
			if (index < 0 || index >= source.cols || j == 0)continue;

			PeakPoint point = unsort[index];
			double amplitude = point.value;
			double slope = abs((region.peak.value - point.value) / (region.peak.index - point.index));

			if (amplitude >= amplitudeThreshold && slope <= slopeThreshold) region.region.push_back(point);
		}

		region.minIndex = region.peak.index;
		region.maxIndex = region.peak.index;
		for (int j = 0; j < static_cast<int>(region.region.size()); j++)
		{
			int index = region.region[j].index;
			if (index > region.maxIndex) region.maxIndex = index;
			if (index < region.minIndex) region.minIndex = index;
		}

		peaks[i] = region;
	}

	return 0x0000;
}
