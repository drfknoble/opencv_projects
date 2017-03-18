//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "main.h"

int main(int argc, char* argv[]) {

	std::string current_directory = "";
	std::string input_directory = "";
	std::string output_directory = "";
	std::string file_name = "";

	getpath(&current_directory);
	input_directory = current_directory + std::string("\\data\\input\\");
	output_directory = current_directory + std::string("\\data\\output\\");

	file_name = std::string("Video.mp4");

	int step_size = 1;
	bool debug = false;

	int r = 0;
	while ((r = GetOpt(argc, argv, "f:i:o:n:d")) != -1) {
		switch (r) {
		case 'f':
			file_name = optarg;
			break;
		case 'i':
			input_directory = optarg;
			break;
		case 'o':
			output_directory = optarg;
			break;
		case 'n':
			step_size = atoi(optarg);
			break;
		case 'd':
			debug = true;
			break;
		}
	}

	if (debug) {
		std::cout << "Input directory: " << input_directory << std::endl;
		std::cout << "Output directory: " << output_directory << std::endl;
		std::cout << "Filename: " << file_name << std::endl;
		std::cout << "Step size: " << step_size << std::endl;
	}

	std::cout << "File: " << input_directory + file_name << std::endl;

	//get file name and parse file type

	std::vector<std::string> token_vec = {};
	std::stringstream ss(file_name);
	std::string token;
	while (std::getline(ss, token, '.')) {
		token_vec.push_back(token);
	}
	
	//is the file type a video or an image
	bool video = false;
	bool image = false;

	if (token_vec[1].compare(".mp4") || token_vec[1].compare(".avi")) {
		video = true;
	}
	else if (token_vec[1].compare(".jpg") || token_vec[1].compare(".png")) {
		image = true;
	}
	else {
		std::cout << "Input  not a video (.mp4, .avi) or an image (.jpg, .png)" << std::endl;
		return -1;
	}
		
	cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);

	if (image) {

		cv::Mat input = cv::imread(input_directory + file_name);

		if (!input.empty()) {
			cv::imshow(file_name, input);
		}

	}
	else if (video) {

		//cv::VideoCapture input(input_directory + file_name);
		cv::VideoCapture input(0);
		input.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
		input.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

		while (true) {

			cv::Mat frame;
			cv::Mat sml_frame;

			if (input.read(frame)) {

				cv::pyrDown(frame, sml_frame);
				project::GreenScreen(frame, cv::Scalar(60, 10, 10), &frame);
				cv::imshow(std::string("Maksed ") + file_name, frame);
				cv::imshow(file_name, sml_frame);
			}

			char c = cv::waitKey(1);
			if (c == 27) {
				break;
			}
		}
	}

	cv::destroyAllWindows();

	return 0;
}