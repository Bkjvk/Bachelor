#include <iostream>
#include <string>
#include <conio.h>

#include "src/CreateSample.h"
#include "src/detect.h"
#include "src/Constants.h"
#include "src/Setuper.h"
#include "src/helper.h"
#include "src/Controller.h"
#include "tools.h"
#include "Summarizer.h"

using namespace std;

int main()
{
	char keyPress;
	string pathToImage;
	string pathToCascade;

	cout << "Welcome friendly-classifier application!\n";
	cout << "press:\n1\tTo start training the classifier\n2\tFor single picture detection!\n3\tTo summarize pictures!\n4\tGenerate example test plan\n0\tTo close the application\n";
	while (keyPress = _getch())
	{
		switch (keyPress)
		{
		case (int)'1':
			controller(&setuper);
			break;
		case (int)'2':
			cout << "Insert path to image: ";
			cin >> pathToImage;
			cout << "Insert path to cascade: ";
			cin >> pathToCascade;
			singleDetection(pathToImage, pathToCascade);
			break;
		case (int)'3':
			Summarizer();
			break;
		case (int)'4':
			setuper.generateBlankTestPlan();
			break;
		case (int)'0':
			return '0';
		default:
			break;
		}
		cout << "press:\n1\tTo start training the classifier\n2\tFor single picture detection!\n3\tTo summarize pictures!\n4\tGenerate example test plan\n0\tTo close the application\n";
	}
	return 0;
}
