////////////////////////
// Collider.cpp       //
// Used for collision //
////////////////////////

#include <iostream>

#include "collider.h"

using namespace std;

Vertex::Vertex() : x(0), y(0), z(0) {}

Vertex::Vertex(double nX, double nY) : x(nX), y(nY), z(0) {}

Vertex::Vertex(double nX, double nY, double nZ) : x(nX), y(nY), z(nZ) {}

void Vertex::operator() () {
	cout << "{" << x << ", " << y << ", " << z << "}" << endl;
}

Vertex Vertex::operator+(Vertex add) {
	return Vertex(x + add.x, y + add.y, z + add.z);
}

Vertex Vertex::operator+(double add) {
	return Vertex(x + add, y + add, z + add);
}

Vertex Vertex::operator-(Vertex sub) {
	return Vertex(x - sub.x, y - sub.y, z - sub.z);
}

Vertex Vertex::operator-(double sub) {
	return Vertex(x - sub, y - sub, z - sub);
}

Vertex Vertex::operator*(Vertex mult) {
	return Vertex(x * mult.x, y * mult.y, z * mult.z);
}

Vertex Vertex::operator*(double mult) {
	return Vertex(x * mult, y * mult, z * mult);
}

Vertex Vertex::operator/(Vertex div) {
	return Vertex((div.x == 0 ? 0 : x / div.x), (div.y == 0 ? 0 : y / div.y), (div.z == 0 ? 0 : z / div.z));
}

Vertex Vertex::operator/(double div) {
	return div == 0 ? Vertex() : Vertex(x / div, y / div, z / div);
}

void Vertex::operator=(Vertex set) {
	x = set.x;
	y = set.y;
	z = set.z;
}

void Vertex::operator=(double set) {
	x = set;
	y = set;
	z = set;
}

void Vertex::operator+=(Vertex add) {
	x += add.x;
	y += add.y;
	z += add.z;
}

void Vertex::operator+=(double add) {
	x += add;
	y += add;
	z += add;
}

void Vertex::operator-=(Vertex sub) {
	x -= sub.x;
	y -= sub.y;
	z -= sub.z;
}

void Vertex::operator-=(double sub) {
	x -= sub;
	y -= sub;
	z -= sub;
}

void Vertex::operator*=(Vertex mult) {
	x *= mult.x;
	y *= mult.y;
	z *= mult.z;
}

void Vertex::operator*=(double mult) {
	x *= mult;
	y *= mult;
	z *= mult;
}

void Vertex::operator/=(Vertex div) {
	x = div.x == 0 ? 0 : (x / div.x);
	y = div.y == 0 ? 0 : (y / div.y);
	x = div.z == 0 ? 0 : (z / div.z);
}

void Vertex::operator/=(double div) {
	x = div == 0 ? 0 : (x / div);
	y = div == 0 ? 0 : (y / div);
	x = div == 0 ? 0 : (z / div);
}


/***************Collider Functions****************/

// Returns a vector from center of this collider to position
Vector3 Collider::centerToVec(Position p) {
	return Vector3(p.x - center.x, p.y - center.y, p.z - center.z);
}

bool Collider::sphereCollide(Position p, double r) {
	return false;
}

Vector3 Collider::getCollisionVector() {
	return Vector3();
}

void Collider::onCollision() {
}

void Collider::update() {
	if (willCollide) {
		onCollision();
		willCollide = false;
	}
}

/****************Quad Functions*******************/

// Construcors

Quad::Quad() {
	center = Position();
	vertices.push_back(Vertex(1, 1));
	vertices.push_back(Vertex(-1, 1));
	vertices.push_back(Vertex(-1, -1));
	vertices.push_back(Vertex(1, -1));
	calculateNormal();
	setBounds();
}

Quad::Quad(Position c) {
	center = c;
	vertices.push_back(Vertex(1, 1));
	vertices.push_back(Vertex(-1, -1));
	vertices.push_back(Vertex(-1, -1));
	vertices.push_back(Vertex(1, -1));
	calculateNormal();
	setBounds();
}

Quad::Quad(vector <Vertex> verts) {
	center = Position();
	vertices = verts;
	calculateNormal();
	setBounds();
}

Quad::Quad(Position c, vector <Vertex> verts) {
	center = c;
	vertices = verts;
	calculateNormal();
	setBounds();
}

// Collider overloads/functions

// Checks if a sphere at a position with a radius will collide with this quad object
bool Quad::sphereCollide(Position p, double r) {
	Vector3 temp = centerToVec(p);

	// Calculates distance to sphere
	double dist = temp.dotProduct(normal);

	if (abs(dist) > r) return false;
	return true;
}

bool Quad::sphereTileEdgeCollide(Position p) {
	Vector3 temp = centerToVec(p);

	// Calculates distance to sphere
	double dist = temp.dotProduct(normal);

	if (abs(dist) > 0) return false;
	
	return true;
}

void Quad::onCollision() {

}

Vector3 Quad::getCollisionVector() {
	return normal;
}

// Quad specific functions


void Quad::calculateNormal() {
	Vector3 vec1(vertices[2].x - vertices[1].x, vertices[2].y - vertices[1].y, vertices[2].z - vertices[1].z);
	Vector3 vec2(vertices[0].x - vertices[1].x, vertices[0].y - vertices[1].y, vertices[0].z - vertices[1].z);
	
	//Cross Product calculation
	normal.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	normal.y =  -1 * ((vec1.x * vec2.z) -  (vec1.z * vec2.x));
	//normal.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	normal.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	
	//Calculating Magnitude
	double total = pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2);
	double magnitude = sqrt(total);

	normal /= magnitude;
}

void Quad::setVertices(vector <Vertex> verts) {
	vertices = verts;
	calculateNormal();
	findCenter();
	setBounds();
}

// Finds the center of current Quad
void Quad::findCenter() {
	center = 0;

	for (auto verts : vertices) {
		center.x += verts.x;
		center.y += verts.y;
		center.z += verts.z;
	}

	center /= vertices.size();
}

// Sets the area that this quad covers, does not work for concave shapes
void Quad::setBounds() {
	double lx = vertices[0].x, ly = vertices[0].y, lz = vertices[0].z;
	double ux = vertices[0].x, uy = vertices[0].y, uz = vertices[0].z;
}

Vector3 Quad::getNormal() {
	return normal;
}



/*************Sphere Functions****************/

Sphere::Sphere() : radius(1) {
	center = Position();
}

Sphere::Sphere(Position c) : radius(1) {
	center = c;
}

Sphere::Sphere(double r) : radius(r) {
	center = Position();
}

Sphere::Sphere(Position c, double r) : radius(r) {
	center = c;
}

// Checks if a sphere at a position with a radius will collide with this sphere object
bool Sphere::sphereCollide(Position p, double r) {
	Vector3 temp = centerToVec(p);

	// Calculates distance to sphere
	double dist = temp.dotProduct(temp);

	double squaredRadius = radius + r;
	squaredRadius *= squaredRadius;

	if (dist > squaredRadius) return false;
	return true;
}

Vector3 Sphere::getCollisionVector() {
	return Vector3();
}

void Sphere::onCollision() {

}