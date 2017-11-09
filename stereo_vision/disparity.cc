#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{

    cv::Mat img1 = cv::imread("/home/frazer/Documents/opencv_projects/stereo_vision/L.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat img2 = cv::imread("/home/frazer/Documents/opencv_projects/stereo_vision/R.jpg", CV_LOAD_IMAGE_COLOR);

    cv::Mat L, R;

    cv::pyrDown(img1, L, cv::Size(img1.cols / 2, img1.rows / 2));
    cv::pyrDown(img2, R, cv::Size(img2.cols / 2, img2.rows / 2));

    cv::Size img_size = L.size();

    int numberOfDisparities = ((img_size.width / 8) + 15) & -16;

    cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);

    sgbm->setPreFilterCap(63);
    int sgbmWinSize = 3;
    sgbm->setBlockSize(sgbmWinSize);

    int cn = img1.channels();

    sgbm->setP1(8 * cn * sgbmWinSize * sgbmWinSize);
    sgbm->setP2(32 * cn * sgbmWinSize * sgbmWinSize);
    sgbm->setMinDisparity(0);
    sgbm->setNumDisparities(numberOfDisparities);
    sgbm->setUniquenessRatio(10);
    sgbm->setSpeckleWindowSize(100);
    sgbm->setSpeckleRange(32);
    sgbm->setDisp12MaxDiff(1);

    cv::Mat disp, disp8;

    sgbm->compute(L, R, disp);

    disp.convertTo(disp8, CV_8U);

    cv::namedWindow("left", CV_WINDOW_AUTOSIZE);
    cv::imshow("left", L);
    
    cv::namedWindow("right", CV_WINDOW_AUTOSIZE);
    cv::imshow("right", R);
    
    cv::namedWindow("disparity", CV_WINDOW_AUTOSIZE);
    cv::imshow("disparity", disp8);

    

    cv::waitKey(0);

    return 0;
}
