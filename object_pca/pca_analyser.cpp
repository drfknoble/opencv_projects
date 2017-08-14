#include "pca_analyser.h"



pc::pca_analyser::pca_analyser()
{
}


pc::pca_analyser::~pca_analyser()
{
}

const bool pc::pca_analyser::compute(const cv::Mat & in1, cv::Mat * out1)
{

	*out1 = in1.clone();

	cv::Mat blurred_frame, hsv_frame, thresholded_frame, morphed_frame, final_frame;

	cv::GaussianBlur(in1, blurred_frame, cv::Size(5, 5), 0, 0, 4);

	cv::cvtColor(blurred_frame, hsv_frame, CV_BGR2HSV);

	cv::inRange(hsv_frame, cv::Scalar(10, 0, 0), cv::Scalar(70, 255, 255), thresholded_frame);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(20, 20), cv::Point(10, 10));

	cv::erode(thresholded_frame, morphed_frame, element);
	cv::erode(morphed_frame, morphed_frame, element);
	cv::dilate(morphed_frame, morphed_frame, element);
	cv::dilate(morphed_frame, morphed_frame, element);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(morphed_frame, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
		
	cv::drawContours(*out1, contours, 0, cv::Scalar(0, 0, 255));

	getOrientation(contours[0], *out1);

	return false;
}

void pc::pca_analyser::drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale = 0.2)
{
	double angle, hypotenuse;

	angle = atan2((double)p.y - q.y, (double)p.x - q.x); 
	hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));

	q.x = (int)(p.x - scale * hypotenuse * cos(angle));
	q.y = (int)(p.y - scale * hypotenuse * sin(angle));
	line(img, p, q, colour, 1, CV_AA);
	// create the arrow hooks
	p.x = (int)(q.x + 9 * cos(angle + CV_PI / 4));
	p.y = (int)(q.y + 9 * sin(angle + CV_PI / 4));
	line(img, p, q, colour, 1, CV_AA);
	p.x = (int)(q.x + 9 * cos(angle - CV_PI / 4));
	p.y = (int)(q.y + 9 * sin(angle - CV_PI / 4));
	line(img, p, q, colour, 1, CV_AA);
}
double pc::pca_analyser::getOrientation(const std::vector<cv::Point> &pts, cv::Mat &img)
{
	
	int sz = static_cast<int>(pts.size());
	cv::Mat data_pts = cv::Mat(sz, 2, CV_64FC1);
	for (int i = 0; i < data_pts.rows; ++i)
	{
		data_pts.at<double>(i, 0) = pts[i].x;
		data_pts.at<double>(i, 1) = pts[i].y;
	}

	cv::PCA pca_analysis(data_pts, cv::Mat(), CV_PCA_DATA_AS_ROW);
	
	cv::Point cntr = cv::Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));

	std::vector<cv::Point2d> eigen_vecs(2);
	std::vector<double> eigen_val(2);

	for (int i = 0; i < 2; ++i)
	{
		eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
			pca_analysis.eigenvectors.at<double>(i, 1));
		eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
	}


	circle(img, cntr, 3, cv::Scalar(255, 0, 255), 2);
	
	cv::Point p1 = cntr + 0.02 * cv::Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
	cv::Point p2 = cntr - 0.02 * cv::Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
	
	drawAxis(img, cntr, p1, cv::Scalar(0, 255, 0), 1);
	drawAxis(img, cntr, p2, cv::Scalar(255, 255, 0), 5);
	
	double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x);

	return angle;
}