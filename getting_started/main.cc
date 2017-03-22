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
* \brief This program demonstrates how the Open Computer Vision (OpenCV) library can be used.
*
* \section Description.
*
* \note Comments are written in Doxygen-compliant format (see \link https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html \endlink). Here, I have used Qt style (/ *! ...text... * /)
*/

#include "main.h"

DEFINE_bool(d, false, "[true/false]");

/*
* \brief Main entry point for the program.
* \param argc is the number of command line parameters provided.
* \param argv is the string of command line parameters provided.
* \return Returns 0 on success; -1 on failure.
*/
int main(int argc, char* argv[]) {

	gflags::ParseCommandLineFlags(&argc, &argv, true); //! Use gflags to parse the command line.

	bool debug = false;

	if (FLAGS_d) { //! If --d is set in the command line, set debug.
		debug = true;
	}

	cv::VideoCapture camera(0); //! Creates a cv::VideoCapture object, which opens the default video capture device, e.g. a USB web camera.

	cv::namedWindow("Hello World", cv::WINDOW_AUTOSIZE); //! Creates a cv::namedWindow, which is used to display images in.

	while (true) {

		cv::Mat image; //! Create a cv::Mat object to hold an image.

		camera >> image; //! Get an image from camera.

		if (!image.empty()) { //! If the image is non-zero, then display it in the window.
			cv::imshow("Hello World", image);
		}

		char c = cv::waitKey(1); //! Wait 1 ms to see if the 'Esc' key is pressed.
		if (c == 27) {
			break;
		}
	}

	//! Close program; release resources.
	cv::destroyAllWindows(); 
	camera.release();

	return 0;
}