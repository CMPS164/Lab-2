/////////////////////////////////////////////////////
// tileCheck.cpp                                   //						   //
// Used for checking the ball position's in a tile //
/////////////////////////////////////////////////////

#include "tileCheck.h"

tileCheck::tileCheck(GolfCourse c, Ball courseBall) : course(c), golfBall(courseBall) {
	//Ball's starting Location given by course
	ballLoc = course.getTee();
};

int tileCheck::getCurLocation() {
	return 0;

}