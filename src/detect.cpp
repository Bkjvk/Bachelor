#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>
#include <conio.h>

#include "Constants.h"
#include "detect.h"
#include "Setuper.h"

using namespace std;
using namespace cv;
using namespace filesystem;

bool checkKeyPress()
{
	char keyPress;
	while (keyPress = _getch())
	{
		if (keyPress == 'y' or keyPress == 'n')
		{
			break;
		}
	}

	if (keyPress == 'y') return true;
	return false;
}

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
	float scale;
	int minNeighbour, minWidth, maxWidth, minHeight, maxHeight;
	bool useDefault, needMinSize, needMaxSize;
	char keyPress;

	CascadeClassifier cascadeClassifier;
	if (!cascadeClassifier.load(pathToClassifier))
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

	cout << "Use default detector? press y(yes) or n(no): \n";
	useDefault = checkKeyPress();
	if (!useDefault)
	{
		cout << "Insert scale (recommended values 1.03 - 1.1): ";
		cin >> scale;
		cout << "Insert min neighbours (recommended values 3 - 6): ";
		cin >> minNeighbour;
		cout << "Use minimal size of object? press y(yes) or n(no): \n";
		needMinSize = checkKeyPress();
		if (needMinSize)
		{
			cout << "Insert minimum width (i.e. 20): ";
			cin >> minWidth;
			cout << "Insert minimum height (i.e. 20): ";
			cin >> minHeight;
			cout << "Use maximum size of object? press y(yes) or n(no): \n";
			needMaxSize = checkKeyPress();
			if (needMaxSize)
			{
				cout << "Insert maximum width (i.e. 20): ";
				cin >> maxWidth;
				cout << "Insert maximum height (i.e. 20): ";
				cin >> maxHeight;
			}
		}
	}


	Mat frame_gray;
	cvtColor(image, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect object
	vector<Rect> object;
	if (useDefault)
	{
		cascadeClassifier.detectMultiScale(frame_gray, object);
	}
	else if (needMinSize and needMaxSize)
	{
		cascadeClassifier.detectMultiScale(frame_gray, object, scale, minNeighbour, 0, Size(minWidth, minHeight), Size(maxWidth, maxHeight));
	}
	else if (needMinSize)
	{
		cascadeClassifier.detectMultiScale(frame_gray, object, scale, minNeighbour, 0, Size(minWidth, minHeight));
	}
	else if (!useDefault)
	{
		cascadeClassifier.detectMultiScale(frame_gray, object, scale, minNeighbour);
	}
	

	for (size_t i = 0; i < object.size(); i++)
	{
		Point upperLeftCorner(object[i].x, object[i].y);
		Point lowerRowCorner(object[i].x + object[i].width, object[i].y + object[i].height);
		rectangle(image, upperLeftCorner, lowerRowCorner,(255, 0, 255), 2);
	}
	string toSave = "detection.jpg";
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