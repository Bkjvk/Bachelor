#include <string>
#include <iostream>

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