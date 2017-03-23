//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/*!
 * \file main.cc
 * \author Dr. Frazer K. Noble
 * \date 2017
 * \brief This program demonstrates how the Open Computer Vision (OpenCV) library can be used to detect a green-screen and replace it with a desired image.
 *
 * \section Description.
 *
 * \note Comments are written in Doxygen-compliant format (see \link https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html \endlink). Here, I have used Qt style (/ *! ...text... * /)
 */

#include "main.h" //! For DEFINE_x() and getpath()

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
DEFINE_string(b, "", "[file.type]");
/*!
* \brief gFlag command line parameter.
* \param o o is the output directory, which an image or video should be loaded to.
*/
DEFINE_string(o, "", "[dir]");
/*!
* \brief gFlag command line parameter.
* \param n n is the number of frames to step by, when viewing a video.
*/
DEFINE_int32(n, 1, "[1, 100]");
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

	std::string current_directory = ""; //! Current working directory of the executable.
	std::string input_directory = ""; //! The input directory.
	std::string output_directory = ""; //! The output directory.
	std::string file_name = "";//! The file name.
	std::string background = "";

	getpath(&current_directory);
	input_directory = current_directory + std::string("\\data\\input\\");
	output_directory = current_directory + std::string("\\data\\output\\");
	//file_name = "Video.mp4";
	background = std::string("background.jpg");

	int step_size = 1; //! The step size.
	bool debug = false; //! The debug flag.

	/*!
	 * Check the command line parameters to see if non-default values are used.
	 */

	gflags::ParseCommandLineFlags(&argc, &argv, true);

	if (FLAGS_i.compare("") != 0) { //! If input directory is provided, update default.
		input_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_i) << std::endl;
	}

	if (FLAGS_f.compare("") != 0) { //! If file name is provided, update default.
		file_name = FLAGS_f;
		//std::cout << std::string(FLAGS_f) << std::endl;
	}

	if (FLAGS_b.compare("") != 0) { //! If file name is provided, update default.
		background = FLAGS_b;
		//std::cout << std::string(FLAGS_b) << std::endl;
	}

	if (FLAGS_o.compare("") != 0) { //! If output directory is provided, update default.
		output_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_o) << std::endl;
	}

	if (!FLAGS_n == 1) { //! If step size is provided, update default.
		step_size = FLAGS_n;
		//std::cout << FLAGS_n << std::endl;
	}

	if (FLAGS_d) { //! If debug flag is set, update default.
		debug = true;
		//std::cout << FLAGS_d << std::endl;
	}

	gflags::ShutDownCommandLineFlags();

	if (debug) { //! If debug flag is set, display the input and output directories, file name, and step size.
		std::cout << "Input directory: " << input_directory << std::endl;
		std::cout << "Output directory: " << output_directory << std::endl;
		std::cout << "Filename: " << file_name << std::endl;
		std::cout << "Background: " << background << std::endl;
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

	//! Read in background image.
	cv::Mat mask = cv::imread(input_directory + background);
	if (mask.empty()) {
		std::cout << "Could not parse background file" << std::endl;
		return -1;
	}

	if (image) { //! If input is an image; run project::GreenScreen() once, display output, and wait for key press.

		cv::Mat input = cv::imread(input_directory + file_name);
		if (input.empty()) {
			std::cout << "Could not parse input file" << std::endl;
			return -1;
		}

		//! Create window
		cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);

		if (!input.empty()) {
			project::GreenScreen(input, mask, cv::Scalar(65, 10, 10), &input);
			cv::imshow(file_name, input);
		}

		char c = cv::waitKey(0);

	}
	else if (video) { //! If input is an video; run project::GreenScreen() continuously, display output, and wait for key press.

		cv::VideoCapture input(input_directory + file_name);

		if(!input.isOpened()) {
			std::cout << "Could not open input file" << std::endl;
			return -1;
		}

		input.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
		input.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

		//! Create window
		cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);

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
				input.release();
				break;
			}
		}
	}
	else { //! Input is a video capture device; run project::GreenScreen() continuously, display output, and wait for key press.

		cv::VideoCapture input(0); //! Get frames from the default video capture device.

		if (!input.isOpened()) {
			std::cout << "Could not open video capture device" << std::endl;
			return -1;
		}

		input.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
		input.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

		//! Create window
		cv::namedWindow("Green Screen", cv::WINDOW_AUTOSIZE);

		while (true) {

			cv::Mat frame;
			cv::Mat sml_frame;

			if (input.read(frame)) {

				cv::pyrDown(frame, sml_frame);
				project::GreenScreen(frame, mask, cv::Scalar(65, 10, 10), &frame);
				cv::imshow("Maksed Image", frame);
				cv::imshow("Green Screen", sml_frame);
			}

			char c = cv::waitKey(1);
			if (c == 27) {
				input.release();
				break;
			}
		}
	}

	cv::destroyAllWindows();

	return 0;
}

//#include <gflags\gflags.h>
//#include <string>
//#include <iostream>
//
//DEFINE_bool(debug, false, "");
//DEFINE_string(f, "", "");
//
//int main(int argc, char* argv[]) {
//
//	gflags::ParseCommandLineFlags(&argc, &argv, true);
//
//	if (FLAGS_debug) {
//		std::cout << std::string("Debug") << std::endl;
//	}
//	
//	if (FLAGS_f.compare("") != 0) {
//		std::cout << std::string(FLAGS_f) + "not rubbish" << std::endl;
//	}
//
//	gflags::ShutDownCommandLineFlags();
//
//	system("pause");
//
//	return 0;
//}