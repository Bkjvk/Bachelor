#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/core/core.hpp>

using namespace cv;

class RectangleRegion {
private:
	
public:
	int x;
	int y;
	int width;
	int height;
	RectangleRegion(int, int, int, int);
	Mat computeFeature(Mat);
};

#endif