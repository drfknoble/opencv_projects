#include "stereo_vision.h"

int main(int argc, char* argv[]) {

    cv::VideoCapture stereo_camera(1);

    if(!stereo_camera.isOpened()) {
        std::cout << "Could not open camera." << std::endl;
        return -1;
    }

    cv::namedWindow("Frame", CV_WINDOW_AUTOSIZE);

    sv::sv_utilities utils;

    int frame_count {0}, index {0};

    while(true) {

        cv::Mat frame;

        stereo_camera >> frame;

        if (!frame.empty()) {

            cv::imshow("Frame", frame);

            cv::Mat left_img, right_img;

            utils.divide_frame(frame, &left_img, &right_img);

            cv::imshow("left", left_img);
            cv::imshow("right", right_img);

            if (frame_count % 100 == 0) {

                utils.save_frame(left_img, "left", index);
                utils.save_frame(right_img, "right", index);

                index++;

            }

            frame_count++;

        }

        char c;
        c = cv::waitKey(1);
        if (c == 27) {
            break;
        }

    }

    cv::destroyAllWindows();

    stereo_camera.release();

    return 0;
}