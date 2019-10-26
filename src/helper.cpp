#include <string>
#include <iostream>
#include <algorithm>

#include "helper.h"

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
		return 0;
	}
	else if (key == "setupname")
	{
		return 1;
	}
	else if (key == "posinfofilename")
	{
		return 2;
	}
	else if (key == "neginfofilename")
	{
		return 3;
	}
	else if (key == "classifier")
	{
		return 4;
	}
	else if (key == "width")
	{
		return 5;
	}
	else if (key == "height")
	{
		return 6;
	}
	else if (key == "posprobes")
	{
		return 7;
	}
	else if (key == "negprobes")
	{
		return 8;
	}
	else if (key == "stages")
	{
		return 9;
	}
	else
	{
		return -1;
	}
	return 0;
}