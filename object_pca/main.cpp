#include <opencv2\opencv.hpp>
#include <iostream>

#include "object_localiser.h"
#include "pca_analyser.h"

int main(int argc, char* argv[]) {

	cv::Mat image_1 = cv::imread("Picture 1.jpg");
	cv::Mat image_2 = cv::imread("Picture 3.jpg");

	if (image_1.empty() || image_2.empty()) {
		std::cout << "Could not open image/s." << std::endl;
		return -1;
	}

	cv::resize(image_1, image_1, cv::Size(), 0.5, 0.5);
	cv::resize(image_2, image_2, cv::Size(), 0.5, 0.5);

	cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);

	ol::object_localiser localiser;
	cv::Mat output_image, roi;

	localiser.BRISK(image_1, image_2, &output_image, &roi);

	cv::imshow("Image", output_image);

	cv::imwrite(cv::String("Out 1.jpg"), output_image);
	
	cv::namedWindow("PCA", CV_WINDOW_AUTOSIZE);

	pc::pca_analyser analyser;
	cv::Mat pca;

	analyser.compute(roi, &pca);

	cv::imshow("PCA", pca);

	cv::imwrite(cv::String("Out 2.jpg"), roi);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;

}