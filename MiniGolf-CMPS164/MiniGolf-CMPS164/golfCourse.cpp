////////////////////////////////////
// GolfCourse.cpp                 //
// Builds course from vector file //
////////////////////////////////////

#include <iostream>
#include <sstream>

#include "golfCourse.h"

Ball::Ball() : RigidSphere() {
	ballRadius = 1;
}

Ball::Ball(float radius) : RigidSphere(radius) {
	ballRadius = radius;
}

Ball::Ball(float radius, Force f) : RigidSphere(radius, f) {
	ballRadius = radius;
}

Ball::Ball(float radius, Position startLoc) : RigidSphere(radius, startLoc){
	ballRadius = radius;
}

Ball::Ball(float radius, Position startLoc, Force f) : RigidSphere(radius, startLoc, f) {
	ballRadius = radius;
}

Tile::Tile() {}

// tile struct constructor
// Deciphers line and stores everything
Tile::Tile(vector<string> data, int lNum): lineNum(lNum){
	for (unsigned int x = 1; x < data.size(); ++x) {
		if (x == 1) {
			tileNum = atoi(data[x].c_str());
		} else if (x == 2) {
			numOfEdges = atoi(data[x].c_str());
		} else if (x >= data.size() - numOfEdges) {
			neighbors.push_back(atoi(data[x].c_str()));
		} else {
			Vertex temp;
			temp.x = atof(data[x].c_str());
			temp.y = atof(data[x+1].c_str());
			temp.z = atof(data[x+2].c_str());
			x += 2;
			verts.push_back(temp);
		}
	}

	setVertices(verts);
	
	
	//create walls here
	int wallNum = 0;
	for (int index = 0; index < neighbors.size(); ++index) {
		if (neighbors.at(index) == 0) { //There is no connecting tile and thus is an edge
			wallNum++;
			Vertex v1;
			Vertex v2;

			//Take the vertex indices and create a new vector for a wall.
			if (index == neighbors.size() - 1) {
				//This check is for the case if there is no edge between the last vertice and the first one in the vector, thus we need to 'loop' around
				v1 = verts.at(index);
				v2 = verts.at(0);
			} else {
				v1 = verts.at(index);
				v2 = verts.at(index + 1);
			}
			Wall temp(v1, v2, 0.1, wallNum);	//wall height is set to 0.1
			walls.push_back(temp);
		}
	}
	
}


//Wall Constructor
Wall::Wall(Vertex v1, Vertex v2, float wHeight, int wNum) : Quad(){
	wallNum = wNum;	//Unknown what to do with WallNum, here just in case
	wallHeight = wHeight;
	
	//Four vertices for the Edge
	wallVert.push_back(Vertex(v1.x, v1.y, v1.z));
	wallVert.push_back(Vertex(v2.x, v2.y, v2.z));
	wallVert.push_back(Vertex(v2.x, v2.y + wallHeight, v2.z));
	wallVert.push_back(Vertex(v1.x, v1.y + wallHeight, v1.z));

	setVertices(wallVert);
}

// Constructor
GolfCourse::GolfCourse(vector< vector<string> > newFile) {
	file = newFile;

	// Used for checking later
	teeTile = -1;
	cupTile = -1;

	decipherFile();
	setBall();
}

//Accessors for tiles Vector, Tee and Cup Locations
vector<Tile> GolfCourse::getTiles() {
	return tiles;
}

Position GolfCourse::getTee() {
	return tee;
}

Position GolfCourse::getCup() {
	return cup;
}

// Sets ball onto tee
void GolfCourse::setBall() {
	golfBall = Ball(0.025, getTee());
	setBallTile(teeTile);
	golfBall.setCollisionObjects(wallsToCollider(golfBall.onTile.walls));
}

// Sets balls tile num and checks if tile in vector matches tile num
// Correctly runs through vector if it doesn't to find matching tile
void GolfCourse::setBallTile(int num) {
	golfBall.tileNum = num;

	if (tiles[teeTile - 1].tileNum == teeTile) {
		golfBall.onTile = tiles[teeTile - 1];
	} else {
		for (auto aTile : tiles) {
			if (aTile.tileNum == teeTile) {
				golfBall.onTile = aTile;
				break;
			} else {
				continue;
			}
			throw "no tile for the ball was found.";
		}
	}
}

// Returns a vector of walls as colliders instead
vector<Collider*> GolfCourse::wallsToCollider(vector<Wall> wal) {
	vector < Collider* > temp;

	for (auto colider : wal) {
		temp.push_back(new Wall(colider.wallVert[0], colider.wallVert[1], colider.wallHeight, colider.wallNum));
	}

	return temp;
}

void GolfCourse::putt(Force f) {
	golfBall.addForce(f);
}

void GolfCourse::putt(double dir, double spd) {
	golfBall.addForce(dir, spd);
}

// Goes through file looking for tee and cup
void GolfCourse::decipherFile() {
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
				istringstream(file[x][2]) >> tee.x;
				istringstream(file[x][3]) >> tee.y;
				istringstream(file[x][4]) >> tee.z;
			} else if (file[x][0].compare("cup") == 0) {
				if (cupTile != -1) throw string("another 'cup' data found at line " + to_string(x) +
					", current engine does not support more than 1.");
				cupLine = x;
				istringstream(file[x][1]) >> cupTile;
				istringstream(file[x][2]) >> cup.x;
				istringstream(file[x][3]) >> cup.y;
				istringstream(file[x][4]) >> cup.z;
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
void GolfCourse::inputTiles(vector< vector<string> > &pTiles, vector<int> &lineNum) {
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
				Tile temp (pTiles[x], lineNum[x]);
				tiles.push_back(temp);
			}
		} 
	}
}


// Prints out the course in its entirety
void GolfCourse::printCourse() {
	for (auto &x : tiles) {
		cout << "tile ";
		cout << x.tileNum << " ";
		cout << x.numOfEdges << " ";
		for (auto &y : x.verts) {
			cout << y.x << " " << y.y << " " << y.z << " ";
		}
		for (auto &y : x.neighbors) {
			cout << y << " ";
		}
		cout << endl;
	}

	cout << "tee ";
	cout << teeTile << " ";
	cout << tee.x << " " << tee.y << " " << tee.z << endl;

	cout << "cup ";
	cout << cupTile << " ";
	cout << cup.x << " " << cup.y << " " << cup.z << endl;
}



/////////////////////////////////////////////
// Code for drawing ideally goes down here //
////////////////////////////////////////////



// Used to build a course from given vector
void GolfCourse::buildCourse() {

	printCourse();	

}








