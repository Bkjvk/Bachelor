#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::experimental::filesystem;

void converter(string src){
	fs::path Path(src);
	int counter = 0;
	for (const auto& entry : fs::directory_iterator(Path))
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