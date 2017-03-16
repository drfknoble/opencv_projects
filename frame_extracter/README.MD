# Frame Extracter

# Introduction

In this project, we extend the [Video Player]() project so that we are able to save a video's individual frames, or the n'th frames, e.g. every 10th frame (given n = 10). 

In this project, we introduce the use of command line parameters. Here, we have used the following:
1. -i input_directory. The directory of the video to be loaded.
1. -f file_name. The name of the video file.
1. -o output_directory. The directory the video's frames should be saved to.
1. -n step_size. The number of frames to step the video by.

# Program Operation

# Key files

The following provides an overview of what each of the project's main files do.

## main.cc

1. Initialises the directory and filename strings.
1. Gets current working directory and appends default input and output directories.

## main.h

## getopt.h

## getdir.h

# Conclusion

