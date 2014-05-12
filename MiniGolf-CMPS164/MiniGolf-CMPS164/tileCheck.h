/////////////////////////////////////////////////////
// tileCheck.h                                     //
// Tile checking header							   //
// Used for checking the ball position's in a tile //
/////////////////////////////////////////////////////

#ifndef TILECHECKER_H
#define TILECHECKER_H

#include "golfCourse.h"

class tileCheck {
public:
	//Constructor
	tileCheck(GolfCourse c, Ball courseBall);
	//Accessors, we might need them
	GolfCourse getCourse();
	Ball getBall();

	int getCurLocation();
private:
	GolfCourse course;
	Ball golfBall;
	Position ballLoc;
};















#endif

