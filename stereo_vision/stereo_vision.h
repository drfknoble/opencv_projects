#ifndef STEREO_VISION_H_
#define STEREO_VISION_H_

#include <iostream>
#include <sstream>
#include <experimental/filesystem>

#include <opencv2/opencv.hpp>

namespace sv {

    class sv_utilities {
    private:
    
    public:

        sv_utilities();

        void divide_frame(const cv::Mat &input_img, cv::Mat *left_img, cv::Mat *right_img);
        void save_frame(const cv::Mat &input_image, const std::string &path, const int &index);

    };

} //sv

#endif