#include <iostream>

#include <opencv2\opencv.hpp>

#include "undistortor.h"

int main(int argc, char* argv[]) {

	cv::VideoCapture camera;

	camera.open(0);
	if (!camera.isOpened()) {
		std::cout << "Could not open camera." << std::endl;
		return -1;
	}

	cv::namedWindow("Frame", CV_WINDOW_AUTOSIZE);

	cv::Mat frame;
	
	un::undistortor undistortor;

	while (true) {

		camera >> frame;
		if (!frame.empty()) {
			undistortor.fix(frame, &frame);
			cv::imshow("Frame", frame);
		}

		char c;
		c = cv::waitKey(1);
		if (c == 27) {
			break;
		}

	}

	cv::destroyAllWindows();

	camera.release();

	return 0;
}