#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>
#include <conio.h>
#include <fstream>

#include "Summarizer.h"

using namespace std;
using namespace cv;
using namespace filesystem;

struct Summarize {
	int positive;
	int negative;
	int falsePositive;

	Summarize(): positive(0), negative(0), falsePositive(0) {};
};

void showImage(string path)
{
	Mat src = imread(path, CV_LOAD_IMAGE_COLOR);
	imshow("Image", src);
	waitKey(1);
}

void showData(string pos, string fpos, string neg)
{
	Mat text = Mat::zeros(Size(600, 160), CV_64FC1);
	putText(text, "positive" + pos, Point(0, 40), CV_FONT_NORMAL, 1, Scalar(255, 255));
	putText(text, "false positive" + fpos, Point(0, 80), CV_FONT_NORMAL, 1, Scalar(255, 255));
	putText(text, "negative" + neg, Point(0, 120), CV_FONT_NORMAL, 1, Scalar(255, 255));
	imshow("description", text);
	waitKey(1);
}

void judgePicture(string pathToPicture, Summarize *s)
{
	cout << pathToPicture << endl;

	int positive = 0, falsePositive = 0, negative = 0, keyPress;
	bool stop = false;

	showImage(pathToPicture);
	showData(to_string(positive), to_string(falsePositive), to_string(negative));

	Mat text = Mat::zeros(Size(600, 400), CV_64FC1);

	while (keyPress = _getch())
	{
		switch (keyPress)
		{
		case (int)'n': //next
			stop = true;
			break;
		case (int)'z': //positive
			positive++;
			break;
		case (int)'x': //falsepositive
			falsePositive++;
			break;
		case (int)'c': //negative
			negative++;
			break;
		case (int)'a': //-positive
			positive--;
			break;
		case (int)'s': //-falsenegative
			falsePositive--;
			break;
		case (int)'d': //-negative
			negative--;
			break;
		default:
			//ignore false keystrokes :)
			break;
		}

		showData(to_string(positive), to_string(falsePositive), to_string(negative));

		if (stop)
		{
			s->positive += positive;
			s->negative += negative;
			s->falsePositive += falsePositive;
			break;
		}
	}
}

void logToFile(Summarize* s, string path)
{
	fstream logFile;
	logFile.open("log", ios::in | ios::app);
	if (!logFile.good())
	{
		cout << "Some error appeared with logging service (summarizer), closing app :(\n";
		exit(-1);
	}

	logFile << path << "\n\tPositive: " << s->positive << "\n\tNegative: " << s->negative << "\n\tFalse positive: " << s->falsePositive << "\n";

	logFile.close();
}

void Summarizer()
{
	path pathToResults;
	cout << "Insert path to results: ";
	cin >> pathToResults;

	cout << "Keybinds\n\tz - add\t\ta - remove from positive count\n\tx - add\t\ts - remove from false positive counter\n\tc - add\t\td - remove from negative\n\tn - next picture\n";

	for (const auto& entry : directory_iterator(pathToResults))
	{
		cout << "Entering catalog: " << entry.path().filename().string() << endl;
		Summarize s;
		path subResults = path(pathToResults.string() + "\\" + entry.path().filename().string());
		for (const auto& entry : directory_iterator(subResults))
		{
			judgePicture(subResults.string() + "\\" + entry.path().filename().string(),&s);
		}
		cout << "Positives: " << to_string(s.positive) << "\nNegatives: " << to_string(s.negative) << "\nFalse Negatives: " << to_string(s.falsePositive) << endl;
		logToFile(&s, subResults.string());
	}
}