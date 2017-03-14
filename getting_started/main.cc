#include <opencv2\opencv.hpp>

int main(int argc, char* argv[]) {

	cv::VideoCapture camera(0);

	cv::namedWindow("Hello World", cv::WINDOW_AUTOSIZE);

	while (true) {

		cv::Mat image;

		camera >> image;

		if (!image.empty()) {
			cv::imshow("Hello World", image);
		}

		char c = cv::waitKey(1);
		if (c == 27) {
			break;
		}
	}

	cv::destroyAllWindows();

	return 0;
}