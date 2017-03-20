//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef FRAME_EXTRACTOR_H_
#define FRAME_EXTRACTOR_H_

#include <opencv2\opencv.hpp>

#include "getdir.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace project {

	void DetectColour(const cv::Mat &src, const cv::Scalar &lwr, const cv::Scalar &upr, cv::Mat *dst) {

		cv::Mat image;
		cv::cvtColor(src, image, cv::COLOR_BGR2HSV);
		cv::inRange(image, lwr, upr, image);

		cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5));

		cv::morphologyEx(image, image, cv::MORPH_OPEN, kernel);
		cv::morphologyEx(image, image, cv::MORPH_OPEN, kernel);
		cv::morphologyEx(image, image, cv::MORPH_CLOSE, kernel);
		cv::morphologyEx(image, *dst, cv::MORPH_CLOSE, kernel);
				
		return;

	}

	void GreenScreen(const cv::Mat &src,  const cv::Mat &mask, cv::Scalar &hsv,  cv::Mat *dst) {

		cv::Mat image = src;

		cv::Scalar lwr(max(0, hsv[0] - 10), hsv[1], hsv[2]);
		cv::Scalar upr(min(180, hsv[0] + 10), 255, 255);

		DetectColour(image, lwr, upr, &image);
		
		cv::threshold(image, image, 100, 255, cv::THRESH_BINARY);
		cv::bitwise_not(image, image);

		cv::Mat img;
		cv::resize(mask, img, cv::Size(image.size()));
		cv::Mat msk;
		cv::bitwise_not(image, msk);
		cv::Mat mskd;
		img.copyTo(mskd, msk);
		cv::imshow("", mskd);

		src.copyTo(image, image);
		
		cv::add(image, mskd, image);

		*dst = image;

	}

} // !project

#endif // !FRAME_EXTRACTOR_H_
