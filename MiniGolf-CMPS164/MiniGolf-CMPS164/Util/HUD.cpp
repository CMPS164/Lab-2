#include "HUD.h"
int windowWidth3 = 800;
int windowHeight3 = 600;

HUD::HUD(GolfCourse *course) {
	thisCourse = course;
}

GolfCourse* HUD::returnCourse() {
	return thisCourse;
}

void HUD::drawGUIText(string s, int x, int y) {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth3, 0.0, windowHeight3);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	void * font = GLUT_BITMAP_9_BY_15;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glColor3f(1.0f, 1.0f, 1.0f);
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}