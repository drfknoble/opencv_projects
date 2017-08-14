#include <opencv2\opencv.hpp>
#include <iostream>

#include "feature_matcher.h"

int main(int argc, char* argv[]) {

	cv::Mat image_1 = cv::imread("Picture 2.jpg");
	cv::Mat image_2 = cv::imread("Picture 3.jpg");

	if (image_1.empty() || image_2.empty()) {
		std::cout << "Could not open image/s." << std::endl;
		return -1;
	}

	cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);

	fm::feature_matcher matcher;
	cv::Mat output_image;

	matcher.BRISK(image_1, image_2, &output_image);

	cv::imshow("Image", output_image);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;

}