#include "stereo_vision.h"

sv::sv_utilities::sv_utilities() {


}

void sv::sv_utilities::divide_frame(const cv::Mat &input_img, cv::Mat *left_img, cv::Mat *right_img) {
    
    cv::Size img_size = input_img.size();

    int w = img_size.width;
    int h = img_size.height;
    
    *left_img = input_img(cv::Rect(0, 0, w/2, h));
    *right_img = input_img(cv::Rect(w/2, 0, w/2, h));

    return;

}

void sv::sv_utilities::save_frame(const cv::Mat &input_image, const std::string &path, const int &index) {
    
    std::stringstream ss;
    
    std::experimental::filesystem::path cwd = std::experimental::filesystem::current_path();

    std::cout << cwd << std::endl;

    if(!std::experimental::filesystem::exists(path)) {

        std::experimental::filesystem::create_directory(path);

        cv::imwrite(ss.str(), input_image);

    } else {

        ss << path << "/img_" << index << ".png" << std::endl;
        
        cv::imwrite(ss.str(), input_image);

    }
   
    return;

}