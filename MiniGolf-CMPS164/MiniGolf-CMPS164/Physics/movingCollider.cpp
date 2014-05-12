//////////////////////////////////////////
// MovingCollider.cpp                   //
// Used for moving objects that collide //
//////////////////////////////////////////

#include "movingCollider.h"

MovingCollider::MovingCollider() : Rigidbody() {}

MovingCollider::MovingCollider(Force f) : Rigidbody(f) {}

MovingCollider::MovingCollider(Position startLoc) : Rigidbody(startLoc) {}

MovingCollider::MovingCollider(Position startLoc, Force f) : Rigidbody(startLoc, f) {}

void MovingCollider::setCollisionObjects(vector<Collider*> colObjects) {
	possibleCollisions = colObjects;
}

void MovingCollider::addCollisionObjects(Collider* colObjects) {
	possibleCollisions.push_back(colObjects);
}

void MovingCollider::addCollisionObjects(vector<Collider*> colObjects) {
	possibleCollisions.insert(possibleCollisions.end(), colObjects.begin(), colObjects.end());
}

RigidSphere::RigidSphere() : MovingCollider(), Sphere(){
	radius = 1;
}

RigidSphere::RigidSphere(float r) : MovingCollider(), Sphere(r) {
	radius = r;
}

RigidSphere::RigidSphere(float r, Force f) : MovingCollider(f), Sphere(r) {
	radius = r;
}

RigidSphere::RigidSphere(float r, Position startLoc) : MovingCollider(startLoc), Sphere(startLoc, r){
	radius = r;
}

RigidSphere::RigidSphere(float r, Position startLoc, Force f) : MovingCollider(startLoc, f), Sphere(startLoc, r) {
	radius = r;
}

void RigidSphere::addForce(Force f) {
	velocity += f.buildVector();
}

void RigidSphere::addForce(double dir, double spd) {
	velocity += Force(dir, spd).buildVector();
}

void RigidSphere::addForce(double dir, double vDir, double spd) {
	velocity += Force(dir, vDir, spd).buildVector();
}

void RigidSphere::update() {
	if (willCollide) {
	} else {
		if (velocity.moving()) {
			position += Position(velocity.x / frameRate, velocity.y / frameRate, velocity.z / frameRate);
			center = position;
		}
		if (grounded) {
			// Simulate rolling friction for now
			velocity -= velocity.singedValues() * 0.01 / frameRate;
			if (velocity.absolute() <= .01)
				velocity = 0;
		}
		if (possibleCollisions.size() > 0) {
			for (auto collides : possibleCollisions) {
				if (collides->sphereCollide(position + Position(velocity.x / frameRate, velocity.y / frameRate, velocity.z / frameRate), radius)) {
					willCollide = true;
					break;
				}
			}
		}
	}
}