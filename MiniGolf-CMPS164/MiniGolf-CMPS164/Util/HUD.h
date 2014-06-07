<<<<<<< HEAD
#ifndef HUD_H
#define HUD_H

#include "GL/glew.h"
#include "GL/freeglut.h"
=======
#include "GL/glew.h"
#include "GL/freeglut.h"

>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
#include <string>
#include "../GolfCourse.h"

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
class HUD {
public:
	HUD(GolfCourse *course);
	void drawGUIText(string s, int x, int y);
	GolfCourse* returnCourse();
private:
	GolfCourse *thisCourse;
<<<<<<< HEAD
};

#endif
=======
};
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
