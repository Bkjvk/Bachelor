#pragma once
#ifndef DETECT_H
#define DETECT_H
#include <string>
#include "opencv2/imgproc.hpp"

#include "Setuper.h"

using namespace std;

struct DetectorParams {
	bool useMax;
	float scale;
	int minNeighbours;
	cv::Size minSize;
	cv::Size maxSize;
	DetectorParams();
	DetectorParams(float, int, cv::Size);
	DetectorParams(float, int, cv::Size, cv::Size);
};

void detectAndSave(string, string, string);
void TestCampaign(Setuper*, DetectorParams, string);
void singleDetection(string, string);

#endif