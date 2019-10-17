//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/dnn/shape_utils.hpp>
//c++
#include <iostream>
//project
#include "helper_functions/helper.h"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	String imageName("test.jpg"); // by default
	Mat image;
	image = imread(samples::findFile(imageName), IMREAD_COLOR); // Read the file
	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);                // Show our image inside it.
	Mat ii = integralImage(image);
	//cout << (int)image.at<Vec3b>(0, 0)[0] << " " << (int)image.at<Vec3b>(0, 0)[1] << " " << (int)image.at<Vec3b>(0, 0)[2] << " ";
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}