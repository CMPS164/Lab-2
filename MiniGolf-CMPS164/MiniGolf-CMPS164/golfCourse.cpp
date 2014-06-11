////////////////////////////////////
// GolfCourse.cpp                 //
// Builds course from vector file //
////////////////////////////////////

#include <iostream>
#include <sstream>

#include "golfCourse.h"
#include <cmath>

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

void Ball::update() {
	RigidSphere::update();
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
	int tileEdgeNum = 0;
	Vertex v1;
	Vertex v2;

	for (int index = 0; index < neighbors.size(); ++index) {
		if (neighbors.at(index) == 0) { //There is no connecting tile and thus is an edge
			wallNum++;
			
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
		} else {
			//This is an Invisible Edge for Tile Checks
			tileEdgeNum = neighbors.at(index);
			//cout << " " << tileEdgeNum << " ";
			//Take the vertex indices and create a new vector for a wall.
			if (index == neighbors.size() - 1) {
				//This check is for the case if there is no edge between the last vertice and the first one in the vector, thus we need to 'loop' around
				v1 = verts.at(index);
				v2 = verts.at(0);
			} else {
				v1 = verts.at(index);
				v2 = verts.at(index + 1);
			}
		//	TriggerWall temp2(v1, v2, 0.1, tileEdgeNum);
		//	triggerWalls.push_back(temp2);
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

/*
//Wall Constructor
TriggerWall::TriggerWall(Vertex v1, Vertex v2, float wHeight, int wNum) : Quad(){
	wallNum = wNum;	//Unknown what to do with WallNum, here just in case
	wallHeight = wHeight;
	//Four vertices for the Edge
	wallVert.push_back(Vertex(v1.x, v1.y, v1.z));
	wallVert.push_back(Vertex(v2.x, v2.y, v2.z));
	wallVert.push_back(Vertex(v2.x, v2.y + wallHeight, v2.z));
	wallVert.push_back(Vertex(v1.x, v1.y + wallHeight, v1.z));

	isPhysical = false;

	setVertices(wallVert);
} 

void TriggerWall::onCollision() {
	newTileNum = wallNum;
}

void TriggerWall::update() {
	Quad::update();
}
*/
/*
// Constructor
GolfCourse::GolfCourse(vector< vector<string> > newFile) {
	file = newFile;

	// Used for checking later
	teeTile = -1;
	cupTile = -1;

	decipherFile();
	setBall();
	newTileNum = getTeeTile();
	shotNum = 0; 
	totalShotNum = shotNum;
	endCourse = false;

}
*/
// Constructor
GolfCourse::GolfCourse(vector< vector<string> > newFile) {
	file = newFile;

	// Used for checking later
	teeTile = -1;
	cupTile = -1;

	decipherFile2();
	setBall();
	newTileNum = getTeeTile();
	shotNum = 0;
	parValue; //changes per golfCourse
	totalShotNum = shotNum;
	courseName == "";
	endCourse = false;

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


int GolfCourse::getTeeTile() {
	return teeTile;
}

int GolfCourse::getCupTile() {
	return cupTile;
}

// Sets ball onto tee
void GolfCourse::setBall() {
	golfBall = Ball(0.025, getTee());
	setBallTile(teeTile);
	golfBall.setCollisionObjects(wallsToCollider(golfBall.onTile.walls));
	//golfBall.addCollisionObjects(triggerWallsToCollider(golfBall.onTile.triggerWalls));
}

// Sets balls tile num and checks if tile in vector matches tile num
// Correctly runs through vector if it doesn't to find matching tile
void GolfCourse::setBallTile(int num) {
	golfBall.tileNum = num;

	if (tiles[num - 1].tileNum == num) {
		golfBall.onTile = tiles[num - 1];
	} else {
		for (auto aTile : tiles) {
			if (aTile.tileNum == num) {
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

/*
vector<Collider*> GolfCourse::triggerWallsToCollider(vector<TriggerWall> wal) {
	vector < Collider* > temp;

	for (auto colider : wal) {
		temp.push_back(new TriggerWall(colider.wallVert[0], colider.wallVert[1], colider.wallHeight, colider.wallNum));
	}

	return temp;
} */

void GolfCourse::putt(Force f) {
	golfBall.addForce(f);
	golfBall.velocity -= (golfBall.onTile.getNormal() * ((golfBall.velocity.dotProduct(golfBall.onTile.getNormal())) / (golfBall.onTile.getNormal().dotProduct(golfBall.onTile.getNormal()))));
}

void GolfCourse::putt(double dir, double spd) {
	golfBall.addForce(dir, spd);
	golfBall.velocity -= (golfBall.onTile.getNormal() * ((golfBall.velocity.dotProduct(golfBall.onTile.getNormal())) / (golfBall.onTile.getNormal().dotProduct(golfBall.onTile.getNormal()))));
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

void GolfCourse::decipherFile2() {
	vector< vector<string> > pTiles;	// Stores that vectors that might be tiles
	vector<int> lineNum;

	// Goes through the vectors looking for tee and cup
	// If error is found, print whats wrong and exits out
	// Correct and non tee/cup lines will be inserted into another vector
	for (unsigned int x = 0; x < file.size(); ++x) {
		if (file[x].size() < 1) {
			throw string("not enough information on line " + to_string(x) + ".");
		} else if (file[x][0].compare("name") == 0) {
			stringstream tempStr;
			for (int tempI = 1; tempI < file[x].size(); tempI++) {
				tempStr << file[x][tempI] << " ";
			}
			courseName = tempStr.str();
		} else if (file[x].size() == 2) {
			if (file[x][0].compare("par") == 0) {
				istringstream(file[x][1]) >> parValue;
				
			}
			
		} else if (file[x].size() == 5) {
			if (file[x][0].compare("tee") == 0) {
				if (teeTile != -1) throw string("another 'tee' data found at line " + to_string(x) +
					", current engine does not support more than 1.");
				teeLine = x;
				istringstream(file[x][1]) >> teeTile;
				istringstream(file[x][2]) >> tee.x;
				istringstream(file[x][3]) >> tee.y;
				istringstream(file[x][4]) >> tee.z;
			}
			else if (file[x][0].compare("cup") == 0) {
				if (cupTile != -1) throw string("another 'cup' data found at line " + to_string(x) +
					", current engine does not support more than 1.");
				cupLine = x;
				istringstream(file[x][1]) >> cupTile;
				istringstream(file[x][2]) >> cup.x;
				istringstream(file[x][3]) >> cup.y;
				istringstream(file[x][4]) >> cup.z;
			}
			else {
				throw string("data at line " + to_string(x) + " has an incorrect tag.");
			}
		}
		else {
			pTiles.push_back(file[x]);
			lineNum.push_back(x);
		}
	}

	if (teeTile == -1) mitt.cont("No tee data found, would you like to continue? (y/n)", "tee data is missing.");
	if (cupTile == -1) mitt.cont("No cup data found, would you like to continue? (y/n)", "cup data is missing.");

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

// Updates everything that needs to be updated in this file
void GolfCourse::update() {	

	int oldTileNum = golfBall.tileNum;
	golfBall.tileNum = checkCurLoc();
	// If tile number has changed, switch the tile on ball and get new collision list
	if (golfBall.tileNum != oldTileNum) {
		setBallTile(golfBall.tileNum);
		golfBall.setCollisionObjects(wallsToCollider(golfBall.onTile.walls));
		golfBall.velocity -= (golfBall.onTile.getNormal() * ((golfBall.velocity.dotProduct(golfBall.onTile.getNormal())) / (golfBall.onTile.getNormal().dotProduct(golfBall.onTile.getNormal()))));
	}

	//Intersection Test for Ball and Cup
	//Only run if the golfBall's current tile is the same as the cup tile
	if (golfBall.tileNum == cupTile) {
		//Using the sphere class as a collider for the cup
		Sphere cupCollider = Sphere(getCup(), (golfBall.ballRadius * 2));
		bool ballCupIntersect = cupCollider.sphereCollide(golfBall.position, golfBall.ballRadius);

		/*
		if (golfBall.velocity != Vector3()) {
			cout << "Velocity: " << golfBall.velocity.x << " " << golfBall.velocity.y << " " << golfBall.velocity.z << endl;
		}
		*/
		if (ballCupIntersect) {

			//Check if the velocity of the ball is too fast
			if (golfBall.velocity.absolute() <= Vector3(0.1, 0.1, 0.1)) {
				golfBall.velocity = 0;	//Stops the ball
				totalShotNum = shotNum;
				endCourse = true;
			}
			else {
				//Change the ball's direction and use its current velocity to create the "lip out" effect

			}
		}
	}
	golfBall.update();
}

//Checks the golfBall's current Tile Location
int GolfCourse::checkCurLoc() {
	//iterates through each tile for its vertices
	for (int t = 0; t < golfBall.onTile.neighbors.size(); t++) {
		if (golfBall.onTile.neighbors[t] - 1 < 0) continue;
		Tile tile = tiles.at(golfBall.onTile.neighbors[t] - 1);

		if (tile.tileNum != golfBall.onTile.neighbors[t]){
			for (auto tt : tiles) {
				if (tt.tileNum == (golfBall.onTile.neighbors[t]))
					tile = tt;
			}
		}
		

		vector<Vertex> temp = formRay(tile.verts);
		
		//Now we need to test all sides of a tile with the calculated ray for intersection
		vector <Vertex> sides_a, sides_b;
		double y_average = 0;	//This tests for cases where tiles overlap
		for (int s = 0; s < tile.verts.size(); s++) {
			Vertex a, b;
			y_average += tile.verts.at(s).y;
			if (s == tile.verts.size() - 1) {
				//Final side loops back to initial vertex
				a = tile.verts.at(s);
				b = tile.verts.at(0);
			}
			else {
				//Otherwise
				a = tile.verts.at(s);
				b = tile.verts.at(s + 1);
			}

			//These will be iterated at the same time
			sides_a.push_back(a); //Holds all first vertices/start points

			sides_b.push_back(b); //Hold all second vertices/end points
		}
		y_average = y_average / tile.verts.size();	//Average

		//Testing ray against all sides for intersections
		int intersections = 0;
		for (int side = 0; side < tile.numOfEdges; side++) {
			//Test here
			//If True, increment intersection
			bool testResult = intersectionTest(temp.at(0), temp.at(1), sides_a.at(side), sides_b.at(side));
			if (testResult) intersections++;
		}
		//The points lies in the polygon/tile if the # of intersections is odd
		if ((intersections & 1) == 1) {
			//inside
			if (abs(y_average - golfBall.position.y) >= 0) {
				return tile.tileNum;
			}

		}
	}
	// Hasn't switched tiles yet
	// Return current tilenum
	return golfBall.onTile.tileNum;
	// throw "ball is not in any tile";
	//return 0;
}

//Used for creating a ray for tile checking using ray casting
vector<Vertex> GolfCourse::formRay(vector <Vertex> vertices) {
	//Loop through all vertices to find XMin/Max and ZMin/Max
	//I'm ignoring Y for now
	//This is for changes in this code to find a Ray for testing
	double xMin = 0, xMax = 0, zMin = 0, zMax = 0;
	double epsilon = 0.001;

	for (int i = 0; i < vertices.size(); i++) {
		if (i == 0) {
			xMin = xMax = vertices.at(i).x;
			zMin = zMax = vertices.at(i).z;
		}
		else {
			if (vertices.at(i).x <= xMin) { xMin = vertices.at(i).x; }
			else if (vertices.at(i).x >= xMax) { xMax = vertices.at(i).x; }
			if (vertices.at(i).z <= zMin) { zMin = vertices.at(i).z; }
			else if (vertices.at(i).z >= zMax) { zMax = vertices.at(i).z; }
		}
	}

	vector<Vertex> v_List;
	//I'm using Vectors to simulate vertices
	//This needs to change to reflect the Ball's current position
	Vertex v1 = Vertex(xMin - epsilon, 0, golfBall.position.z);	//Start
	Vertex v2 = Vertex(golfBall.position.x, 0, golfBall.position.z);	//End
	v_List.push_back(v1);
	v_List.push_back(v2);

	return v_List;
}

//Intersection Method
//See this link: http://stackoverflow.com/questions/217578/point-in-polygon-aka-hit-test
bool GolfCourse::intersectionTest(Vertex v1a, Vertex v1b, Vertex v2a, Vertex v2b) {
	float d1, d2;
	float a1, a2, b1, b2, c1, c2;
	
	//Convert Vector 1 into a line
	//Vector 1 are the start and end points defined from v1a and v1b
	//Line Equation Ax + By + C = 0; we are using Bz instead
	a1 = v1b.z - v1a.z;
	b1 = v1a.x - v1b.x;
	c1 = (v1b.x * v1a.z) - (v1a.x * v1b.z);

	//Every point (x,z) that solves the equation above is on the line
	//Otherwise its above or below it
	//Insert the points of Vector 2 into the above equation
	d1 = (a1 * v2a.x) + (b1 * v2a.z) + c1;
	d2 = (a1 * v2b.x) + (b1 * v2b.z) + c1;

	//if d1 and d2 have the same sign, then no intersection is possible due to being on the same side
	//Don't test 0; it means its on the line
	if ((d1 > 0 && d2 > 0) || (d1 < 0 && d2 < 0)) return false;

	//Do the same thing for Vector 2 as Vector 1
	//and plug in the values of Vector 1 to test
	a2 = v2b.z - v2a.z;
	b2 = v2a.x - v2b.x;
	c2 = (v2b.x * v2a.z) - (v2a.x * v2b.z);

	d1 = (a2 * v1a.x) + (b2 * v1a.z) + c2;
	d2 = (a2 * v1b.x) + (b2 * v1b.z) + c2;

	if ((d1 > 0 && d2 > 0) || (d1 < 0 && d2 < 0)) return false;

	//Collinear tests don't count for collision so return false
	//Collinear means the vectors instersect infinitely many times
	if ((a1 * b2) - (a2 * b1) == 0) return false;

	//Reach here, the vectors have to intersect once
	return true;
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
/////////////////////////////////////////////



// Used to build a course from given vector
void GolfCourse::buildCourse() {

	printCourse();	

}








