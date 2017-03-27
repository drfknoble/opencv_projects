//Copyright 2017 Dr. Frazer K. Noble
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE S

/*!
* \file main.cc
* \author Dr. Frazer K. Noble
* \date 2017
* \brief Generic OpenCV application.
*
* \section Description.
*
* \note Comments are written in Doxygen-compliant format (see \link https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html \endlink). Here, I have used Qt style (/ *! ...text... * /)
*/

#include "main.h"

/*!
* \brief gFlag command line parameter.
* \param i i is the input directory, which an image or video should be loaded from.
*/
DEFINE_string(i, "", "[dir]");
/*!
* \brief gFlag command line parameter.
* \param f f is the image's or video's file name.
*/
DEFINE_string(f, "", "[file.type]");
/*!
* \brief gFlag command line parameter.
* \param b b is the background image's file name.
*/
DEFINE_string(o, "", "[dir]");
/*!
* \brief gFlag command line parameter.
* \param d d is the debug flag; when set, it displays additional information.
*/
DEFINE_bool(d, false, "[true, false]");

/*
* \brief Main entry point for the program.
* \param argc is the number of command line parameters provided.
* \param argv is the string of command line parameters provided.
* \return Returns 0 on success; -1 on failure.
*/

int main(int argc, char* argv[]) {

	std::string current_directory = ""; //! Current working directory of the executable.
	std::string input_directory = ""; //! The input directory.
	std::string output_directory = ""; //! The output directory.
	std::string file_name = "";//! The file name.
	int step_size = 1; //! The step size.
	bool debug = false; //! The debug flag.

	getpath(&current_directory);

	tinyxml2::XMLDocument config;
	config.LoadFile("./config.xml");
	
	tinyxml2::XMLElement* xml;
	
	xml = config.FirstChildElement("Input");
	input_directory = current_directory + std::string(xml->GetText());
	
	xml = config.FirstChildElement("Output");
	output_directory = current_directory + std::string(xml->GetText());
	
	xml = config.FirstChildElement("File");
	file_name = xml->GetText();

	/*!
	* Check the command line parameters to see if non-default values are used.
	*/

	gflags::ParseCommandLineFlags(&argc, &argv, true);

	if (FLAGS_i.compare("") != 0) { //! If input directory is provided, update default.
		input_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_i) << std::endl;
	}

	if (FLAGS_f.compare("") != 0) { //! If file name is provided, update default.
		file_name = FLAGS_f;
		//std::cout << std::string(FLAGS_f) << std::endl;
	}

	if (FLAGS_o.compare("") != 0) { //! If output directory is provided, update default.
		output_directory = FLAGS_i;
		//std::cout << std::string(FLAGS_o) << std::endl;
	}

	if (FLAGS_d) { //! If debug flag is set, update default.
		debug = true;
		//std::cout << FLAGS_d << std::endl;
	}

	gflags::ShutDownCommandLineFlags();

	if (debug) { //! If debug flag is set, display the input and output directories, file name, and step size.
		std::cout << "Input directory: " << input_directory << std::endl;
		std::cout << "Output directory: " << output_directory << std::endl;
		std::cout << "Filename: " << file_name << std::endl;
		std::cout << "Step size: " << step_size << std::endl;
	}
	
	system("pause");

	return 0;
}