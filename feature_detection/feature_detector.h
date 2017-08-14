#pragma once
#include <opencv2\opencv.hpp>
#include <vector>

class feature_detector
{
public:
	feature_detector();
	~feature_detector();

	const bool ORB(const cv::Mat &in, cv::Mat *out);
	const bool BRISK(const cv::Mat &in, cv::Mat *out);

};

