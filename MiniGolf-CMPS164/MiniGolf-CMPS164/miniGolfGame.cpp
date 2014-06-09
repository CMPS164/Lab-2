#include "miniGolfGame.h"

int windowWidth = 800;
int windowHeight = 600;

cam_coord default{0, 3, 3, 0, 0, 0};
cam_coord third_person_ball{ 0, 0, 0, 0, 0, 0 };
cam_coord top_down{ 0, 3, 0, 0, 0, 0 };

bool default_cam = true;
bool third_person_cam = false;
bool top_down_cam = false;

bool userInputSwitch = false;

double direction, force = 0;

void setCameraModes(GolfCourse *course) {
	
	third_person_ball = { course->golfBall.position.x, course->golfBall.position.y + 0.2, course->golfBall.position.z + 0.3,
		course->golfBall.position.x, course->golfBall.position.y, course->golfBall.position.z };

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

}

void HUDCalls(HUD* HUDArg) {

	HUDArg->drawGUIText("MiniGolf Game Engine", 10, windowHeight - 20); //Once Refactoring is done, get the current course number and place it here                                              
	HUDArg->drawGUIText("Shot Number: " + to_string(HUDArg->returnCourse()->shotNum), 10, windowHeight - 40); //Course has a shotNum property. Gets incremented per shot
	HUDArg->drawGUIText("Inputted Direction: " + to_string(direction), 10, windowHeight - 60);
	HUDArg->drawGUIText("Inputted Force: " + to_string(force), 10, windowHeight - 80);
	HUDArg->drawGUIText("Course Number: 1", 10, windowHeight - 100);
}

/*
*	This function draws the golf course through primitives.
*/
void draw_Course(GolfCourse *course) {
	
	vector<Tile> tiles = course->getTiles();
	
	for (auto tile : tiles) {
		vector< Vertex > vertices = tile.verts;
		vector<Wall> edges = tile.walls;

		glPushMatrix();
		//Drawing the polygon, counter-clockwise
		glBegin(GL_POLYGON);

		glNormal3f(tile.getNormal().x, tile.getNormal().y, tile.getNormal().z);
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
	glTranslatef(course->golfBall.position.x, course->golfBall.position.y + course->golfBall.ballRadius, course->golfBall.position.z);
	glutSolidSphere(course->golfBall.ballRadius, 360, 360);
	glPopMatrix();

	//Drawing the cup
	//This draws a cylinder as the cup. 	
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(cupLoc.x, cupLoc.y + 0.001, cupLoc.z);
	GLUquadric* hole = gluNewQuadric();
	gluQuadricNormals(hole, GL_SMOOTH);
	glRotatef(90, 1, 0, 0);
	gluCylinder(hole, (course->golfBall.ballRadius * 2), (course->golfBall.ballRadius * 2), 0.05, 360, 1); //parameters are (gluQuatric, radius of base, radius of top, height, slices, subdivisions)
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(180, 1, 0, 0);
	gluDisk(hole, 0.0f, (course->golfBall.ballRadius * 2), 360, 1);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, 0, 0.05);
	gluDisk(hole, 0.0f, (course->golfBall.ballRadius * 2), 360, 1);
	glPopMatrix();
}

void userInput(GolfCourse *course) {
	if (course->golfBall.velocity == 0) { //If the ball isn't moving

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

void keyFunctions(unsigned char key, GolfCourse *course) {

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
	case 'c':
		//focus on the cup

		default.xEye = course->getCup().x;
		default.yEye = course->getCup().y;
		default.zEye = course->getCup().z;

		break;
	case 'r':
		//Reset the Camera Position

		default.xLoc = 0;
		default.yLoc = 3;
		default.zLoc = 3;

		break;
	case 'b':

		default_cam = true;
		third_person_cam = false;
		top_down_cam = false;

		break;
	case 'n':

		default_cam = false;
		third_person_cam = true;
		top_down_cam = false;

		break;
	case 'm':

		default_cam = false;
		third_person_cam = false;
		top_down_cam = true;

		break;
	}
}

GolfCourse* readCourseFile(int argc, char** argv) {

	string fileName;

	vector< vector<string> > file;	// Our file, as a vector

	Catcher mitt;			// catcher object
	GolfCourse* course;

	// Try block, used to catch problems in what we do
	try {
		// Checks file entered, asks for input if a single file is not supplied
		if (argc != 2) {
			// Requests for an input
			fileName = mitt.reEnter("We expected one file, would you like to enter a file? (y/n)",
				"Enter file location: ", "no file location was entered.");
		}
		else {
			fileName = argv[1];
		}

		reader fileReader(fileName);		// reader object
		file = fileReader.getWords();		// Gets a vector of a vector of each word

		course = new GolfCourse(file);
		third_person_ball = { course->getTee().x, course->getTee().y + 0.4, course->getTee().z + 0.3,
			course->getTee().x, course->getTee().y, course->getTee().z };
	}
	catch (string error) {
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
	cout << "'B' DefaultCam" << endl;
	cout << "'N' ThirdPersonCam" << endl;
	cout << "'M' TopDownCam" << endl;
	cout << endl << "//////////" << endl;

	return course;
}