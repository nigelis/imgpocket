#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*! Define peak point. */
struct PeakPoint
{
	int index;		/*!< point index in x direction, zero based. */
	double value;	/*!< point value. */
};

/*! 
Define peak region. 
An actual peak corresponds to a region.
Not only the point with highest value will be included,
But also those points whose slope are in a certain range.
*/
struct PeakRegion
{
	PeakPoint peak;				/*!< peak center. */
	vector<PeakPoint> region;	/*!< all points in peak region. */
	int minIndex;				/*!< minimum index in peak region. */
	int maxIndex;				/*!< maximum index in peak region. */
};

/*!
Find peak.

@param src [in] Mat, single channel, rows should equal to 1.
*/
int FindPeak(InputArray src, vector<PeakRegion> &peaks);
