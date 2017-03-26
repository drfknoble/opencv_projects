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
* \brief This program demonstrates how the Open Computer Vision (OpenCV) library can be used to extract a frame from a video and save it as an image.
*
* \section Description.
*
* \note Comments are written in Doxygen-compliant format (see \link https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html \endlink). Here, I have used Qt style (/ *! ...text... * /)
*/

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
* \param b b is the background image's file name.
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
		std::cout << "Step size: " << step_size << std::endl;
	}

	std::cout << "File: " << input_directory + file_name << std::endl;
	cv::VideoCapture video(input_directory + file_name);

	cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);

	int frame_count = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
	int current_frame = 0;

	while (true) {

		cv::Mat frame;
		std::stringstream ss;

		if (current_frame + step_size < frame_count) {
			if (video.read(frame)) {
				cv::imshow(file_name, frame);
				ss << output_directory << "frame_" << current_frame << ".png";
				std::cout << ss.str() << std::endl;
				cv::imwrite(ss.str(), frame);
				current_frame += step_size;
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