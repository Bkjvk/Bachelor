#pragma once
#ifndef SETUPER_H
#define SETUPER_H
#include <string>
#include <fstream>

using namespace std;

static class Setuper {
	bool useSetup;
	string setupName;
	string posInfoFileName;
	string negInfoFileName;
	string classifier;
	unsigned int width;
	unsigned int height;
	unsigned int posProbes;
	unsigned int posProbesStages;
	unsigned int negProbes;
	unsigned int stages;
	fstream log_file;
public:
	Setuper();
	Setuper(bool, string, string, string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	void readNewSetuperParams(string fileName);
	void changeSetuperParams(bool, string, string, string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	void manualSetup();
	string generateTrainingArgs();
	string generateSampleArgs();
	string generateClassifierPath();
	string generateVecFilePath();
	string generateResultPath();
	void createSetupDirectories();
	void generateBlankTestPlan();
	void openLog();
	void closeLog();
	void log(string);
}setuper;

#endif
