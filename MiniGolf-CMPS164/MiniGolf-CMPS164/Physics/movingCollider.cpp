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

void MovingCollider::onCollision() {

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

void RigidSphere::onCollision() {
}

void RigidSphere::update() {
	if (willCollide) {
		Collider::update();
		//velocity();
		if (isPhysical && otherIsPhysical) {
			velocity = velocity - (collisionNormal * 2 * velocity.dotProduct(collisionNormal));
		}
		willCollide = false;
	} else {
		if (velocity.moving()) {
			position += Position(velocity.x / frameRate, velocity.y / frameRate, velocity.z / frameRate);
			center = position;
			if (grounded) {
				// Simulate rolling friction for now
				float totalVel = velocity.absolute().x + velocity.absolute().y + velocity.absolute().z;
				
				velocity.x -= (velocity.x / totalVel) * (0.1 / frameRate);
				velocity.y -= (velocity.y / totalVel) * (0.1 / frameRate);
				velocity.z -= (velocity.z / totalVel) * (0.1 / frameRate);
				
				// velocity -= (velocity / 8)/frameRate;

				//velocity -= (velocity.singedValues() * (0.01 / frameRate));
				if (velocity.absolute().x <= (.1 / frameRate)) {
					velocity.x = 0;
				}
				if (velocity.absolute().y <= (.1 / frameRate)) {
					velocity.y = 0;
				}
				if (velocity.absolute().z <= (.1 / frameRate)) {
					velocity.z = 0;
				}
			}
		}
		

		if (possibleCollisions.size() > 0) {
			for (auto collides : possibleCollisions) {
				collisionNormal = collides->getCollisionVector();
				if (collisionNormal.dotProduct(velocity) != 0) {	// If parallel to velocity, will not check
					if (collides->sphereCollide(position + Position(velocity.x / frameRate, velocity.y / frameRate, velocity.z / frameRate), radius)) {
						willCollide = true;
						collides->willCollide = true;
						otherIsPhysical = collides->isPhysical;
						collides->update();
						break;
					}
				}
			}
		}
	}
}