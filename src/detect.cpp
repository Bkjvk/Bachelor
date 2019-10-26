#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>

#include "Constants.h"
#include "detect.h"

using namespace std;
using namespace cv;
namespace fs = std::experimental::filesystem;

void detectAndSave(string pathToPicture, string nameOfClassifier, string resultId)
{
	CascadeClassifier cascadeClassifier;
	if (!cascadeClassifier.load(nameOfClassifier))
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
	cout << "saving " << PATH_TO_TEST_RESULT << "/result" << resultId << string(".jpg") << endl;
	imwrite(PATH_TO_TEST_RESULT + string("/result") + resultId + string(".jpg") , image);
}

void TestCampaign(string pathToClassifier)
{
	int counter = 0;
	fs::path Path(PATH_TO_TEST_SAMPLES);
	for (const auto& entry : fs::directory_iterator(Path))
	{
		detectAndSave(Path.string() + ("\\") + entry.path().filename().string(), pathToClassifier, to_string(counter++));
	}
}