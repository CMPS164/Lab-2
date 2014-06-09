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
		//velocity -= (velocity / 8) / frameRate;
		float totalVel = velocity.absolute().x + velocity.absolute().y + velocity.absolute().z;

		velocity.x -= (velocity.x / totalVel) * (0.1 / frameRate);
		velocity.y -= (velocity.y / totalVel) * (0.1 / frameRate);
		velocity.z -= (velocity.z / totalVel) * (0.1 / frameRate);
		// velocity -= velocity.singedValues() * 0.01 / frameRate;

		// if too slow stop motion
		if (velocity.absolute().x <= (.01 / frameRate)) {
			velocity.x = 0;
		}
		if (velocity.absolute().y <= (.01 / frameRate)) {
			velocity.y = 0;
		}
		if (velocity.absolute().z <= (.01 / frameRate)) {
			velocity.z = 0;
		}
	}
}