#pragma once

#include <iostream>

#include <opencv2\opencv.hpp>

namespace un {

	class undistortor
	{
	private:

		cv::Mat camera_matrix, distortion_coefficients;
		cv::Mat map_1, map_2;

	public:
		undistortor();
		~undistortor();

		const bool fix(const cv::Mat &in1, cv::Mat *out1);
	};

}