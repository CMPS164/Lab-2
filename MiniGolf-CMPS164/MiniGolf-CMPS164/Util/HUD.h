#include "GL/glew.h"
#include "GL/freeglut.h"

#include <string>
#include "../GolfCourse.h"

using namespace std;
class HUD {
public:
	HUD(GolfCourse *course);
	void drawGUIText(string s, int x, int y);
	GolfCourse* returnCourse();
private:
	GolfCourse *thisCourse;
};