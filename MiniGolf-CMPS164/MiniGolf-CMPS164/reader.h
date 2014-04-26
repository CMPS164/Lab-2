///////////////////////////
// Reader.h              //
// Reader header         //
// Used for file reading //
///////////////////////////

#ifndef READER_H
#define READER_H

#include "catcher.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class reader {
	private:
		catcher mitt;								// Catcher object
		ifstream dataFile;							// Our file

	public:
		string file;								// File path
		reader(string fileName);					// Constructor
		~reader();									// Destructor
		vector<string> getLines();					// Returns a vector that has each line of the document as an element
		vector< vector<string> > getWords();		// Returns a vector of a vector of the words in the document
};

#endif