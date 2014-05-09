//////////////////////////////
// Rigidbody.cpp            //
// The rigidbody of objects //
//////////////////////////////

#include "rigidbody.h"

Rigidbody::Rigidbody() : position(Position()) {}

Rigidbody::Rigidbody(Force f) : position(Position()) {
	addForce(f);
}

Rigidbody::Rigidbody(Position p) : position(p) {}

Rigidbody::Rigidbody(Position p, Force f) : position(p) {
	addForce(f);
}

void Rigidbody::addForce(Force f) {
	velocity += f.buildVector();
}

void Rigidbody::addForce(double dir, double spd) {
	velocity += Force(dir, spd).buildVector();
}

void Rigidbody::addForce(double dir, double vDir, double spd) {
	velocity += Force(dir, vDir, spd).buildVector();
}

// Objects update, for pretty much everything that needs to be remade
void Rigidbody::update() {
	if (velocity.moving()) {
		position.x += velocity.x / frameRate;
		position.y += velocity.y / frameRate;
		position.z += velocity.z / frameRate;
	}
	if (grounded) {
		// Simulate rolling friction for now
		velocity -= velocity.singedValues() * 0.01/frameRate;
		if (velocity.absolute() <= .01)
			velocity = 0;
	}
}