#ifndef HUD_H
#define HUD_H

#include "GL/freeglut.h"
#include <string>
#include "../GolfCourse.h"
#include "playerProfile.h"

using namespace std;

class HUD {
public:
	HUD(GolfCourse *course);	//for each course
	HUD(playerProfile* player); //For the scoreboard
	void drawGUIText(string s, int x, int y);
	void updatePlayer(playerProfile* player);
	GolfCourse* returnCourse();
	playerProfile* returnPlayer();
	void changeCourse(GolfCourse* c);
private:
	GolfCourse *thisCourse;
	playerProfile* thisPlayer;
};

#endif

