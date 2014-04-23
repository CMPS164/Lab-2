/////////////////////////////////
// Lab 2: Golf Course Renderer //
/////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <string>

#include "reader.h"
#include "catcher.h"
#include "golfCourse.h"

using namespace std;

int main(int argc, char** argv) {
	int exitNum = 0;
	string fileName;

	vector< vector<string> > file;	// Our file, as a vector

	catcher mitt;			// catcher object

	// Try block, used to catch problems in what we do
	try {
		// Checks file entered, asks for input if a single file is not supplied
		if (argc != 2) {
			// Requests for an input
			fileName = mitt.reEnter("We expected one file, would you like to enter a file? (y/n)",
					"Enter file location: ", "no file location was entered.");
		} else {
			fileName = argv[1];
		}

		reader fileReader (fileName);		// reader object
		file = fileReader.getWords();		// Gets a vector of a vector of each word

		golfCourse course(file);
	} catch (string error) {
		// Reports error and changes the exit value
		cout << "Program exited because ";
		cout << error << endl;
		exitNum = 1;
	}

	return 0;
}