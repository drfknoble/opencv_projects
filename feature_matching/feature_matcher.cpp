#include "feature_matcher.h"



fm::feature_matcher::feature_matcher()
{
}


fm::feature_matcher::~feature_matcher()
{
}

const bool fm::feature_matcher::ORB(const cv::Mat & in1, const cv::Mat & in2, cv::Mat * out1, fm::matcher matcher)
{

	cv::Ptr<cv::ORB> detector = cv::ORB::create();

	std::vector<cv::KeyPoint> key_points1, key_points2;
	cv::Mat descriptors1, descriptors2;

	detector->detectAndCompute(in1, cv::Mat(), key_points1, descriptors1);
	detector->detectAndCompute(in2, cv::Mat(), key_points2, descriptors2);

	switch (matcher) {
	case fm::BF:
		
		cv::BFMatcher matcher(cv::NORM_HAMMING);

		std::vector<cv::DMatch> matches;
		matcher.match(descriptors1, descriptors2, matches);

		double min_dist = 100, max_dist = 0;

		for (int i = 0; i < descriptors1.rows; i++) {
			double dist = matches[i].distance;
			if (dist > max_dist) {
				max_dist = dist;
			}
			if (dist < min_dist) {
				min_dist = dist;
			}
		}

		std::vector<cv::DMatch> good_matches;

		for (int i = 0; i < descriptors1.rows; i++) {

			if (matches[i].distance <= 0.8 * max_dist) {

				good_matches.push_back(matches[i]);
			}

		}

		cv::drawMatches(in1, key_points1, in2, key_points2, good_matches, *out1);

		break;
	}

	return false;
}

const bool fm::feature_matcher::BRISK(const cv::Mat & in1, const cv::Mat & in2, cv::Mat * out1, fm::matcher matcher)
{

	cv::Ptr<cv::BRISK> detector = cv::BRISK::create();

	std::vector<cv::KeyPoint> key_points1, key_points2;
	cv::Mat descriptors1, descriptors2;

	detector->detectAndCompute(in1, cv::Mat(), key_points1, descriptors1);
	detector->detectAndCompute(in2, cv::Mat(), key_points2, descriptors2);

	switch (matcher) {
	case fm::BF:

		cv::BFMatcher matcher(cv::NORM_HAMMING);

		std::vector<cv::DMatch> matches;
		matcher.match(descriptors1, descriptors2, matches);

		double min_dist = 100, max_dist = 0;

		for (int i = 0; i < descriptors1.rows; i++) {
			double dist = matches[i].distance;
			if (dist > max_dist) {
				max_dist = dist;
			}
			if (dist < min_dist) {
				min_dist = dist;
			}
		}

		std::vector<cv::DMatch> good_matches;

		for (int i = 0; i < descriptors1.rows; i++) {

			if (matches[i].distance <= 0.8 * max_dist) {

				good_matches.push_back(matches[i]);
			}

		}

		cv::drawMatches(in1, key_points1, in2, key_points2, good_matches, *out1);

		break;
	}

	return false;
}


