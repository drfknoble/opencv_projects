#include "undistortor.h"



un::undistortor::undistortor()
{

	std::string setting_file = "out_camera_data.xml";
	cv::FileStorage fs;
	fs.open(setting_file, cv::FileStorage::READ);
	if (!fs.isOpened()) {
		std::cout << "Could not open file." << std::endl;
	}

	fs["camera_matrix"] >> camera_matrix;
	fs["distortion_coefficients"] >> distortion_coefficients;

	fs.release();

	cv::initUndistortRectifyMap(camera_matrix, distortion_coefficients, cv::Mat(), camera_matrix, cv::Size(640, 480), CV_32FC1, map_1, map_2);

}


un::undistortor::~undistortor()
{
}


const bool un::undistortor::fix(const cv::Mat & in1, cv::Mat * out1)
{
	
	cv::remap(in1, *out1, map_1, map_2, cv::INTER_LINEAR);
	
	return false;
}
