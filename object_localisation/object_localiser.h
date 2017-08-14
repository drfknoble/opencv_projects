#pragma once

#include <opencv2\opencv.hpp>

namespace ol {

	enum matcher {BF, FLANN};

	class object_localiser
	{
	public:
		object_localiser();
		~object_localiser();

		const bool ORB(const cv::Mat &in1, const cv::Mat &in2, cv::Mat *out1, ol::matcher matcher = ol::BF);
		const bool BRISK(const cv::Mat &in1, const cv::Mat &in2, cv::Mat *out1, ol::matcher matcher = ol::BF);

	};

}
