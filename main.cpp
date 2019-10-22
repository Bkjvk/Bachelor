#include <iostream>
#include <filesystem>
#include <string>

#include "CreateSamples.h"

using namespace std;

int main()
{
	CreateInfoFiles();
	CreateSamples();
	cout << "this is the end :(";
	getchar();
	return 0;
}