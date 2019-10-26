#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "Constants.h"
#include "Setuper.h"
#include "helper.h"

using namespace std;
namespace fs = std::experimental::filesystem;

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
	bool test[10] = { false, false, false, false, false, false, false, false, false, false };
	file.open(fileName, fstream::in);
	if (file.good())
	{
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
			cout << "print setup: \n";
			/*
			switch (parseKey(key)) 
			{
				case USESETUP:
					test[USESETUP] = 0;
					useSetup = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case SETUPNAME:
					test[SETUPNAME] = 0;
					setupName = read.substr(++equal);
					cout << "Setup Name:\t" << useSetup << endl;
					break;
				case POSINFOFILENAME:
					test[POSINFOFILENAME] = 0;
					posInfoFileName = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case NEGINFOFILENAME:
					test[NEGINFOFILENAME] = 0;
					negInfoFileName = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case CLASSIFIER:
					test[CLASSIFIER] = 0;
					classifier = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case WIDTH:
					test[WIDTH] = 0;
					width = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case HEIGHT:
					test[HEIGHT] = 0;
					height = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case POSPROBES:
					test[POSPROBES] = 0;
					posProbes = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case NEGPROBES:
					test[NEGPROBES] = 0;
					negProbes = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				case STAGES:
					test[STAGES] = 0;
					stages = stoi(read.substr(++equal));
					cout << "Use Setup:\t" << useSetup << endl;
					break;
				default:
					cout << "Did not found the symbol: " << key << endl;
					break;
			}
			*/
			cout << read << endl;
		}
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
	return "xd";
}
string Setuper::generateClassifierArgs()
{
	return "xd";
}
string Setuper::generateClassifierPath()
{
	return "xd";
}
string Setuper::generateVecFilePath()
{
	return "xd";
}
void Setuper::generateBlankTestPlan()
{
	fstream file;
	file.open("TestPlan", fstream::out);
	
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
	file << "stages=1 #Longer training but better results";
	file.close();
}