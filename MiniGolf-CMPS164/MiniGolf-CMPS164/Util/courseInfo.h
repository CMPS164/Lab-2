#ifndef COURSEINFO_H
#define COURSEINFO_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "../GolfCourse.h"

using namespace std;

class courseInfo {
public:
	courseInfo(GolfCourse* course);
	int getShotNum();
	void setShotNum(int num);
	int getParValue();
	string getName();
private:
	string course_Name;
	int parValue;
	int shotNum;
};
#endif