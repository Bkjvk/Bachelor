#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdlib>

#include "CreateSample.h"
#include "Constants.h"
#include "helper.h"
#include "Setuper.h"

using namespace std;
namespace fs = std::experimental::filesystem;

void CreateInfoFile(string fileName, string pathToSamples, string additional = "")
{
		fstream file;
		file.open(fileName, ios::out);
		fs::path PathToImages(pathToSamples);
		for (const auto& picture : fs::directory_iterator(PathToImages))
		{
			file << pathToSamples << "/" << picture.path().filename().string() << additional << "\n";
		}
		file.close();
}

void CreateInfoFiles(bool automatic)
{
	fstream file;
	if (automatic)
	{
		CreateInfoFile("pos.info", PATH_TO_POSITIVE_SAMPLES, " 1 0 0 100 40");
		CreateInfoFile("neg.info", PATH_TO_NEGATIVE_SAMPLES);
	}
	else
	{
		string message = "Create positive samples info file?";
		if (askUserForAcceptance(message))
		{
			string commandPositive = ANNOTATION + string(" --annotations=") + string("/pos.info --images=") + PATH_TO_POSITIVE_SAMPLES;
			system(commandPositive.c_str());
		}

		message = "Create negative samples info file?";
		if (askUserForAcceptance(message))
		{
			CreateInfoFile("neg.info", PATH_TO_NEGATIVE_SAMPLES);
		}
		
	}
}

void CreateSamples(Setuper* s)
{
	system(s->generateSampleArgs().c_str());
}

void TrainClassifier(Setuper* s)
{
	system(s->generateTrainingArgs().c_str());
}