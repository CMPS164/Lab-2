/////////////////////////////////
// Lab 2: Golf Course Renderer //
/////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Util/reader.h"
#include "Util/catcher.h"
#include "Physics/rigidbody.h"
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
GolfCourse* course;
Ball* golfTee;
cam_coord default{0, 3, 3, 0, 0, 0};
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

void calc_Normal(array<double, 3> &result, Vertex v1, Vertex v2, Vertex v3) {
	array<double, 3> vector_1;
	vector_1[0] = v3.x - v2.x;
	vector_1[1] = v3.y - v2.y;
	vector_1[2] = v3.z - v2.z;

	array<double, 3> vector_2;
	vector_2[0] = v1.x - v2.x;
	vector_2[1] = v1.y - v2.y;
	vector_2[2] = v1.z - v2.z;

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
void draw_Course(GolfCourse* course) {
	vector<Tile> tiles = course->getTiles();
	for (auto tile : tiles) {
		vector< Vertex > vertices = tile.verts;
		vector<Wall> edges = tile.walls;

		array<double, 3> temp;
		//Get Face Normal
		
		glPushMatrix();
		//Drawing the polygon, counter-clockwise
		glBegin(GL_POLYGON);
		calc_Normal(temp, vertices.at(0), vertices.at(1), vertices.at(vertices.size() - 1));
		cout << "Kenneth: " << temp[0] << " " << temp[1] << " " << temp[2] << endl;

		//glNormal3f(tile.getNormal().x, tile.getNormal().y, tile.getNormal().z);
		//cout << "Francis: " << tile.getNormal().x << " " << tile.getNormal().y << " " << tile.getNormal().z << endl;
		//system("pause");
		glNormal3f(temp[0],temp[1], temp[2]);
		for (auto vertex : vertices) {
			float x_Coord = vertex.x;
			float y_Coord = vertex.y;
			float z_Coord = vertex.z;

			glColor3f(0.0f, 1.0f, 0.0f); //Blue
			glVertex3f(x_Coord, y_Coord, z_Coord);
		}
		glEnd();
		glPopMatrix();

		//Drawing the walls
		for (auto wall : edges) {
			
			glPushMatrix();
			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f); //Red
			//glNormal3f(1.0f, 1.0f, 1.0f); //Possibly need to change normal calculation for better lighting?
			glNormal3f(wall.getNormal().x, wall.getNormal().y, wall.getNormal().z);
			glVertex3f(wall.wallVert[0].x, wall.wallVert[0].y, wall.wallVert[0].z);
			glVertex3f(wall.wallVert[1].x, wall.wallVert[1].y, wall.wallVert[1].z);
			glVertex3f(wall.wallVert[2].x, wall.wallVert[2].y, wall.wallVert[2].z);
			glVertex3f(wall.wallVert[3].x, wall.wallVert[3].y, wall.wallVert[3].z);
			glEnd();
			glPopMatrix();
		}
	}

	//Drawing the tee
	Position cupLoc = course->getCup();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(golfTee->position.x, golfTee->position.y + golfTee->ballRadius, golfTee->position.z);
	glutSolidSphere(golfTee->ballRadius, 360, 360);
	glPopMatrix();

	//Drawing the cup
	//This draws a cylinder as the cup. 	
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(cupLoc.x, cupLoc.y + 0.001, cupLoc.z);
	GLUquadric* hole = gluNewQuadric();
	gluQuadricNormals(hole, GL_SMOOTH);
	glRotatef(90, 1, 0, 0);
	gluCylinder(hole, 0.03, 0.03, 0.05, 360, 1); //parameters are (gluQuatric, radius of base, radius of top, height, slices, subdivisions)
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(180, 1, 0, 0);
	gluDisk(hole, 0.0f, 0.03, 360, 1);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, 0, 0.05);
	gluDisk(hole, 0.0f, 0.03, 360, 1);
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
	golfTee->update();

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
		default.xEye = course->getTee().x;
		default.yEye = course->getTee().y;
		default.zEye = course->getTee().z;
		break;
	case 'o':
		//focus on the origin
		default.xEye = 0;
		default.yEye = 0;
		default.zEye = 0;
		break;
	case 'c' :
		//focus on the ball
		default.xEye = course->getCup().x;
		default.yEye = course->getCup().y;
		default.zEye = course->getCup().z;
		break;
	case 'r':
		//Reset the Camera Position
		//focus on the ball
		default.xLoc = 0;
		default.yLoc = 3;
		default.zLoc = 3;
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

	Catcher mitt;			// catcher object

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
		course = new GolfCourse(file);
		golfTee = new Ball(0.025, Position(course->getTee().x, course->getTee().y, course->getTee().z));

		golfTee->addForce(0, .25);

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