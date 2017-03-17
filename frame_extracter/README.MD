# Frame Extracter

# Introduction

In this project, we extend the [Video Player]() project so that we are able to save a video's individual frames, or the n'th frames, e.g. every 10th frame (given n = 10). 

In this project, we introduce the use of command line parameters. Here, we have used the following:
1. -i input_directory. The directory of the video to be loaded.
1. -f file_name. The name of the video file.
1. -o output_directory. The directory the video's frames should be saved to.
1. -n step_size. The number of frames to step the video by.

# Program Operation

1. Initialises directories and filename strings.
1. Gets current working directory and appends default input and output directories.
1. Reads the command line parameters, and if any are set, updates local variables.
1. Creates a cv::VideoCapture object and reads frames from the video.
1. Frames are then saved to the output directory.
1. When Esc is pressed, display window is closed and the cv::VideoCapture object is released.

# Conclusion

This program successfully extracts frames from a video.
