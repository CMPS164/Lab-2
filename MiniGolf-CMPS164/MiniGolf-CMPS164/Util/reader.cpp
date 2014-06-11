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


vector< vector< vector<string > > > reader::parseFile() {
	vector<string> lines = getLines();
	vector<string> p_CourseLines;
	vector< vector< vector<string> > > returnList;

	for (int i = 1; i < lines.size(); i++) {
		string lineContent = lines.at(i);
		if (lineContent.compare("begin_hole") == 0) {
		
			//cout << "Begin_Hole string" << endl;
			p_CourseLines.clear();
			continue;
		}
		else if (lineContent.compare("end_hole") == 0) {
			//cout << "End_Hole string" << endl;
			//end the course reading and send the lines vector to getWords2
			//clears the vector p_CourseLines to continue reading
			//toCourses.push_back(getWords2(p_CourseLines));
			returnList.push_back(getWords2(p_CourseLines));
			//p_CourseLines.clear();
		
			continue;
		}
		
			p_CourseLines.push_back(lineContent);
		
	}
	return returnList;
}

vector< vector<string> > reader::getWords2(vector <string> lines) {
	
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
