#pragma once

#include <opencv2\opencv.hpp>

namespace pc {

	class pca_analyser
	{

	private:
		void drawAxis(cv::Mat&, cv::Point, cv::Point, cv::Scalar, const float);
		double getOrientation(const std::vector<cv::Point> &, cv::Mat&);

	public:
		pca_analyser();
		~pca_analyser();

		const bool compute(const cv::Mat &in1, cv::Mat *out1);
	};

}

