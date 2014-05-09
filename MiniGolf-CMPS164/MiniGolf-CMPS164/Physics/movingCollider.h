//////////////////////////////////////////
// MovingCollider.h                     //
// Moving Collider header               //
// Used for moving objects that collide //
//////////////////////////////////////////

#ifndef MOVINGCOLLIDER_H
#define MOVINGCOLLIDER_H

#include "rigidbody.h"
#include "collider.h"

class RigidSphere: public Rigidbody, public Sphere {
	public:
		float radius;

		// Constructors
		RigidSphere();
		RigidSphere(float r);
		RigidSphere(float r, Force f);
		RigidSphere(float r, Position startLoc);
		RigidSphere(float r, Position startLoc, Force f);

		void addForce(Force f);
		void addForce(double dir, double spd);
		void addForce(double dir, double vDir, double spd);

		void update();
};

#endif