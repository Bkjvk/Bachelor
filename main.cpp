#include <iostream>
#include <string>

#include "src/CreateSample.h"
#include "src/detect.h"
#include "src/Constants.h"
#include "src/Setuper.h"
#include "src/helper.h"
#include "src/Controller.h"

using namespace std;

int main()
{
	controller(&setuper);
	getchar();
	return 0;
}