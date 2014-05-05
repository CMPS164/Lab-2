/////////////////////////////////
// Lab 2: Golf Course Renderer //
/////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include "GL/glew.h"
#include "GL/freeglut.h"


#include "reader.h"
#include "catcher.h"
#include "golfCourse.h"

using namespace std;

//Placeholder. Eventually will allow User customizable window parameters
 int windowWidth = 800;
 int windowHeight = 600;
 //For gluLookAt

struct cam_coord {
	float xLoc;
	float yLoc;
	float zLoc;
	float xEye;
	float yEye;
	float zEye;
	//Up Vector is defined as {0,1,0} so we don't need it.
};

//Global Golf_Course object
golfCourse* course;
cam_coord default{0, 3, 5, 0, 0, 0};
cam_coord third_person_ball{ 0, 0, 0, 0, 0, 0 };
cam_coord top_down{ 0, 3, 0, 0, 0, 0 };

//global booleans to switch between the camera views
bool default_cam = true;
bool third_person_cam = false;
bool top_down_cam = false;

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
*	This calculates FACE NORMALS. One per tile
*/
void calc_Normal(array<double, 3> &result, array<double, 3> v1, array<double,3> v2, array<double,3> v3) {
	array<double, 3> vector_1;
	vector_1[0] = v1[0] - v3[0];
	vector_1[1] = v1[1] - v3[1];
	vector_1[2] = v1[2] - v3[2];

	array<double, 3> vector_2;
	vector_2[0] = v2[0] - v1[0];
	vector_2[1] = v2[1] - v1[1];
	vector_2[2] = v2[2] - v1[2];

	//Cross Product calculation
	result[0] = (vector_1[1] * vector_2[2]) - (vector_1[2] * vector_2[1]);
	result[1] = -1*((vector_1[0] * vector_2[2]) - (vector_1[2] * vector_2[0]));
	result[2] = (vector_1[0] * vector_2[1]) - (vector_1[1] * vector_2[0]);

	//Calculating Magnitude
	float total = pow(result[0], 2) + pow(result[1], 2) + pow(result[2], 2);
	float magnitude = sqrt(total);

	//Getting Normalized
	result[0] = result[0] / magnitude;
	result[1] = result[1] / magnitude;
	result[2] = result[2] / magnitude;
}

/*
*	This function draws the golf course through primitives.
*	In the future, we need to change this as fixed functional pipeline
*	is deprecated in current openGL standards
*/
void draw_Course(golfCourse* course) {
	vector<tile> tiles = course->getTiles();
	for (auto tile : tiles) {
		vector< array<double, 3> > vertices = tile.vertices;
		vector<wall> edges = tile.walls;

		//Get Face Normal
		array<double, 3> useNormal;
		calc_Normal(useNormal, vertices.at(0), vertices.at(1), vertices.at(vertices.size() - 1));
		
		glPushMatrix();
		//Drawing the polygon, counter-clockwise
		glBegin(GL_POLYGON);
		glNormal3f(useNormal[0], useNormal[1], useNormal[2]);
		for (auto vertex : vertices) {
			float x_Coord = vertex[0];
			float y_Coord = vertex[1];
			float z_Coord = vertex[2];

			glColor3f(0.0f, 1.0f, 0.0f); //Blue
			glVertex3f(x_Coord, y_Coord, z_Coord);
		}
		glEnd();
		glPopMatrix();

		//Drawing is done through wall structs as discussed in lab.
		//Feel free to remove this if the code works fine. Works okay with me
		/*
		//Checking and Drawing Edges
		for (int index = 0; index < neighbors.size(); ++index) {
			if (neighbors.at(index) == 0) { //There is no connecting tile and thus is an edge
				array<double, 3> v1;
				v1[0] = v1[1] = v1[2] = 0.0;
				array<double, 3> v2;
				v2[0] = v2[1] = v2[2] = 0.0;

				//Take the vertex indices and create a new vector for a wall.
				if (index == neighbors.size() - 1) {
					//This check is for the case if there is no edge between the last vertice and the first one in the vector, thus we need to 'loop' around
					v1 = vertices.at(index);
					v2 = vertices.at(0);
				}
				else {
					v1 = vertices.at(index);
					v2 = vertices.at(index + 1);
				}

				//After having both v1 and v2 defined...make a wall
				//counter clockwise drawing
				glPushMatrix();
				glBegin(GL_POLYGON);
				glColor3f(1.0f, 0.0f, 0.0f); //Red
				glNormal3f(1.0f, 1.0f, 1.0f);
				glVertex3f(v1[0], v1[1], v1[2]);
				glVertex3f(v2[0], v2[1], v2[2]);
				glVertex3f(v2[0], v2[1] + 0.1, v2[2]);
				glVertex3f(v1[0], v1[1] + 0.1, v1[2]);
				glEnd();
				glPopMatrix();
			}
		}
		*/

		//Drawing the polygon
		for (auto wall : edges) {
			
			glPushMatrix();
			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f); //Red
			glNormal3f(1.0f, 1.0f, 1.0f); //Possibly need to change normal calculation for better lighting?
			glVertex3f(wall.wall_v1[0], wall.wall_v1[1], wall.wall_v1[2]);
			glVertex3f(wall.wall_v2[0], wall.wall_v2[1], wall.wall_v2[2]);
			glVertex3f(wall.wall_v2h[0], wall.wall_v2h[1], wall.wall_v2h[2]);
			glVertex3f(wall.wall_v1h[0], wall.wall_v1h[1], wall.wall_v1h[2]);
			glEnd();
			glPopMatrix();
		}
	}

	//Drawing the tee
	array<double, 3> teeLoc = course->getTee();
	array<double, 3> cupLoc = course->getCup();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(teeLoc[0], teeLoc[1] + 0.025, teeLoc[2]);
	glutSolidSphere(0.025, 360, 360);
	glPopMatrix();

	//Drawing the cup
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(cupLoc[0], cupLoc[1] + 0.025, cupLoc[2]);

	//This draws a cylinder as the cup. 
	//*INCOMPLETE*
	/*
	GLUquadric* temp = gluNewQuadric();
	gluQuadricNormals(temp, GL_SMOOTH);
	glRotatef(90, 1, 0, 0);
	gluCylinder(temp, 0.03, 0.03, 0.05, 360, 360); //I need to fix this.
	*/
	glutSolidSphere(0.025, 360, 360);
	glPopMatrix();
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
	//gluPerspective(90, windowWidth/windowHeight, 0.1, 100);
