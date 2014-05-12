/////////////////////////////////////
// Rigidbody.h                     //
// Rigidbody header                //
// Used for movement and collision //
/////////////////////////////////////

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <iostream>

#include "force.h"
#include "vector3.h"
#include "position.h"

using namespace std;

class Rigidbody {
public:
	double frameRate = 33;
	Vector3 velocity = Vector3();			// Velocity object of this class
	Position position;						// Position object of this class
	bool grounded = true;					// Whether the object is touching ground

	// Constructors
	Rigidbody();
	Rigidbody(Force f);
	Rigidbody(Position p);
	Rigidbody(Position p, Force f);

	void addForce(Force f);
	void addForce(double dir, double spd);
	void addForce(double dir, double vDir, double spd);

	void update();
};

#endif