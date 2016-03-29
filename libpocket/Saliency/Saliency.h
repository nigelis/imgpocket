#ifndef SLIENCY_DLL_H_
#define SLIENCY_DLL_H_

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

#ifdef SALIENCY_DLL_API
#define SALIENCY_DLL_API extern "C" _declspec(dllimport)
#else
#define SALIENCY_DLL_API extern "C" _declspec(dllexport)
#endif
/************************************************************************
�� �� ����GetHC
�������ܣ��õ�����ͼ���������ͼ
���������ԭͼ
�������������ֱ��ͼ�Աȶȵ�������ͼ
************************************************************************/
SALIENCY_DLL_API void GetHC(const Mat &img3f,Mat &salHC);

/************************************************************************
�� �� ����GetRC
�������ܣ��õ�����ͼ���������ͼ
���������ԭͼ--img3f
		 ���ƿռ�Ȩֵǿ�Ȳ���--sigmaDist
		 ����ͼ�ķָ���ֵ��������--segK
		 ��С�ڵ���--segMinSize
		 �ָ��и�˹ģ����׼��--segSigma
�����������������Աȶȵ�������ͼ--salRC�ͷָ�ͼ--seg
************************************************************************/
SALIENCY_DLL_API void GetRC(const Mat &img3f,double sigmaDist, double segK, int segMinSize, double segSigma, Mat &salRC, Mat &seg);

#endif //SLIENCY_DLL_H_

typedef pair<float, int> CostfIdx;
typedef vector<float> vecF;

struct Region {
	Region() { pixNum = 0; }
	int pixNum;  // ������;
	vector<CostfIdx> freIdx;  // ÿ����ɫ�������Լ������Ƶ��;
	Point2d centroid;// ͼ��;
};

template<typename T> inline T sqr(T x) { return x * x; }
template<class T> inline T vecDist3(const Vec<T, 3> &v1, const Vec<T, 3> &v2) { return sqrt(sqr(v1[0] - v2[0]) + sqr(v1[1] - v2[1]) + sqr(v1[2] - v2[2])); }
template<class T> inline T vecSqrDist3(const Vec<T, 3> &v1, const Vec<T, 3> &v2) { return sqr(v1[0] - v2[0]) + sqr(v1[1] - v2[1]) + sqr(v1[2] - v2[2]); }
template<class T> inline T pntSqrDist(const Point_<T> &p1, const Point_<T> &p2) { return sqr(p1.x - p2.x) + sqr(p1.y - p2.y); }

static void GetHC(const Mat &binColor3f, const Mat &weight1f, Mat &_colorSal);
static void SmoothSaliency(const Mat &binColor3f, Mat &sal1d, float delta, const vector<vector<CostfIdx>> &similar);

static Mat GetRC(const Mat &img3f, double sigmaDist, double segK, int segMinSize, double segSigma, Mat &Reg);
static int Quantize(const Mat& img3f, Mat &idx1i, Mat &_color3f, Mat &_colorNum, double ratio = 0.95);
static int SegmentImage(const Mat &_src3f, Mat &pImgInd, double sigma, double c, int min_size);
static void BuildRegions(const Mat& regIdx1i, vector<Region> &regs, const Mat &colorIdx1i, int colorNum);
static void RegionContrast(const vector<Region> &regs, const Mat &color3fv, Mat& regSal1d, double sigmaDist);

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <windows.h>

