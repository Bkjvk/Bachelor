#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include "opencv2/imgproc.hpp"

#include "Controller.h"
#include "Setuper.h"
#include "helper.h"
#include "Constants.h"
#include "CreateSample.h"
#include "detect.h"

using namespace std;
using namespace filesystem;

string transformTime(double temp)
{
	int hours = temp / 3600000;
	temp -= (double)hours * 3600000;
	int minutes = temp / 60000;
	temp -= (double)minutes * 60000;
	int seconds = temp / 1000;
	temp -= (double)seconds * 1000;
	return to_string(hours) + "h:" + to_string(minutes) + "m:" + to_string(seconds) + "s:" + to_string(temp) + "ms";
}

void controller(Setuper* s)
{
	vector<DetectorParams> detectorParams;
	detectorParams.push_back(DetectorParams(1.05, 3, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.05, 4, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.05, 5, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.05, 6, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.10, 5, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.07, 5, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.03, 5, cv::Size(50, 20), cv::Size(100, 40)));
	detectorParams.push_back(DetectorParams(1.03, 15, cv::Size(50, 20), cv::Size(100, 40)));

	string message = "Do you want to recreate info files? ";
	bool recreateInfoFiles = askUserForAcceptance(message);
	message = "Do you want to use test plans";
	if (askUserForAcceptance(message))
	{
		if (recreateInfoFiles)
		{
			CreateInfoFiles(true);
		}
		path Path(PATH_TO_TEST_PLANS);
		for (const auto& entry : directory_iterator(Path))
		{
			s->log("#### Reading new setup data ####\n");
			s->readNewSetuperParams(entry.path().filename().string());

			s->log("#### Creating samples ####\n");
			chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
			CreateSamples(s);
			chrono::duration<double, milli> time_span = chrono::high_resolution_clock::now() - t1;
			s->log("It took " + transformTime(time_span.count()));

			s->log("#### Training classifier ####\n");
			t1 = chrono::high_resolution_clock::now();
			TrainClassifier(s);
			time_span = chrono::high_resolution_clock::now() - t1;
			s->log("It took " + transformTime(time_span.count()));

			int detectionCounter = 1;
			for (auto dp : detectorParams)
			{
				path PathToResult(s->generateResultPath() + string("/") + to_string(detectionCounter));
				create_directory(PathToResult);
				if (dp.useMax)
				{
					s->log("Detector Parameters (" + to_string(detectionCounter) + "):\n\tscale - " + to_string(dp.scale) + "\n\tMinimum Neighbours - " + to_string(dp.minNeighbours) + "\n\tMinimum detected object size - " + to_string(dp.minSize.height) + ";" + to_string(dp.minSize.width) + "\n\tMaximum detected object size - " + to_string(dp.maxSize.height) + ";" + to_string(dp.maxSize.width));
				}
				else
				{
					s->log("Detector Parameters (" + to_string(detectionCounter) + "):\n\tscale - " + to_string(dp.scale) + "\n\tMinimum Neighbours - " + to_string(dp.minNeighbours) + "\n\tMinimum detected object size - " + to_string(dp.minSize.height) + ";" + to_string(dp.minSize.width));
				}
				
				s->log("#### Testing classifier ####\n");
				t1 = chrono::high_resolution_clock::now();
				//TEST CONFIGURATION
				TestCampaign(s, dp, PathToResult.string());
				time_span = chrono::high_resolution_clock::now() - t1;
				s->log("It took " + transformTime(time_span.count()));
				detectionCounter++;
			}
		}
	}
	else
	{
		if (recreateInfoFiles)
		{
			CreateInfoFiles(false);
		}

		s->manualSetup();
		string message = "Do you want to create vec file";
		if (askUserForAcceptance(message))
		{
			CreateSamples(s);
		}

		message = "Do you want to train classifier";
		if (askUserForAcceptance(message))
		{
			TrainClassifier(s);
		}

		message = "Do you want to test classifier";
		if (askUserForAcceptance(message))
		{
			TrainClassifier(s);
		}
	}

	


}

using namespace std;