#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdlib>

#include "CreateSamples.h"
#include "Constants.h"
#include "helper/helper.h"

using namespace std;
namespace fs = std::experimental::filesystem;

void CreateInfoFiles()
{
	string question = "Create positive samples info file?";
	if (askUserForAcceptance(question))
	{
		string commandPositive = ANNOTATION + string(" --annotations=") + string("/banana.info --images=") + PATH_TO_POSITIVE_SAMPLES;
		system(commandPositive.c_str());
	}

	question = "Create negative samples info file?";
	if (askUserForAcceptance(question))
	{
		fs::path Path(PATH_TO_NEGATIVE_SAMPLES);
		for (const auto& entry : fs::directory_iterator(Path))
		{
			fstream plik;
			plik.open("bg.info", ios::app);
			if (plik.good() == true)
			{
				plik << entry.path().string() + string("\n");
			}
			plik.close();
		}
	}
}

void CreateSamples() 
{
	string question = "Create samples vec file?";
	if (askUserForAcceptance(question))
	{
		string width;
		string height;
		int nsamples;
		cout << "Insert width for your samples: ";
		cin >> width;
		cout << "Inster height for your samples: ";
		cin >> height;
		//cout << "How many probes you want?: ";
		//cin >> nsamples;
		string command = SAMPLE_TOOL + string(" -vec train.vec -info banana.info -num 30 -w ") + width + string(" -h ") + height;
		cout << command << endl;
		system(command.c_str());
	}
}