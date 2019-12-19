#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "Constants.h"
#include "Setuper.h"
#include "helper.h"

using namespace std;
using namespace filesystem;

Logger::Logger()
{
	logFile.open("log", ios::in | ios::app);
	if (!logFile.good())
	{
		cout << "Some error appeared with logging service, closing app :(\n";
		exit(-1);
	}
}

Logger::~Logger()
{
	logFile.close();
}

void Logger::log(string message)
{
	logFile << message << '\n';
}

Setuper::Setuper()
{
	useSetup = false;
	setupName = "";
	posInfoFileName = "";
	negInfoFileName = "";
	classifier ="";
	width = 0;
	height = 0;
	posProbes = 0;
	negProbes = 0;
	stages = 0;
}

Setuper::Setuper(bool _useSetup, string _setupName, string _posInfoFileName, string _negInfoFileName, string _classifier, unsigned int _width, unsigned int _height, unsigned int _posProbes, unsigned int _negProbes, unsigned int _stages)
{
	useSetup = _useSetup;
	setupName = _setupName;
	posInfoFileName = _posInfoFileName;
	negInfoFileName = _negInfoFileName;
	classifier = _classifier;
	width = _width;
	height = _height;
	posProbes = _posProbes;
	negProbes = _negProbes;
	stages = _stages;
}

void Setuper::readNewSetuperParams(string fileName)
{
	fstream file;
	string read;
	bool test[11] = { false, false, false, false, false, false, false, false, false, false, false };
	file.open(string(PATH_TO_TEST_PLANS) + "/" + fileName, fstream::in);
	if (file.good())
	{
		logger.log("print setup: ");
		while (file >> read)
		{
			//skip comments
			if (read[0] == '#')
			{
				char clear;
				while (file.get(clear)) { if (clear == '\n') { break; } }
				continue;
			}

			//find equation mark
			int equal = 0;
			for (; equal < read.length() && read[equal] != '='; equal++);
			if (equal <= 0 || equal >= read.length())
			{
				cout << "[ERROR] either you forggot equation mark or forggot insert value!\n";
				exit(-1);
			}
			//parse value
			string key = read.substr(0, equal);
			switch (parseKey(key)) 
			{
				case USESETUP:
					test[USESETUP] = 1;
					useSetup = stoi(read.substr(++equal));
					logger.log("Use Setup:\t\t" + to_string(useSetup));
					break;
				case SETUPNAME:
					test[SETUPNAME] = 1;
					setupName = read.substr(++equal);
					createSetupDirectories();
					logger.log("Setup Name:\t\t" + setupName);
					break;
				case POSINFOFILENAME:
					test[POSINFOFILENAME] = 1;
					posInfoFileName = read.substr(++equal) + ".info";
					logger.log("Pos info file name:\t" + posInfoFileName);
					break;
				case NEGINFOFILENAME:
					test[NEGINFOFILENAME] = 1;
					negInfoFileName = read.substr(++equal) + ".info";
					logger.log("Neg info file name:\t" + negInfoFileName);
					break;
				case CLASSIFIER:
					test[CLASSIFIER] = 1;
					classifier = read.substr(++equal);
					logger.log("Classifier:\t\t" + classifier);
					break;
				case WIDTH:
					test[WIDTH] = 1;
					width = stoi(read.substr(++equal));
					logger.log("Width:\t\t\t" + to_string(width));
					break;
				case HEIGHT:
					test[HEIGHT] = 1;
					height = stoi(read.substr(++equal));
					logger.log("Height:\t\t\t" + to_string(height));
					break;
				case POSPROBES:
					test[POSPROBES] = 1;
					posProbes = stoi(read.substr(++equal));
					logger.log("Positive Probes:\t" + to_string(posProbes));
					break;
				case NEGPROBES:
					test[NEGPROBES] = 1;
					negProbes = stoi(read.substr(++equal));
					logger.log("Negative Probes:\t" + to_string(negProbes));
					break;
				case STAGES:
					test[STAGES] = 1;
					stages = stoi(read.substr(++equal));
					logger.log("Stages:\t\t\t" + to_string(stages));
					break;
				case POSPROBESSTAGES:
					test[POSPROBESSTAGES] = 1;
					posProbesStages = stoi(read.substr(++equal));
					logger.log("Positive Samples for Training:\t\t\t" + to_string(posProbesStages));
					break;
				default:
					logger.log("Did not found the symbol: " + key);
					break;
			}
		}
		for (auto x : test)
		{
			if (!x)
			{
				cout << "Some setting were lacking program will shut down";
				exit(-1);
			}
		}
		logger.log("Generate Training args: " + generateTrainingArgs());
		logger.log("Generate Sample args: " + generateSampleArgs());
	}
	else
	{
		logger.log("Couldn't read test plan :" + string(PATH_TO_TEST_PLANS) + "/" + fileName);
	}
	file.close();
}

