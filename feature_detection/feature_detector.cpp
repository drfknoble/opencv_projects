#include "feature_detector.h"



feature_detector::feature_detector()
{
}


feature_detector::~feature_detector()
{
}

const bool feature_detector::ORB(const cv::Mat & in, cv::Mat * out)
{

	cv::Ptr<cv::ORB> detector = cv::ORB::create();

	std::vector<cv::KeyPoint> key_points;

	detector->detect(in, key_points);

	cv::drawKeypoints(in, key_points, *out, cv::Scalar(0, 0, 255));

	return true;
}

const bool feature_detector::BRISK(const cv::Mat & in, cv::Mat * out)
{

	cv::Ptr<cv::BRISK> detector = cv::BRISK::create();

	std::vector<cv::KeyPoint> key_points;

	detector->detect(in, key_points);

	cv::drawKeypoints(in, key_points, *out, cv::Scalar(0, 0, 255));

	return true;
}
