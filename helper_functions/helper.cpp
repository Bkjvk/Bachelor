#include <opencv2/core/core.hpp>
#include <iostream>

#include "helper.h"

using namespace cv;
using namespace std;

Mat integralImage(Mat image) {
	//since we will use it more, there is no need to evaluate them each time
	int width = image.size().width;
	int height = image.size().height;
	//empty matrices for calculations
	Mat ii = Mat(height, width, CV_32S, 0.0);
	Mat s = Mat(height, width, CV_32S, 0.0);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			/*
			s.at<Vec3i>(y, x).val[0] = ((y - 1 < 0) ? 0 : s.at<Vec3i>(y - 1, x).val[0]) + (int)image.at<Vec3b>(y, x)[0];
			s.at<Vec3i>(y, x).val[1] = ((y - 1 < 0) ? 0 : s.at<Vec3i>(y - 1, x).val[1]) + (int)image.at<Vec3b>(y, x)[1];
			s.at<Vec3i>(y, x).val[2] = ((y - 1 < 0) ? 0 : s.at<Vec3i>(y - 1, x).val[2]) + (int)image.at<Vec3b>(y, x)[2];
			ii.at<Vec3i>(y, x).val[0] = ((x - 1 < 0) ? 0 : ii.at<Vec3i>(y, x - 1).val[0]) + s.at<Vec3i>(y, x).val[0];
			ii.at<Vec3i>(y, x).val[1] = ((x - 1 < 0) ? 0 : ii.at<Vec3i>(y, x - 1).val[1]) + s.at<Vec3i>(y, x).val[1];
			ii.at<Vec3i>(y, x).val[2] = ((x - 1 < 0) ? 0 : ii.at<Vec3i>(y, x - 1).val[2]) + s.at<Vec3i>(y, x).val[2];
			*/
			cout << "(" << ii.at<Vec3i>(y, x).val[0] << ", " << ii.at<Vec3i>(y, x).val[1] << ", " << ii.at<Vec3i>(y, x).val[2] << ") ";
			//cout << (int)image.at<Vec3b>(y, x)[0] << " " << (int)image.at<Vec3b>(y, x)[1] << " " << (int)image.at<Vec3b>(y, x)[2] << "; ";
		}
		cout << endl;
	}
	return ii;
}

