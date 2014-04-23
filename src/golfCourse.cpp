////////////////////////////////////
// GolfCourse.cpp                 //
// Builds course from vector file //
////////////////////////////////////

#include <iostream>
#include <sstream>

#include "golfCourse.h"

// tile struct constructor
// Deciphers line and stores everything
tile::tile(vector<string> data, int lNum): lineNum(lNum){
	for (unsigned int x = 1; x < data.size(); ++x) {
		if (x == 1) {
			tileNum = atoi(data[x].c_str());
		} else if (x == 2) {
			numOfEdges = atoi(data[x].c_str());
		} else if (x >= data.size() - numOfEdges) {
			neighbors.push_back(atoi(data[x].c_str()));
		} else {
			array<double, 3> temp;
			temp[0] = atof(data[x].c_str());
			temp[1] = atof(data[x+1].c_str());
			temp[2] = atof(data[x+2].c_str());
			x += 2;
			vertices.push_back(temp);
		}
	}
}

// Constructor
golfCourse::golfCourse(vector< vector<string> > newFile) {
	file = newFile;

	// Used for checking later
	teeTile = -1;
	cupTile = -1;

	decipherFile();

	buildCourse();		// Builds the course from data
}

// Goes through file looking for tee and cup
void golfCourse::decipherFile() {
	vector< vector<string> > pTiles;	// Stores that vectors that might be tiles
	vector<int> lineNum;

	// Goes through the vectors looking for tee and cup
	// If error is found, print whats wrong and exits out
	// Correct and non tee/cup lines will be inserted into another vector
	for (unsigned int x = 0; x < file.size(); ++x) {
		if (file[x].size() < 3) {
			throw string ("not enough information on line " + to_string(x) + ".");
		} else if (file[x].size() == 5) {
			if (file[x][0].compare("tee") == 0) {
				if (teeTile != -1) throw string("another 'tee' data found at line " + to_string(x) +
						", current engine does not support more than 1.");
				teeLine = x;
				istringstream(file[x][1]) >> teeTile;
				istringstream(file[x][2]) >> tee[0];
				istringstream(file[x][3]) >> tee[1];
				istringstream(file[x][4]) >> tee[2];
			} else if (file[x][0].compare("cup") == 0) {
				if (cupTile != -1) throw string("another 'cup' data found at line " + to_string(x) +
					", current engine does not support more than 1.");
				cupLine = x;
				istringstream(file[x][1]) >> cupTile;
				istringstream(file[x][2]) >> cup[0];
				istringstream(file[x][3]) >> cup[1];
				istringstream(file[x][4]) >> cup[2];
			} else {
				throw string("data at line " + to_string(x) + " has an incorrect tag.");
			}
		} else {
			pTiles.push_back(file[x]);
			lineNum.push_back(x);
		}
	}

	if (teeTile == -1) mitt.cont("No tee data found, would you like to continue? (y/n)","tee data is missing.");
	if (cupTile == -1) mitt.cont("No cup data found, would you like to continue? (y/n)","cup data is missing.");

	inputTiles(pTiles, lineNum);
}

// Goes through remaining file storing the tile data that are correct
// Throws if input is incorrect
void golfCourse::inputTiles(vector< vector<string> > &pTiles, vector<int> &lineNum) {
	vector<int> taken(pTiles.size());

	// Goes through remaining data
	// Those that are incorrect will print a message and throw
	// Correct one will be checked to duplicates
	// Once all parameters have passed, data is inserted
	for (unsigned int x = 0; x < pTiles.size(); ++x) {//for (auto &x : pTiles) {
		if (pTiles[x].size() != 3 + 4 * atoi(pTiles[x][2].c_str())) {
			throw string("one of the 'tiles' is not formatted correctly.");
		} else {
			if (taken[atoi(pTiles[x][1].c_str()) - 1] != 0) {
				throw string("multiple tile " + pTiles[x][1] + "'s are listed.");
			} else {
				taken[atoi(pTiles[x][1].c_str()) - 1] = 1;
				tile temp (pTiles[x], lineNum[x]);
				tiles.push_back(temp);
			}
		} 
	}
}

// Prints out the course in its entirety
void golfCourse::printCourse() {
	for (auto &x : tiles) {
		cout << "tile ";
		cout << x.tileNum << " ";
		cout << x.numOfEdges << " ";
		for (auto &y : x.vertices) {
			cout << y[0] << " " << y[1] << " " << y[2] << " ";
		}
		for (auto &y : x.neighbors) {
			cout << y << " ";
		}
		cout << endl;
	}

	cout << "tee ";
	cout << teeTile << " ";
	cout << tee[0] << " " << tee[1] << " " << tee[2] << endl;

	cout << "cup ";
	cout << cupTile << " ";
	cout << cup[0] << " " << cup[1] << " " << cup[2] << endl;
}



/////////////////////////////////////////////
// Code for drawing ideally goes down here //
////////////////////////////////////////////



// Used to build a course from given vector
void golfCourse::buildCourse() {

	printCourse();	// Remove when you start working

	/*
	* Kennth does this part
	* If you can think of a better way to do this, go for it
	*/
	
}








