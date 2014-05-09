////////////////////////////
// force.h                //
// Force header           //
// Used for adding forces //
////////////////////////////

#ifndef FORCE_H
#define FORCE_H

#include "vector3.h"
#include "../Util/catcher.h"

class Force {
	private:
		Catcher mitt;
		double direction, vertDirection;

	public:
		double speed;

		// Constructors
		Force();
		Force(double dir, double spd);
		Force(double dir, double vDir, double spd);

		// Sets x and z direction, checks value to be between 0 and 360 inclusive
		// 0 will be forward or the -z direction and 90 will be +x direction
		void setDirection(double dir);

		// Sets y direction, checks value to be between -90 and 90
		// -90 will be -y(Down), 0 no vertical movement, 90 +y (Up)
		void setVDirection(double vDir);

		Vector3 buildVector();
};

#endif