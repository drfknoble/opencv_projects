#include "object_localiser.h"

ol::object_localiser::object_localiser()
{
}


ol::object_localiser::~object_localiser()
{
}

const bool ol::object_localiser::ORB(const cv::Mat & in1, const cv::Mat & in2, cv::Mat * out1, ol::matcher matcher)
{

	cv::Ptr<cv::ORB> detector = cv::ORB::create();

	std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;

	cv::Mat descriptors_object, descriptors_scene;

	detector->detectAndCompute(in1, cv::Mat(), keypoints_object, descriptors_object);
	detector->detectAndCompute(in2, cv::Mat(), keypoints_scene, descriptors_scene);

	switch (matcher) {
	case ol::BF:

		cv::BFMatcher bf;
		std::vector< cv::DMatch > matches;

		bf.match(descriptors_object, descriptors_scene, matches);

		double max_dist = 0; double min_dist = 100;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			double dist = matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			if (dist > max_dist) max_dist = dist;
		}

		std::vector< cv::DMatch > good_matches;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			if (matches[i].distance <= 0.5 * max_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}

		cv::drawMatches(in1, keypoints_object, in2, keypoints_scene,
			good_matches, *out1, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


		std::vector<cv::Point2f> obj;
		std::vector<cv::Point2f> scene;

		for (size_t i = 0; i < good_matches.size(); i++)
		{
			obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
			scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
		}

		cv::Mat H = findHomography(obj, scene, cv::RANSAC);

		std::vector<cv::Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(in1.cols, 0);
		obj_corners[2] = cvPoint(in1.cols, in1.rows); obj_corners[3] = cvPoint(0, in1.rows);

		std::vector<cv::Point2f> scene_corners(4);

		perspectiveTransform(obj_corners, scene_corners, H);

		line(*out1, scene_corners[0] + cv::Point2f(in1.cols, 0.0), scene_corners[1] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[1] + cv::Point2f(in1.cols, 0.0), scene_corners[2] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[2] + cv::Point2f(in1.cols, 0.0), scene_corners[3] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[3] + cv::Point2f(in1.cols, 0.0), scene_corners[0] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);

		break;

	}


	return false;
}

const bool ol::object_localiser::BRISK(const cv::Mat & in1, const cv::Mat & in2, cv::Mat * out1, ol::matcher matcher)
{

	cv::Ptr<cv::BRISK> detector = cv::BRISK::create();

	std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;

	cv::Mat descriptors_object, descriptors_scene;

	detector->detectAndCompute(in1, cv::Mat(), keypoints_object, descriptors_object);
	detector->detectAndCompute(in2, cv::Mat(), keypoints_scene, descriptors_scene);

	switch (matcher) {
	case ol::BF:

		cv::BFMatcher bf;
		std::vector< cv::DMatch > matches;

		bf.match(descriptors_object, descriptors_scene, matches);

		double max_dist = 0; double min_dist = 100;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			double dist = matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			if (dist > max_dist) max_dist = dist;
		}

		std::vector< cv::DMatch > good_matches;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			if (matches[i].distance <= 0.5 * max_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}

		cv::drawMatches(in1, keypoints_object, in2, keypoints_scene,
			good_matches, *out1, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


		std::vector<cv::Point2f> obj;
		std::vector<cv::Point2f> scene;

		for (size_t i = 0; i < good_matches.size(); i++)
		{
			obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
			scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
		}

		cv::Mat H = findHomography(obj, scene, cv::RANSAC);

		std::vector<cv::Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(in1.cols, 0);
		obj_corners[2] = cvPoint(in1.cols, in1.rows); obj_corners[3] = cvPoint(0, in1.rows);

		std::vector<cv::Point2f> scene_corners(4);

		perspectiveTransform(obj_corners, scene_corners, H);

		line(*out1, scene_corners[0] + cv::Point2f(in1.cols, 0.0), scene_corners[1] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[1] + cv::Point2f(in1.cols, 0.0), scene_corners[2] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[2] + cv::Point2f(in1.cols, 0.0), scene_corners[3] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);
		line(*out1, scene_corners[3] + cv::Point2f(in1.cols, 0.0), scene_corners[0] + cv::Point2f(in1.cols, 0.0), cv::Scalar(0, 255, 0), 4);

		break;

	}

	return false;
}


