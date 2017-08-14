#include <opencv2\opencv.hpp>
#include <iostream>

#include "feature_detector.h"

int main(int argc, char* argv[]) {

	cv::Mat image = cv::imread("Image 1.jpg");

	if (image.empty()) {
		std::cout << "Could not open image." << std::endl;
		return -1;
	}

	cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);

	feature_detector detector;

	detector.BRISK(image, &image);

	cv::imshow("Image", image);

	cv::imwrite(cv::String("Out 1.jpg"), image);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;

}