#include <iostream>
#include <string>

#include "src/CreateSample.h"
#include "src/detect.h"
#include "src/Constants.h"
#include "src/Setuper.h"
#include "src/helper.h"
#include "src/Controller.h"
#include "tools.h"

using namespace std;

int main()
{
	//controller(&setuper);
	//converter(PATH_TO_TEST_SAMPLES);
	//converter(PATH_TO_NEGATIVE_SAMPLES);
	//histogramEqalizer("Images/Other/histogram.jpg");
	singleDetection("Images/Positive/Positive8.jpg", "kaskada");
	getchar();
	return 0;
}