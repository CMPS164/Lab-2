////////////////////////////
// Force.cpp              //
// Used for adding forces //
////////////////////////////

#include <math.h> 

#include "force.h"

#define PI 3.14159265

Force::Force() : direction(0), vertDirection(0), speed(0) {}

Force::Force(double dir, double spd) : vertDirection(0), speed(spd) {
	setDirection(dir);
}

Force::Force(double dir, double vDir, double spd) : direction(dir), vertDirection(vDir), speed(spd) {
	setDirection(dir);
	setVDirection(vDir);
}

// Sets x and z direction, checks value to be between 0 and 360 inclusive
// 0 will be forward or the -z direction and 90 will be +x direction
void Force::setDirection(double dir) {
	while (dir < 0 || dir > 360) {
		dir = mitt.reEnterNum("Direction angle must be between 0 and 360, would you like to input a new angle? (y/n)",
			"Enter new angle (0 - 360): ", "direction angle was not between 0 - 360");
	}
	direction = dir;
}

// Sets y direction, checks value to be between -90 and 90
// -90 will be -y(Down), 0 no vertical movement, 90 +y (Up)
void Force::setVDirection(double vDir) {
	while (vDir < -90 || vDir > 90) {
		vDir = mitt.reEnterNum("Vertical angle must be between -90 and 90, would you like to input a new angle? (y/n)",
			"Enter new angle(-90 - 90): ", "vertical angle was not between -90 - 90");
	}
	vertDirection = vDir;
}

// For now, this only does x and z directions
Vector3 Force::buildVector() {
	return Vector3(sin(direction * PI / 180) * speed, 0, -cos(direction * PI / 180) * speed);
}