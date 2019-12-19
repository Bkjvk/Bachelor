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

void detectAndSave(string pathToPicture, string pathToResult, Setuper* s, string resultId, DetectorParams detectorParams)
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
	if (!detectorParams.useMax)
	{
		cascadeClassifier.detectMultiScale(frame_gray, object, detectorParams.scale, detectorParams.minNeighbours, 0, detectorParams.minSize, detectorParams.maxSize);
	}
	else
	{
		cascadeClassifier.detectMultiScale(frame_gray, object, detectorParams.scale, detectorParams.minNeighbours, 0, detectorParams.minSize);
	}
	
	for (size_t i = 0; i < object.size(); i++)
	{
		Point upperLeftCorner(object[i].x, object[i].y);
		Point lowerRowCorner(object[i].x + object[i].width, object[i].y + object[i].height);
		rectangle(image, upperLeftCorner, lowerRowCorner,(255, 0, 255), 2);
	}
	string toSave = pathToResult + "/result" + resultId + string(".jpg");
	//s->log("saving " + toSave + "\n");
	imwrite(toSave , image);
}

void TestCampaign(Setuper* s, DetectorParams detectorParams, string PathToResult)
{
	int counter = 0;
	path Path(PATH_TO_TEST_SAMPLES);
	for (const auto& entry : directory_iterator(Path))
	{
		detectAndSave(Path.string() + ("\\") + entry.path().filename().string(), PathToResult, s, to_string(counter++), detectorParams);
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
	cascadeClassifier.detectMultiScale(frame_gray, object, 1.04, 15, 0, Size(64, 22), Size(65,25));

	for (size_t i = 0; i < object.size(); i++)
	{
		Point upperLeftCorner(object[i].x, object[i].y);
		Point lowerRowCorner(object[i].x + object[i].width, object[i].y + object[i].height);
		rectangle(image, upperLeftCorner, lowerRowCorner,(255, 0, 255), 2);
	}
	string toSave = pathToClassifier + string("/rezultat7.jpg");
	imwrite(toSave, image);
}

DetectorParams::DetectorParams()
{
	useMax = false;
	scale = 1.05;
	minNeighbours = 5;
	minSize = Size(24,24);
}

DetectorParams::DetectorParams(float _scale, int _minNeighbours, Size _minSize)
{
	useMax = false;
	scale = _scale;
	minNeighbours = _minNeighbours;
	minSize = _minSize;
}

DetectorParams::DetectorParams(float _scale, int _minNeighbours, Size _minSize, Size _maxSize)
{
	scale = _scale;
	minNeighbours = _minNeighbours;
	minSize = _minSize;
	maxSize = _maxSize;
}