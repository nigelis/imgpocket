#include "BasicHist.h"

#ifndef BASIC_HIST_BIN_SIZE
#define BISIC_HIST_BIN_SIZE 256
#endif

int BasicHist(InputArray src, OutputArray hist)
{
	Mat source = src.getMat();
	CV_Assert(!source.empty() && source.type() == CV_8UC1);

	float summary[BISIC_HIST_BIN_SIZE] = {0.0F};

	auto start = source.begin<uchar>();
	auto end = source.end<uchar>();

	while (start != end)
	{
		summary[*start]++;
		++start;
	}

	hist.create(1, BISIC_HIST_BIN_SIZE, CV_32FC1);
	Mat destination = hist.getMat();
	for (int i = 0; i < BISIC_HIST_BIN_SIZE; i++)
	{
		destination.at<float>(i) = summary[i];
	}

	return 0x0000;
}