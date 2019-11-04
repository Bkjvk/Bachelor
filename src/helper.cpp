#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "helper.h"
#include "Constants.h"
#include "Setuper.h"

namespace fs = std::experimental::filesystem;
using namespace std;

bool parseAnswer(char answer) {
	switch (answer) 
	{
	case 'y': case 'Y': case 'n': case 'N': return false;
	default:
		cout << "Wrong character, try again!\n";
		return true;
	}
}

bool askUserForAcceptance(string message)
{
	char answer;
	do {
		cout << "Do you want to " << message << " (y/n): ";
		cin >> answer;
	} while (parseAnswer(answer));

	if (answer == 'y' || answer == 'Y') return true;
	else return false;
}

int parseKey(string key)
{
	for_each(key.begin(), key.end(), [](char& c) {
		c = tolower(c);
		});
	if (key == "usesetup")
	{
		return USESETUP;
	}
	else if (key == "setupname")
	{
		return SETUPNAME;
	}
	else if (key == "posinfofilename")
	{
		return POSINFOFILENAME;
	}
	else if (key == "neginfofilename")
	{
		return NEGINFOFILENAME;
	}
	else if (key == "classifier")
	{
		return CLASSIFIER;
	}
	else if (key == "width")
	{
		return WIDTH;
	}
	else if (key == "height")
	{
		return HEIGHT;
	}
	else if (key == "posprobes")
	{
		return POSPROBES;
	}
	else if (key == "negprobes")
	{
		return NEGPROBES;
	}
	else if (key == "stages")
	{
		return STAGES;
	}
	else if (key == "posprobesstages")
	{
		return POSPROBESSTAGES;
	}
	else
	{
		return -1;
	}
	return 0;
}
