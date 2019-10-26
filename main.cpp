#include <iostream>
#include <string>

#include "src/CreateSample.h"
#include "src/detect.h"
#include "src/Constants.h"
#include "src/Setuper.h"

using namespace std;

int main()
{
	//opencv_createsamples.exe -vec train.vec -w 36 -h 24
	//CreateInfoFiles();
	//CreateSamples();
	//TrainClassifier();
	//TestCampaign("D:/programowanie/Projekt/bachelor/Images/Feed/cascade.xml");
	//detectAndDisplay(PATH_TO_TEST_SAMPLES + string("/Test4.jpg"), string("D:/programowanie/Projekt/bachelor/Images/Feed/cascade.xml"));
	//cout << "this is the end :(";

	setuper.generateBlankTestPlan();
	setuper.readNewSetuperParams("TestPlan");

	getchar();
	return 0;
}