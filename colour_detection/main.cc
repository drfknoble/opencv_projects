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
	cv::VideoCapture video(input_directory + file_name);

	cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Small " + file_name, cv::WINDOW_AUTOSIZE);

	int frame_count = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
	int current_frame = 0;

	cv::Mat bgr_red = cv::Mat(1, 1, CV_8UC3, { 0, 0, 255 });
	cv::Mat bgr_green = cv::Mat(1, 1, CV_8UC3, { 0, 255, 0 });
	cv::Mat bgr_blue = cv::Mat(1, 1, CV_8UC3, { 255, 0, 0 });

	cv::Mat hsv_red = cv::Mat(1, 1, CV_8UC3);
	cv::Mat hsv_green = cv::Mat(1, 1, CV_8UC3);
	cv::Mat hsv_blue = cv::Mat(1, 1, CV_8UC3);

	cv::cvtColor(bgr_blue, hsv_blue, cv::COLOR_BGR2HSV);
	std::cout << "BGR Blue to HSV: " << bgr_blue << ", " << hsv_blue << std::endl;

	cv::cvtColor(bgr_green, hsv_green, cv::COLOR_BGR2HSV);
	std::cout << "BGR Green to HSV: " << bgr_green << ", " << hsv_green << std::endl;

	cv::cvtColor(bgr_red, hsv_red, cv::COLOR_BGR2HSV);
	std::cout << "BGR Red to HSV: " << bgr_red << ", " << hsv_red << std::endl;

	while (true) {

		cv::Mat frame, sml_frame;
		std::stringstream ss;

		if (current_frame + step_size < frame_count) {
			if (video.read(frame)) {

				cv::pyrDown(frame, sml_frame);
				cv::imshow("Small " + file_name, sml_frame);

				cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0.0);

				project::DetectColour(frame, cv::Scalar(110, 25, 25), cv::Scalar(130, 255, 255), &frame);

				cv::imshow(file_name, frame);
				/*ss << output_directory << "frame_" << current_frame << ".png";
				std::cout << ss.str() << std::endl;
				cv::imwrite(ss.str(), frame);
				*/current_frame += step_size;
				video.set(cv::CAP_PROP_POS_FRAMES, current_frame);
			}
		}		

		char c = cv::waitKey(1);
		if (c == 27) {
			break;
		}
	}

	cv::destroyAllWindows();

	return 0;
}