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
函 数 名：GetHC
函数功能：得到输入图像的显著性图
输入参数：原图
输出参数：基于直方图对比度的显著性图
************************************************************************/
SALIENCY_DLL_API void GetHC(const Mat &img3f,Mat &salHC);

/************************************************************************
函 数 名：GetRC
函数功能：得到输入图像的显著性图
输入参数：原图--img3f
		 控制空间权值强度参数--sigmaDist
		 基于图的分割阈值函数常量--segK
		 最小节点数--segMinSize
		 分割中高斯模糊标准差--segSigma
输出参数：基于区域对比度的显著性图--salRC和分割图--seg
************************************************************************/
SALIENCY_DLL_API void GetRC(const Mat &img3f,double sigmaDist, double segK, int segMinSize, double segSigma, Mat &salRC, Mat &seg);

#endif //SLIENCY_DLL_H_

typedef pair<float, int> CostfIdx;
typedef vector<float> vecF;

struct Region {
	Region() { pixNum = 0; }
	int pixNum;  // 像素数;
	vector<CostfIdx> freIdx;  // 每种颜色的索引以及其出现频率;
	Point2d centroid;// 图心;
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

