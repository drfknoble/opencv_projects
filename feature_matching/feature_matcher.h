#pragma once

#include <opencv2\opencv.hpp>

namespace fm {

	enum matcher {BF, FLANN};

	class feature_matcher
	{
	public:
		feature_matcher();
		~feature_matcher();

		const bool ORB(const cv::Mat &in1, const cv::Mat &in2, cv::Mat *out1, fm::matcher matcher = fm::BF);
		const bool BRISK(const cv::Mat &in1, const cv::Mat &in2, cv::Mat *out1, fm::matcher matcher = fm::BF);

	};

}
