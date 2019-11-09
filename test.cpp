#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;
using namespace filesystem;

void converter(string src){
	path Path(src);
	int counter = 0;
	for (const auto& entry : directory_iterator(Path))
	{
		Mat image = imread(entry.path().string(), CV_LOAD_IMAGE_COLOR);   // Read the file
		if (!image.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image\n";
			exit(-1);
		}
		imwrite(src + to_string(++counter) + ".jpg", image);
	}
}