////////////////////////////////
// GolfCourse.h               //
// GolfCourse header          //
// Used for building a course //
////////////////////////////////

#ifndef GOLFCOURSE_H
#define GOLFCOURSE_H

#include <string>
#include <array>
#include <vector>

#include "catcher.h"

using namespace std;

class ball {
public:
	ball(float radius, array<double, 3> startLoc);
	float getRadius();
	array<double, 3> getBallLoc();
private:
	float ballRadius;
	array<double, 3> ballLoc; //The Tee location from the course file

	//How to keep track of ball position with Physics?
	//Francis Tang figures this out
};

struct wall {
	int wallNum;
	float wallHeight;
	array<double, 3> wall_v1;
	array<double, 3> wall_v2;
	array<double, 3> wall_v1h; //add in wallHeight to the y-component
	array<double, 3> wall_v2h;
	wall(array<double, 3> v1, array<double, 3> v2, float wHeight, int wNum);
};

// Holds tile information
struct tile {
	int lineNum;				// Line number this information was at
	int tileNum;
	int numOfEdges;
	vector< array<double, 3> > vertices; //x, y, z coordinates; one per slot in the array
	vector<int> neighbors;	// Corresponds to each pair in vertices
	// IE: neighbor at element 0 corresponds to
	//     vertices at element 0 and 1
	vector<wall> walls; 
	tile(vector<string> data, int lNum);
	
};

class golfCourse {
	public:
		vector< vector<string> > file;
		golfCourse(vector< vector<string> > newFile);			// Constructor
		void buildCourse();							// Used to build a course from given vector
		vector<tile> getTiles();
		array<double, 3> getTee();
		array<double, 3> getCup();
	private:
		// Position arrays should be in x, y, z format
		catcher mitt;	// Catcher object

		// Tile tee/cup is on
		int teeTile;
		int cupTile;

		// Line Number info is at
		int teeLine;
		int cupLine;

		// Position in tile that the tee/cup resides in
		array<double, 3> tee;
		array<double, 3> cup;

		// Tiles in course
		vector<tile> tiles;

		void decipherFile();	// Goes through file looking for tee and cup
		void inputTiles(vector< vector<string> > &pTiles, vector<int> &lineNum);		// Goes through reamaining file storing the tile data
		void setNorms(vector<tile> &tiles);
		void printCourse();		// Prints out the course in its entirety
};

#endif