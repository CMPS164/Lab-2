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

#include "Util/catcher.h"
#include "Physics/movingCollider.h"
#include "Physics/rigidbody.h"

using namespace std;

class Ball: public RigidSphere {
	public:
		float ballRadius;

		// Constructors
		Ball();
		Ball(float radius);
		Ball(float radius, Force f);
		Ball(float radius, Position startLoc);
		Ball(float radius, Position startLoc, Force f);
		
};

struct Wall: public Quad {
	int wallNum;
	float wallHeight;
	vector <Vertex>  wallVert;
	Wall(Vertex v1, Vertex v2, float wHeight, int wNum);
};

// Holds tile information
struct Tile: public Quad {
	int lineNum;				// Line number this information was at
	int tileNum;
	int numOfEdges;
	vector< Vertex > verts; //x, y, z coordinates; one per slot in the array
	vector< int > neighbors;	// Corresponds to each pair in vertices
	// IE: neighbor at element 0 corresponds to
	//     vertices at element 0 and 1
	vector< Wall > walls; 
	Tile(vector<string> data, int lNum);
};

class GolfCourse {
	public:
		vector< vector<string> > file;
		GolfCourse(vector< vector<string> > newFile);			// Constructor
		void buildCourse();							// Used to build a course from given vector
		vector<Tile> getTiles();
		Position getTee();
		Position getCup();
	private:
		// Position arrays should be in x, y, z format
		Catcher mitt;	// Catcher object

		// Tile tee/cup is on
		int teeTile;
		int cupTile;

		// Line Number info is at
		int teeLine;
		int cupLine;

		// Position in tile that the tee/cup resides in
		Position tee;
		Position cup;

		// Tiles in course
		vector<Tile> tiles;

		void decipherFile();	// Goes through file looking for tee and cup
		void inputTiles(vector< vector<string> > &pTiles, vector<int> &lineNum);		// Goes through reamaining file storing the tile data
		void setNorms(vector<Tile> &tiles);
		void printCourse();		// Prints out the course in its entirety
};

#endif