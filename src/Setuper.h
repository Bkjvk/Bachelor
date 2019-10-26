#pragma once
#ifndef SETUPER_H
#define SETUPER_H
#include <string>

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
	unsigned int negProbes;
	unsigned int stages;
public:
	Setuper();
	Setuper(bool, string, string, string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

	void readNewSetuperParams(string fileName);
	void changeSetuperParams(bool, string, string, string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	string generateTrainingArgs();
	string generateClassifierArgs();
	string generateClassifierPath();
	string generateVecFilePath();
	void generateBlankTestPlan();

}setuper;

#endif
