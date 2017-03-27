//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "main.h"

/*!
* \brief gFlag command line parameter.
* \param i i is the input directory, which an image or video should be loaded from.
*/
DEFINE_string(i, "", "[dir]");
/*!
* \brief gFlag command line parameter.
* \param f f is the image's or video's file name.
*/
DEFINE_string(f, "", "[file.type]");
/*!
* \brief gFlag command line parameter.
* \param o o is the output directory, which an image or video should be loaded to.
*/
DEFINE_string(o, "", "[dir]");
/*!
* \brief gFlag command line parameter.
* \param d d is the debug flag; when set, it displays additional information.
*/
DEFINE_int32(n, 1, "[0:MAX_FRAME-1]");
/*!
* \brief gFlag command line parameter.
* \param d d is the debug flag; when set, it displays additional information.
*/
DEFINE_bool(d, false, "[true, false]");

/*
* \brief Main entry point for the program.
* \param argc is the number of command line parameters provided.
* \param argv is the string of command line parameters provided.
* \return Returns 0 on success; -1 on failure.
*/
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
	
	gflags::ParseCommandLineFlags(&argc, &argv, true);

	if (FLAGS_i.compare("") != 0) { //! If input directory is provided, update default.
		input_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_i) << std::endl;
	}

	if (FLAGS_f.compare("") != 0) { //! If file name is provided, update default.
		file_name = FLAGS_f;
		//std::cout << std::string(FLAGS_f) << std::endl;
	}

	if (FLAGS_o.compare("") != 0) { //! If output directory is provided, update default.
		output_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_o) << std::endl;
	}

	if (FLAGS_n != 1) { //! If output directory is provided, update default.
		step_size = FLAGS_n;
		//std::cout << std::string(FLAGS_o) << std::endl;
	}

	if (FLAGS_d) { //! If debug flag is set, update default.
		debug = true;
		//std::cout << FLAGS_d << std::endl;
	}

	gflags::ShutDownCommandLineFlags();
	
	if (debug) {
		std::cout << "Input directory: " << input_directory << std::endl;
		std::cout << "Output directory: " << output_directory << std::endl;
		std::cout << "Filename: " << file_name << std::endl;
		std::cout << "Step size: " << step_size << std::endl;
	}

	bool video = false; //! Video flag.
	bool image = false; //! Image flag.

	if (file_name.compare("") != 0) { //! If a file name is provided; parse it to see what its file type is.

		std::cout << "File: " << input_directory + file_name << std::endl;

		//! Split the file name and its type. 
		std::vector<std::string> token_vec = {};
		std::stringstream ss(file_name);
		std::string token;

		while (std::getline(ss, token, '.')) {
			token_vec.push_back(token);
		}

		try {
			//test; it'll throw an exception if not able to parse a file suffix.
			std::string suffix = token_vec.at(1);

			//! Check to see if the file type corresponds to a video or an image.
			if ((suffix.compare("mp4") == 0) || (suffix.compare("avi") == 0)) {
				video = true;
			}
			else if ((suffix.compare("jpg") == 0) || (suffix.compare("png") == 0)) {
				image = true;
			}
			else {
				std::cout << "Input  not a video (.mp4, .avi) or an image (.jpg, .png)" << std::endl;
				return -1;
			}

		}
		catch (const std::exception& ex) {
			std::cerr << "Could not parse file name: " << ex.what() << std::endl;
			return -1; //!Should break 
		}

	}

	std::cout << "File: " << input_directory + file_name << std::endl;

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

	if (image) {

		cv::Mat input = cv::imread(input_directory + file_name);
		if (input.empty()) {
			std::cout << "Could not parse input file" << std::endl;
			return -1;
		}

		//! Create window
		cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);
		cv::namedWindow("Small " + file_name, cv::WINDOW_AUTOSIZE);

		if (!input.empty()) {
			cv::resize(input, input, cv::Size(1280, 720));

			cv::Mat original = input.clone();
			cv::pyrDown(original, original);
			cv::imshow("Small " + file_name, original);

			project::DetectColour(input, cv::Scalar(110, 25, 25), cv::Scalar(130, 255, 255), &input);
			cv::imshow(file_name, input);
		}

		cv::waitKey(0);

	} else{

		cv::VideoCapture input(input_directory + file_name);

		if (!input.isOpened()) {
			std::cout << "Could not open input file" << std::endl;
			return -1;
		}

		input.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
		input.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

		int frame_count = static_cast<int>(input.get(cv::CAP_PROP_FRAME_COUNT));
		int current_frame = 0;

		cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);
		cv::namedWindow("Small " + file_name, cv::WINDOW_AUTOSIZE);

		while (true) {

			cv::Mat frame, sml_frame;
			std::stringstream ss;

			if (current_frame + step_size < frame_count) {
				if (input.read(frame)) {

					cv::pyrDown(frame, sml_frame);
					cv::imshow("Small " + file_name, sml_frame);

					cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0.0);

					project::DetectColour(frame, cv::Scalar(110, 25, 25), cv::Scalar(130, 255, 255), &frame);

					cv::imshow(file_name, frame);
					/*ss << output_directory << "frame_" << current_frame << ".png";
					std::cout << ss.str() << std::endl;
					cv::imwrite(ss.str(), frame);
					*/
					current_frame += step_size;
					input.set(cv::CAP_PROP_POS_FRAMES, current_frame);
				}
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