#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>

#include "Constants.h"
#include "detect.h"
#include "Setuper.h"

using namespace std;
using namespace cv;
using namespace filesystem;

void detectAndSave(string pathToPicture, Setuper* s, string resultId)
{
	CascadeClassifier cascadeClassifier;
	if (!cascadeClassifier.load(s->generateClassifierPath() + "/cascade.xml"))
	{
		cout << "[ERROR]\tFailed to load classifier!\n";
		exit(-1);
	};
	Mat image = imread(pathToPicture, CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image\n";
		exit(-1);
	}

	Mat frame_gray;
	cvtColor(image, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect object
	vector<Rect> object;
	cascadeClassifier.detectMultiScale(frame_gray, object);
	
	for (size_t i = 0; i < object.size(); i++)
	{
		Point upperLeftCorner(object[i].x, object[i].y);
		Point lowerRowCorner(object[i].x + object[i].width - 20, object[i].y + object[i].height - 20);
		rectangle(image, upperLeftCorner, lowerRowCorner,(255, 0, 255), 2);
	}
	string toSave = s->generateResultPath() + "/result" + resultId + string(".jpg");
	s->log("saving " + toSave + "\n");
	imwrite(toSave , image);
}

void TestCampaign(Setuper* s)
{
	int counter = 0;
	path Path(PATH_TO_TEST_SAMPLES);
	for (const auto& entry : directory_iterator(Path))
	{
		detectAndSave(Path.string() + ("\\") + entry.path().filename().string(), s ,to_string(counter++));
	}
}

void singleDetection(string pathToPicture, string pathToClassifier)
{
	CascadeClassifier cascadeClassifier;
	if (!cascadeClassifier.load(pathToClassifier + "/cascade.xml"))
	{
		cout << "[ERROR]\tFailed to load classifier!\n";
		exit(-1);
	};
	Mat image = imread(pathToPicture, CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image\n";
		exit(-1);
	}

	Mat frame_gray;
	cvtColor(image, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect object
	vector<Rect> object;
	cascadeClassifier.detectMultiScale(frame_gray, object);

	for (size_t i = 0; i < object.size(); i++)
	{
		Point upperLeftCorner(object[i].x, object[i].y);
		Point lowerRowCorner(object[i].x + object[i].width - 20, object[i].y + object[i].height - 20);
		rectangle(image, upperLeftCorner, lowerRowCorner, (255, 0, 255), 2);
	}
	string toSave = pathToClassifier + string("/rezultat.jpg");
	imwrite(toSave, image);
}