//	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	if (third_person_cam) {
		gluPerspective(90, windowWidth / windowHeight, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(third_person_ball.xLoc, third_person_ball.yLoc, third_person_ball.zLoc, third_person_ball.xEye, third_person_ball.yEye, third_person_ball.zEye, 0, 1, 0);
	}
	else if (top_down_cam) {
		gluPerspective(90, windowWidth / windowHeight, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(top_down.xLoc, top_down.yLoc, top_down.zLoc, top_down.xEye, top_down.yEye, top_down.zEye, 0, 0, 1);
	}
	else {
		gluPerspective(90, windowWidth / windowHeight, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(default.xLoc, default.yLoc, default.zLoc, default.xEye, default.yEye, default.zEye, 0, 1, 0);
		
	}

	//Draws the Golf Course
	draw_Course(course);

	glFlush();
	glutSwapBuffers();
}

void GL_reshapeFunc(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	int aspect = width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, aspect, 0.1, 100); // necessary to preserve aspect ratio
	glMatrixMode(GL_MODELVIEW);
}

/*
*	Interactivity for the engine. In the future, we need a proper UI
*/
void GL_keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		if (default_cam) {
			default.yLoc += 0.1;
		}
		break;
	case 's':
		if (default_cam) {
			default.yLoc -= 0.1;
		}
		break;
	case 'a':
		if (default_cam) {
			default.xLoc -= 0.1;
		}
		break;
	case 'd':
		if (default_cam) {
			default.xLoc += 0.1;
		}
		break;
	case 'q':
		if (default_cam) {
			default.zLoc += 0.1;
		}
		break;
	case 'e':
		if (default_cam) {
			default.zLoc -= 0.1;
		}
		break;
	case 't':
		//focus on the ball
		default.xEye = course->getTee()[0];
		default.yEye = course->getTee()[1];
		default.zEye = course->getTee()[2];
		break;
	case 'o':
		//focus on the origin
		default.xEye = 0;
		default.yEye = 0;
		default.zEye = 0;
		break;
	case 'c' :
		//focus on the ball
		default.xEye = course->getCup()[0];
		default.yEye = course->getCup()[1];
		default.zEye = course->getCup()[2];
		break;
	case 'r':
		//Reset the Camera Position
		//focus on the ball
		default.xLoc = 0;
		default.yLoc = 3;
		default.zLoc = 5;
		break;
	case '1':
		default_cam = true;
		third_person_cam = false;
		top_down_cam = false;
		break;
	case '2':
		default_cam = false;
		third_person_cam = true;
		top_down_cam = false;
		break;
	case '3':
		default_cam = false;
		third_person_cam = false;
		top_down_cam = true;
		break;
	}
}

void GL_idleFunc() {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	int exitNum = 0;
	string fileName;

	vector< vector<string> > file;	// Our file, as a vector

	catcher mitt;			// catcher object

	// Try block, used to catch problems in what we do
	try {
		// Checks file entered, asks for input if a single file is not supplied
		if (argc != 2) {
			// Requests for an input
			fileName = mitt.reEnter("We expected one file, would you like to enter a file? (y/n)",
					"Enter file location: ", "no file location was entered.");
		} else {
			fileName = argv[1];
		}

		reader fileReader (fileName);		// reader object
		file = fileReader.getWords();		// Gets a vector of a vector of each word

		//golfCourse course(file);
		course = new golfCourse(file);
		third_person_ball = {0, 2, 0, course->getTee()[0], course->getTee()[1], course->getTee()[2]};	//These parameters define gluLookAt for third person view. Need to work on this
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

	//OpenGL Functions only begin if file reader succeeded
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("MiniGolf Rendering");

	init(); //Enables the Lighting in the scene

	glutDisplayFunc(GL_displayFunc);
	glutReshapeFunc(GL_reshapeFunc);
	glutIdleFunc(GL_idleFunc);
	
	glutKeyboardFunc(GL_keyboardFunc);

	glClearColor(0,0,0,0);
	glutMainLoop();

	return 0;
}