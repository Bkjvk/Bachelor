#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>

#include "tools.h"

using namespace std;
using namespace cv;
using namespace filesystem;

void converter(string src){
	path Path(src);
	int counter = 0;
	for (const auto& entry : directory_iterator(Path))
	{
		Mat image = imread(entry.path().string(), CV_LOAD_IMAGE_COLOR);   // Read the file
		if (!image.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image\n";
			exit(-1);
		}
		imwrite(src + to_string(++counter) + ".jpg", image);
	}
}

void histogramEqalizer(string fileName)
{
	Mat src = imread(fileName, CV_LOAD_IMAGE_COLOR); 
	if (!src.data)                             
	{
		cout << "Could not open or find the image\n";
		exit(-1);
	}
	cvtColor(src, src, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(src, dst);
	imshow("Obraz zrodlowy", src);
	imshow("equalizeHist", dst);
	waitKey();
}

void gradient(string fileName)
{
	Mat img = imread(fileName);
	if (!img.data)
	{
		cout << "Could not open or find the image\n";
		exit(-1);
	}
	img.convertTo(img, CV_32F, 1 / 255.0);

	// Calculate gradients gx, gy
	Mat gx, gy;
	Sobel(img, gx, CV_32F, 1, 0, 1);
	Sobel(img, gy, CV_32F, 0, 1, 1);

	Mat mag, angle;
	cartToPolar(gx, gy, mag, angle, 1);

	cout << "Mag = " << endl << " " << mag << endl << endl;
	cout << "angle = " << endl << " " << angle << endl << endl;
}