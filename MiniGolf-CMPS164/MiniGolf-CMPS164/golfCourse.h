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

#define PI 3.14159265

using namespace std;

namespace
{
	int newTileNum;
}

struct Wall : public Quad {
	int wallNum;
	float wallHeight;
	vector <Vertex>  wallVert;
	Wall(Vertex v1, Vertex v2, float wHeight, int wNum);
};

/*
struct TriggerWall : public Quad {
	int wallNum;
	float wallHeight;
	vector <Vertex>  wallVert;
	TriggerWall(Vertex v1, Vertex v2, float wHeight, int wNum);
	void onCollision();
	void update();
};*/

// Holds tile information
struct Tile : public Quad {
	int lineNum;				// Line number this information was at
	int tileNum;
	int numOfEdges;
	vector< Vertex > verts; //x, y, z coordinates; one per slot in the array
	vector< int > neighbors;	// Corresponds to each pair in vertices
	// IE: neighbor at element 0 corresponds to
	//     vertices at element 0 and 1
	vector<Wall> walls;
	// vector<TriggerWall> triggerWalls;
	Tile();
	Tile(vector<string> data, int lNum);
};

class Ball: public RigidSphere {
	public:
		float ballRadius;

		int tileNum;
		Tile onTile;

		// Constructors
		Ball();
		Ball(float radius);
		Ball(float radius, Force f);
		Ball(float radius, Position startLoc);
		Ball(float radius, Position startLoc, Force f);

		void update();
};

class GolfCourse {
	public:
		Ball golfBall;
		int shotNum;

		vector< vector<string> > file;
		GolfCourse(vector< vector<string> > newFile);			// Constructor
		void buildCourse();							// Used to build a course from given vector
		vector<Tile> getTiles();
		Position getTee();
		Position getCup();
		int getTeeTile();
		int getCupTile();
		int checkCurLoc();
		vector<Vertex> formRay(vector <Vertex> vertices); //Used for Ray Casting
		bool intersectionTest(Vertex v1a, Vertex v1b, Vertex v2a, Vertex v2b);
		void setBall();
		void setBallTile(int num);
		vector<Collider*> wallsToCollider(vector<Wall> wal);
		// vector<Collider*> triggerWallsToCollider(vector<TriggerWall> wal);
		void putt(Force f);
		void putt(double dir, double spd);

		

		void update();
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