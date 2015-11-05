#include "SegmentationBySaliencyPeak.h"
#include "../Hist/BasicHist.h"
#include "../Helper/FindPeak.h"

/*! Store information about contours for contour merging. */
struct ContourInfo
{
	Rect rect;
	vector<vector<Point>> contours;
};

int SegmentationBySaliencyPeak(InputArray saliency, OutputArray area)
{
	Mat source = saliency.getMat();
	CV_Assert(!source.empty() && source.type() == CV_8UC1);

	Mat hist;		/*!< histogram of saliency. */
	BasicHist(source, hist);

	vector<PeakRegion> peaks;	/*!< peaks in histogram, indicating interest area. */
	vector<Mat> regions;
	FindPeak(hist, peaks);

	for (int i = 0; i < static_cast<int>(peaks.size()); i++)
	{
		Mat interest;
		if (peaks[i].minIndex == peaks[i].maxIndex)
			interest = source == peaks[i].minIndex;
		else
			interest = source >= peaks[i].minIndex & source <= peaks[i].maxIndex;
		regions.push_back(interest);


		/*! find contours. */
		Mat copy;
		interest.copyTo(copy);
		vector<vector<Point>> totalContours;
		findContours(copy, totalContours, RETR_LIST, CHAIN_APPROX_NONE);

		int maxSize = 0;
		for (int j = 0; j < static_cast<int>(totalContours.size()); j++)
			if (static_cast<int>(totalContours[j].size()) >= maxSize) 
				maxSize = totalContours[j].size();

		/*!
		ignoring contours whose size is relatively samll.
		get contours bounding rects, for merging or spliting.
		*/
		list<ContourInfo> contours;
		int thresSize = maxSize / 25;
		for (int j = 0; j < static_cast<int>(totalContours.size()); j++)
		{
			if (static_cast<int>(totalContours[j].size()) >= thresSize)
			{
				ContourInfo info;
				info.contours.push_back(totalContours[j]);
				info.rect = boundingRect(totalContours[j]);
				contours.push_back(info);
			}
		}

		/*!
		
		*/
		bool canCombine = true;
		while(canCombine)
		{
			canCombine = false;

			/*! Bubble sort. */
			for (int j = 1; j < static_cast<int>(contours.size()); j++)
			{
				for (int k = j; k < static_cast<int>(contours.size()); k++)
				{

				}
			}
			
		}

		imshow("INTEREST", interest);
		waitKey();
		destroyAllWindows();
	}


	return 0x0000;
}
