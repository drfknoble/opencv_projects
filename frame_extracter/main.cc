//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "main.h"

int main(int argc, char* argv[]) {
	
	std::string current_directory = GetPath();

	std::string input_directory = current_directory.append("\\data\\input\\");
	std::string output_directory = current_directory.append("\\data\\output\\");
	
	int step_size = 10;

	int r = 0;
	while ((r = GetOpt(argc, argv, "i:o:n:")) != -1) {
		switch (r) {
		case 'i':
			input_directory = optarg;
			break;
		case 'o':
			output_directory = optarg;
			break;
		case 'n':
			step_size = atoi(optarg);
			break;
		}
	}
	
	std::string file_name = input_directory.append("Video.mp4");

	cv::VideoCapture camera(file_name);

	cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

	while (true) {

		cv::Mat image;

		camera >> image;

		if (!image.empty()) {
			cv::imshow("Video", image);
		}

		char c = cv::waitKey(30);
		if (c == 27) {
			break;
		}
	}

	cv::destroyAllWindows();

	return 0;
}