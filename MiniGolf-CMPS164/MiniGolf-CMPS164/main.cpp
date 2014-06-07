/////////////////////////////////
// Lab 2: Golf Course Renderer //
/////////////////////////////////


#include "miniGolfGame.h"
#include "Util/HUD.h"

using namespace std;
int windowWidth2 = 800;
int windowHeight2 = 600;

GolfCourse* course;
HUD* golfHUD;

//Does some of the glut initializations
void init() {
	GLfloat light_Position_0[] = { 1.0f, 1.0f, 1.0f, 0.0f }; //Directional Light
	GLfloat diffuse_0[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat specular_0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient_0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_Position_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

}

/*
*	This is called through glutMainLoop so it draws per frame
*/
void GL_displayFunc() {
	//Clears the buffers. Needed per frame drawn
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set up view matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, windowWidth2 / windowHeight2, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setCameraModes(course);

	//Draws the Golf Course
	HUDCalls(golfHUD);

	draw_Course(course);
	
	course->update();
	glFlush();
	glutSwapBuffers();

	userInput(course);
}


void GL_reshapeFunc(int width, int height) {
	windowWidth2 = width;
	windowHeight2 = height;
	int aspect = width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, aspect, 0.1, 100); // necessary to preserve aspect ratio
	glMatrixMode(GL_MODELVIEW);
}

/*
*	Interactivity for the engine.
*/
void GL_keyboardFunc(unsigned char key, int x, int y) {
	keyFunctions(key, course);
}

void GL_idleFunc() {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	int exitNum = 0;

	course = readCourseFile(argc, argv);
	golfHUD = new HUD(course);
		
	//OpenGL Functions only begin if file reader succeeded
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth2, windowHeight2);
	glutCreateWindow("MiniGolf Rendering");

	init(); //Enables the Lighting in the scene

	glutDisplayFunc(GL_displayFunc);
	glutReshapeFunc(GL_reshapeFunc);
	glutIdleFunc(GL_idleFunc);
	glutKeyboardFunc(GL_keyboardFunc);
	glClearColor(1,1,1,0);
	glutMainLoop();

	return 0;
}