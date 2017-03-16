//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "main.h"

int main(int argc, char* argv[]) {

	std::string current_directory = "";
	std::string input_directory = "";
	std::string output_directory = "";
	std::string file_name = "";

	getpath(&current_directory);
	input_directory = current_directory.append("\\data\\input\\");
	getpath(&current_directory);
	output_directory = current_directory.append("\\data\\output\\");

	file_name = input_directory.append("Video.mp4");

	int step_size = 1;

	int r = 0;
	while ((r = GetOpt(argc, argv, "f:i:o:n:")) != -1) {
		switch (r) {
		case 'f':
			file_name = optarg;
			break;
		case 'i':
			input_directory = optarg;
			break;
		case 'o':
			output_directory = optarg;
			break;
		case 'n':
			step_size = atoi(optarg);
			break;
		}
	}

	cv::VideoCapture video(file_name);

	cv::namedWindow(file_name, cv::WINDOW_AUTOSIZE);

	int frame_count = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
	int current_frame = 0;

	while (true) {

		cv::Mat frame;
		std::stringstream ss;

		if (current_frame + step_size < frame_count) {
			if (video.read(frame)) {
				cv::imshow(file_name, frame);
				ss << output_directory << "frame_" << current_frame << ".png";
				std::cout << ss.str() << std::endl;
				cv::imwrite(ss.str(), frame);
				current_frame += step_size;
				video.set(cv::CAP_PROP_POS_FRAMES, current_frame);
			}
		}		

		char c = cv::waitKey(30);
		if (c == 27) {
			break;
		}
	}

	cv::destroyAllWindows();

	return 0;
}