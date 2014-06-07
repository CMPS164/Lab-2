/////////////////////////////////
// Lab 2: Golf Course Renderer //
/////////////////////////////////

<<<<<<< HEAD
#include "miniGolfGame.h"
#include "Util/HUD.h"
=======
<<<<<<< HEAD
#include "miniGolfGame.h"
=======
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Util/reader.h"
#include "Util/catcher.h"
#include "Physics/rigidbody.h"
#include "golfCourse.h"
>>>>>>> e686ba5a3fddee720ad8009f905c0a072565bb91
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95

using namespace std;
int windowWidth2 = 800;
int windowHeight2 = 600;

GolfCourse* course;
HUD* golfHUD;
<<<<<<< HEAD
=======

double force, direction = 0;
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95

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

<<<<<<< HEAD
=======
void userInputShots() {
	
	if (course->golfBall.velocity == (Vector3())) { //If the ball isn't moving
		
		cout << "//////////" << endl << "Shot #" << course->shotNum << endl;
		while (true) {
			cout << "Please Enter a Direction value from 0 to 360: " << endl;
			string input;
			getline(cin, input);
			stringstream myInput(input);
			if (myInput >> direction) {
				cout << "Success " << direction << endl;
				while (true) {
					cout << "Please enter a Force value from 0.0 to 1.0" << endl;
					getline(cin, input);
					stringstream myInput(input);
					if (myInput >> force) {
						cout << "Success 2! " << force << endl;
						course->putt(direction, force);
						course->shotNum++;

						break;
					}
					else {
						cout << "Not a valid force value" << endl;
					}
				}
				break;
			}
			else {
				cout << "Not a valid direction value" << endl;
			}
		}
	}

}

void drawGUIText(string s, int x, int y){
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
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

void HUD() {
	glColor3f(0, 0, 0);
	drawGUIText("MiniGolf Game Engine", 10, windowHeight - 20); //Once Refactoring is done, get the current course number and place it here                                              
	drawGUIText("Shot Number: " + to_string(course->shotNum), 10, windowHeight - 40); //Course has a shotNum property. Gets incremented per shot
	drawGUIText("Inputted Direction: " + to_string(direction), 10, windowHeight - 60);
	drawGUIText("Inputted Force: " + to_string(force), 10, windowHeight - 80);
	drawGUIText("Course Number: 1", 10, windowHeight - 100);
}

>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
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
<<<<<<< HEAD

	HUDCalls(golfHUD);
=======
<<<<<<< HEAD
	HUDCalls(golfHUD);
=======
	HUD();
>>>>>>> e686ba5a3fddee720ad8009f905c0a072565bb91
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
	draw_Course(course);
	
	course->update();
	glFlush();
	glutSwapBuffers();
<<<<<<< HEAD
	userInput(course);
=======
<<<<<<< HEAD

	userInput(course);
=======
	
	userInputShots();
>>>>>>> e686ba5a3fddee720ad8009f905c0a072565bb91
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
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
<<<<<<< HEAD

	course = readCourseFile(argc, argv);
	golfHUD = new HUD(course);
				
=======

	course = readCourseFile(argc, argv);
	golfHUD = new HUD(course);
		
<<<<<<< HEAD
=======
		course = new GolfCourse(file);
		//course->golfBall.position = Position(-.75, 0, 1);
		//course->golfBall.position = Position(0.75, 0, 0.6);
		
		//course->putt(Force (0, 1));
		//course->putt(Force(0, 1));
		//course->putt(Force (46, .37));

		//These parameters define gluLookAt for third person view. This is dependant on the ball's changing position.
		third_person_ball = {course->getTee().x, course->getTee().y + 0.4, course->getTee().z + 0.3,
				course->getTee().x, course->getTee().y, course->getTee().z };
	} catch (string error) {
		// Reports error and changes the exit value
		cout << "Program exited because ";
		cout << error << endl;
		exit(EXIT_FAILURE);
	}

	cout << "CMPS164 Game Engines Lab 2 by Francis Tang and Kenneth Thieu" << endl;
	cout << "This is a temporary implemention of user interactivity with the engine." << endl << "The features and controls are thus limited." << endl;
	cout << "The perspective of the camera is locked at 90 Degrees Field of View" << endl << "with a near clip of 0.1 and a far clip of 100" << endl;
	cout << "It also operates with the depth in the negative Z-axis" << endl;
	cout << "However, the camera configurations may be altered with the following controls: " << endl;
	cout << "'A' or 'D' keys to move the camera position in the negative/positive x-axis respectively" << endl;
	cout << "'W' or 'S' keys to move the camera position in the positive/negative x-axis respectively" << endl;
	cout << "'Q' or 'E' keys to move the camera position in the positive/negative x-axis respectively" << endl;
	cout << "'R' to reset the camera positions to default" << endl;
	cout << "To have the camera focus on either the origin, tee, or cup, we have the following controls: " << endl;
	cout << "'T' to focus on the Tee" << endl;
	cout << "'O' to focus on the Origin" << endl;
	cout << "'C' to focus on the Cup" << endl;

	/*
	for (auto tile : course->getTiles()) {
		cout << "Tile # " << tile.tileNum << " and the number of Walls are " << tile.walls.size() << " and the number of border checks are " << tile.triggerWalls.size() << endl;
		for (auto Wall : tile.triggerWalls) {
			cout << "Tile to enter is numbered " << Wall.wallNum << endl;
			//cout << "V1 is <" << Wall.wallVert.at(0).x << " " << Wall.wallVert.at(0).y << " " << Wall.wallVert.at(0).z << "> and V2 is <" << Wall.wallVert.at(1).x << " " << Wall.wallVert.at(1).y << " " << Wall.wallVert.at(1).z << ">" << endl;
		}
	}*/
	

>>>>>>> e686ba5a3fddee720ad8009f905c0a072565bb91
>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95
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

<<<<<<< HEAD
	glClearColor(1.0f, 1.0f, 1.0f, 0);

	glClearColor(1,1,1,0);

	glutMainLoop();
=======
<<<<<<< HEAD
	glClearColor(1.0f, 1.0f, 1.0f, 0);
=======
	glClearColor(0,0,1,0);
>>>>>>> e686ba5a3fddee720ad8009f905c0a072565bb91
	glutMainLoop();

>>>>>>> 744727c3b4c908a05c34202b48adb3f013a38d95

	return 0;
}