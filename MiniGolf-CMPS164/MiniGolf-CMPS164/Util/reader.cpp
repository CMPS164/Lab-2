/////////////////////////////////////////
// Reader.cpp                          //
// Open file from given location       //
// Stores each line onto vector object //
/////////////////////////////////////////

#include <sstream>

#include "reader.h"

reader::reader(string fileName) {
	file = fileName;
	
	dataFile.open(fileName);			// Opens the file at the given location

	// Checks if file is open
	// if not, requests if user wants to input new location
	// If declined, throws an error
	while (!dataFile.is_open()) {
		// Requests new file location
		fileName = mitt.reEnter("File does not exists, would you like to enter a new file? (y/n)",
			"Enter new file location: ", "file does not exist.");

		dataFile.open(fileName);
	}
}

reader::~reader() {
	dataFile.close();					// Closes the document when done
}

// Returns a vector that has each line of the document as an element
vector<string> reader::getLines() {
	string line;

	vector<string> ofFile;

	// Runs through file and stores each line as a vector element
	while (getline(dataFile, line))
		ofFile.push_back(line);

	return ofFile;
}

// Returns a vector of a vector of the words in document
vector< vector<string> > reader::getWords() {
	vector<string> lines = getLines();		// Use function to get lines

	vector<string> tokens;					// Variable to hold the words in a line
	vector< vector<string> > temp;			// Variable to hold values that will be returned

	stringstream ss;
	string buf;

	// Goes through each line, seperating the words
	// and stores them into a vector
	// vector is then pushed onto a vector
	for (auto &line : lines) {
		ss << line;
		
		while (ss >> buf) {
			tokens.push_back(buf);
		}

		// Pushes vector onto the vector and clears our variables, to be used again
		temp.push_back(tokens);
		tokens.clear();
		ss.clear();
	}

	return temp;
}