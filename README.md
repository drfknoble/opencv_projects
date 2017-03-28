# OpenCV Projects

Hi There!

My name is [Dr. Frazer K. Noble](http://www.massey.ac.nz/massey/expertise/profile.cfm?stref=803250) and I am a lecturer at Massey University's School of Engineering and Advanced Technology (SEAT), Albany, New Zealand.

This repository is a collection of projects and tutorials for getting started and working with the Open Computer Vision (OpenCV) library. I intend this to be an ongoing effort that I will update on a regular basis; I hope that it may be of some use to you.

Best regards,

Frazer

P.S. If you'd like to hear about new projects and tutorials, follow me on Twitter [@FrazerNoble](https://twitter.com/FrazerNoble).

# Table of Contents

1. Requirements.
1. Projects.
1. Tutorials.
1. Installation.
1. Contribution.
1. Credits.

# Requirements

I have used the following tools and libraries to create each project:

 1. [gflags](https://github.com/gflags/gflags).
 1. [tinyxml2](https://github.com/leethomason/tinyxml2).
 1. [CMake](https://cmake.org/).
 1. [Microsoft Visual Studio 2017](https://www.visualstudio.com/).
 1. [OpenCV 3.2](http://opencv.org/).
 1. [Logitec c920 USB Camera](https://www.logitech.com/en-nz/product/hd-pro-webcam-c920).
 
To help ensure everything works, I'd also suggest you create the following enrionmental variables:

1. OPENCV_DIR C:/opencv/opencv/build. This is where OpenCV is installed.
1. DEV_LIBRARIES C:/dev_libraries. This is where you, might, have additional libraries you want to use in a project.
 
Each project has been compiled and run on PCs running Windows 8 x64 and Windows 10 x64 to ensure they work.

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
1. [Green Screen](https://github.com/FKNoble/opencv_projects/tree/master/green_screen). This project looks at how we can detect the colour green in an image, video, or video capture device and replace it with a desired background.

As mentioned, these projects were created using Microsoft's Visual Studio 2017. To facilitate getting each started quickly, I created a number of property sheets: opencv_debug_x64.props, opencv_release_x64.props, dev_libraries_debug_x64, adn dev_libraries_release_x64. These, essentially, tell each project's solution where OpenCV's and useful libraries' include and lib directories are, and which .lib files to use.

In the OpenCV property sheets, I have used the OPENCV_DIR environmental variable, whose value on my PC is C:\opencv\opencv\build, to specify where the include directory ($(OPENCV_DIR)\Include) and the library directory ($(OPENCV_DIR)\x64\vc14\lib\) are. Also, in the property sheets, I've made it so that the solution uses opencv_world320d.lib and opencv_wordl320.lib when linking.

If you're OpenCV installation is not in C:\opencv\, then you will need to modify the environmental variable accordingly; though, you need only do this once (just be sure that you've got the admin' privaledges to do so).

In the DevLibraries property sheets, I have used the DEV_LIBRARIES environmental variable, whose value on my PC is C:\dev_libraries, to specify where the root folder of useful libraries include and library directories are. One such library is gflags, which I've used to parse the command line for instructions.

# Tutorials

The following is a list of the tutorials included in this repository:

1. [How to Install OpenCV](https://youtu.be/IMZsrL12k6I). A short tutorial on installing OpenCV.
1. [How to Build an Open Source Project](https://youtu.be/LxHV-KNEG3k) A short video on how to build an open source project with CMake.

# Installation

1. Clone the opencv_projects repo'.
1. Clone the gflags repo'.
1. If you've not done so already, build gflags and tinyxml2 using CMake and Visual Studio as an Administrator. Also, ensure 'Shared Libraries' are enabled. Once completed, by default, you should find that there is now C:/Program Files/gflags and ./tinyxml2 directories, which contains Include and Lib sub-directories. Move these to C:/dev_libraries.
1. Create environment variables OPENCV_DIR and DEV_LIBRARIES.
1. Open a project's solution file.
1. Change the solution platforms from x86 to x64, if necessary.
1. Build project.

At this point everything should compile and run.

# Contributions

If you feel like you can make a contribution; please, feel free to make a request.

# Credits

Dr. Frazer K. Noble 2017
