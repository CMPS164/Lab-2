#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

#include "Util/reader.h"
#include "Util/catcher.h"
#include "Physics/rigidbody.h"
#include "golfCourse.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Util/HUD.h"

struct cam_coord {
	float xLoc;
	float yLoc;
	float zLoc;
	float xEye;
	float yEye;
	float zEye;
	//Up Vector is defined as {0,1,0} so we don't need it.
};

//global booleans to switch between the camera views

void setCameraModes(GolfCourse *course);

void HUDCalls(HUD* HUDArg);

void draw_Course(GolfCourse *course);

void userInput(GolfCourse *course);

void keyFunctions(unsigned char key, GolfCourse *course);

GolfCourse* readCourseFile(int argc, char** argv);
