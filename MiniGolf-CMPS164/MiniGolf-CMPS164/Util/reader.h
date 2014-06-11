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
		Catcher mitt;								// Catcher object
		ifstream dataFile;							// Our file

	public:
		string file;								// File path
		reader(string fileName);					// Constructor
		~reader();									// Destructor
		vector<string> getLines();					// Returns a vector that has each line of the document as an element
		vector< vector<string> > getWords();		// Returns a vector of a vector of the words in the document
		vector< vector < vector <string> > > toCourses; //Variable to hold all the potential courses
		vector< vector<string> > getWords2(vector<string> lines);		// Returns a vector of a vector of the words in the document. This is for reading all courses in one file
		vector< vector< vector<string > > >  parseFile();
};

#endif