void Setuper::changeSetuperParams(bool _useSetup, string _setupName, string _posInfoFileName, string _negInfoFileName, string _classifier, unsigned int _width, unsigned int _height, unsigned int _posProbes, unsigned int _negProbes, unsigned int _stages)
{
	useSetup = _useSetup;
	setupName = _setupName;
	posInfoFileName = _posInfoFileName;
	negInfoFileName = _negInfoFileName;
	classifier = _classifier;
	width = _width;
	height = _height;
	posProbes = _posProbes;
	negProbes = _negProbes;
	stages = _stages;
}

string Setuper::generateTrainingArgs()
{
	return TRAIN_TOOL + string(" -data ") + generateClassifierPath() + " -vec " + generateVecFilePath() + " -bg neg.info -numPos " + to_string(posProbesStages) + " -numNeg " + to_string(negProbes) + " -numStages " + to_string(stages) + " -w " + to_string(width) + " -h " + to_string(height);
	//return TRAIN_TOOL + string(" -data ") + generateClassifierPath() + " -vec " + generateVecFilePath() + " -bg neg.info -numPos " + to_string(posProbesStages) + " -numNeg " + to_string(negProbes) + " -w " + to_string(width) + " -h " + to_string(height) + " -numStages " + to_string(stages);
}

string Setuper::generateSampleArgs()
{
	return string(SAMPLE_TOOL) + " -vec " + generateVecFilePath() + " -info " + posInfoFileName + " -bg neg.info" + " -num " + to_string(posProbes) +" -w " + to_string(width) + " -h " + to_string(height);
}


string Setuper::generateClassifierPath()
{
	return string(PATH_TO_TRAINED_CLASSIFIERS) + "/" + setupName;
}

string Setuper::generateVecFilePath()
{
	return setupName + ".vec";
}

string Setuper::generateResultPath()
{
	return string(PATH_TO_TEST_RESULT) + "/" + setupName;
}

void Setuper::createSetupDirectories()
{
	int i = 0;
	path Path(PATH_TO_TRAINED_CLASSIFIERS + string("/") + setupName);
	if (exists(Path))
	{
		do
		{
			Path = PATH_TO_TRAINED_CLASSIFIERS + string("/") + setupName + to_string(++i);
		} while (exists(Path));
		setupName = setupName + to_string(i);
		logger.log("[WARN] following setup name already exist new name: " + setupName);
	}
	create_directory(Path);
	Path = PATH_TO_TEST_RESULT + string("/") + setupName;
	create_directory(Path);
}

void Setuper::generateBlankTestPlan()
{
	fstream file;
	file.open("Images/TestPlans/testplans", fstream::out);
	
	file << "#Everything after # will be ignored \n";
	file << "#variable names are case insensitive\n";
	file << "setupName=name\n";
	file << "useSetup=0 #1 - true, 0 - false\n";
	file << "posInfoFileName=pos #.info will be added in the end automatically\n";
	file << "negInfoFileName=neg #.info will be added in the end automatically\n";
	file << "classifier=HAAR #or LBP\n";
	file << "width=36\n";
	file << "height=24\n";
	file << "posProbes=50\n";
	file << "negProbes=100\n";
	file << "posProbesStages=500\n";
	file << "stages=1 #Longer training but better results";
	file.close();
}

void Setuper::manualSetup()
{
	cout << "If you see [any] you can type anything and hit enter if you see [num] the value have to be non negative integer, if you do not follow instructions, the program will crash" << endl;
	cout << "Inser name of your setup [any]: ";
	cin >> setupName;
	cout << "Insert name of info file containing positive images info (.info added automaticaly) [any]: ";
	cin >> posInfoFileName;
	posInfoFileName += ".info";
	cout << "Insert name of info file containing negative images info (.info added automaticaly) [any]:  ";
	cin >> negInfoFileName;
	negInfoFileName += ".info";
	cout << "Inser the name of classivier [HAAR / LBP]: ";
	cin >> classifier;
	cout << "Insert width for your samples [num]: ";
	cin >> width;
	cout << "Inster height for your samples [num]: ";
	cin >> height;
	cout << "How many probes you want? [num]: ";
	cin >> posProbes;
	cout << "How many positive probes for classifier training? [num]: ";
	cin >> posProbesStages;
	cout << "stages? [num]: ";
	cin >> stages;
}

void Setuper::log(string message)
{
	logger.log(message);
}

unsigned int Setuper::getHeight()
{
	return height;
}
unsigned int Setuper::getWidth()
{
	return width;
}