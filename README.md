# OpenCV Projects

Hi There!

My name is [Dr. Frazer K. Noble](http://www.massey.ac.nz/massey/expertise/profile.cfm?stref=803250) and I am a lecturer at Massey University's School of Engineering and Advanced Technology (SEAT), Albany, New Zealand.

This repository is a collection of projects and tutorials for getting started and working with the Open Computer Vision (OpenCV) library. I intend this to be an ongoing effort that I will update on a regular basis; I hope that it may be of some use to you.

I have used the following tools to create each project:
 1. [Microsoft Visual Studio 2017](https://www.visualstudio.com/).
 1. [OpenCV 3.2](http://opencv.org/).
 1. [Logitec c920 USB Camera](https://www.logitech.com/en-nz/product/hd-pro-webcam-c920).
 
Furthermore, each project has been compiled and run on a PC running Windows 8 x64 to ensure they work.

Best regards,

Frazer

P.S. If you'd like to hear about new projects and tutorials, follow me on Twitter [@FrazerNoble](https://twitter.com/FrazerNoble).

# Resources

Here is a list of resources, which I think, are helpful for learning OpenCV and coding:

1. [OpenCV Documentation](http://docs.opencv.org/3.2.0/). OpenCV's documentation.
1. [Learning OpenCV 3.0](http://shop.oreilly.com/product/0636920044765.do). A book for learning OpenCV.
1. [Learn C++](http://www.learncpp.com/). A great website for learning C++.

Please note, the above list is not exhaustive; more of a minimal set to get started.

# Projects

The following is a list of the projects included in this repository:
1. [Getting Started](https://github.com/FKNoble/opencv_projects/tree/master/getting_started). This project is the 'Hello World!' of OpenCV projects. 
1. [Video Player](https://github.com/FKNoble/opencv_projects/tree/master/video_player). This project looks at how we can play a video file.
1. [Frame Extractor](https://github.com/FKNoble/opencv_projects/tree/master/frame_extracter). This project looks at how to extract frames from a video.

As mentioned, these projects were created using Microsoft's Visual Studio 2017. To facilitate getting each started quickly, I created a pair of property sheets: opencv_debug_x64.props and opencv_release_x64.props. These, essentially, tell each project's solution where OpenCV's include and lib directories are, and which .lib files to use. Here, I have used C:\opencv\opencv\build\include and C:\opencv\opencv\build\x64\vc14\lib, and the opencv_world320d.lib and opencv_world320.lib directories and files, respectively. If you're OpenCV installation is not in C:\opencv\, then you will need to modify the property sheets; though, you need only do this once (just take care to not overwrite changes if you clone this repo again to your working directory).

# Tutorials

The following is a list of the tutorials included in this repository:

1. [How to Install OpenCV](). A short tutorial on installing OpenCV.
