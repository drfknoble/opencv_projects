//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <gflags/gflags.h>
#include "main.h"

DEFINE_string(i, "", "[dir]");
DEFINE_string(f, "", "[file.type]");
DEFINE_string(o, "", "[dir]");
DEFINE_int32(n, 1, "[1, 100]");
DEFINE_bool(d, false, "[true, false]");

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

	//int r = 0;
	//while ((r = GetOpt(argc, argv, "f:i:o:n:d")) != -1) {
	//	switch (r) {
	//	case 'f':
	//		file_name = optarg;
	//		break;
	//	case 'i':
	//		input_directory = optarg;
	//		break;
	//	case 'o':
	//		output_directory = optarg;
	//		break;
	//	case 'n':
	//		step_size = atoi(optarg);
	//		break;
	//	case 'd':
	//		debug = true;
	//		break;
	//	}
	//}

	if (FLAGS_i.compare("")) {
		input_directory = FLAGS_i;
		std::cout << FLAGS_i << std::endl;
	}

	if (FLAGS_f.compare("")) {
		file_name = FLAGS_f;
		std::cout << FLAGS_f << std::endl;
	}

	if (FLAGS_o.compare("")) {
		output_directory = FLAGS_i;
		std::cout << FLAGS_o << std::endl;
	}

	if (!FLAGS_n == 1) {
		step_size = FLAGS_n;
		std::cout << FLAGS_n << std::endl;
	}

	if (FLAGS_d) {
		debug = true;
		std::cout << FLAGS_d << std::endl;
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

	cv::Mat mask = cv::imread(input_directory + "mask_gray.jpg");

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
				project::GreenScreen(frame, mask, cv::Scalar(65, 10, 10), &frame);
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