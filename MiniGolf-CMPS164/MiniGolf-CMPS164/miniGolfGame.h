#ifndef MINIGOLFGAME_H
#define MINIGOLFGAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

#include "Util/reader.h"
#include "Util/catcher.h"
#include "Physics/rigidbody.h"
#include "golfCourse.h"

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

void HUDResults(HUD* HUDArg);

void draw_Course(GolfCourse *course);

void userInput(GolfCourse *course);

void keyFunctions(unsigned char key, GolfCourse *course);

string readCourseName(int argc, char** argv);

GolfCourse* readCourseFile(int argc, char** argv);

vector<GolfCourse*> readCourseFile2(int argc, char** argv);

#endif

