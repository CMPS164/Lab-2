#include "courseInfo.h"

courseInfo::courseInfo(GolfCourse* course) {
	course_Name = course->courseName;
	parValue = course->parValue;
	shotNum = 0;
}

string courseInfo::getName() {
	return course_Name;
}

int courseInfo::getShotNum() {
	return shotNum;
}

void courseInfo::setShotNum(int num) {
	shotNum = num;
}

int courseInfo::getParValue() {
	return parValue;
}