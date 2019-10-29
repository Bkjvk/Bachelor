#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>

#include "Controller.h"
#include "Setuper.h"
#include "helper.h"
#include "Constants.h"
#include "CreateSample.h"
#include "detect.h"

using namespace std;
namespace fs = std::experimental::filesystem;

void controller(Setuper* s)
{
	string message = "Do you want to recreate info files? ";
	bool recreateInfoFiles = askUserForAcceptance(message);
	message = "Do you want to use test plans";
	if (askUserForAcceptance(message))
	{
		if (recreateInfoFiles)
		{
			CreateInfoFiles(true);
		}
		fs::path Path(PATH_TO_TEST_PLANS);
		for (const auto& entry : fs::directory_iterator(Path))
		{
			s->log("#### Reading new setup data ####\n");
			s->readNewSetuperParams(entry.path().filename().string());

			s->log("#### Creating samples ####\n");
			chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
			CreateSamples(s);
			chrono::duration<double, std::milli> time_span = chrono::high_resolution_clock::now() - t1;
			s->log("It took " + to_string(time_span.count()) + " seconds.");

			s->log("#### Training classifier ####\n");
			t1 = chrono::high_resolution_clock::now();
			TrainClassifier(s);
			time_span = chrono::high_resolution_clock::now() - t1;
			s->log("It took " + to_string(time_span.count()) + " seconds.");

			s->log("#### Testing classifier ####\n");
			t1 = chrono::high_resolution_clock::now();
			TestCampaign(s);
			time_span = chrono::high_resolution_clock::now() - t1;
			s->log("It took " + to_string(time_span.count()) + " seconds.");
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