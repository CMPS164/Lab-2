/////////////////////////////
// Position.cpp            //
// The position of objects //
/////////////////////////////

#include <iostream>

#include "position.h"

using namespace std;

// Sets velocities to 0
Position::Position() : x(0), y(0), z(0) {
}

// Sets given x and y velocities and z to zero (2d possibilities)
Position::Position(double vX, double vY) : x(vX), y(vY), z(0) {
}

// Sets given x, y, and z velocities
Position::Position(double vX, double vY, double vZ) : x(vX), y(vY), z(vZ) {
}


////////////////
// Operations //
////////////////

// Prints out all 3 velocities
void Position::operator()() {
	cout << "{" << x << ", " << y << ", " << z << "}" << endl;
}


/*
* Basic Arithmetic operations
*/

Position Position::operator+(Position add) {
	Position temp;
	temp.x = x + add.x;
	temp.y = y + add.y;
	temp.z = z + add.z;
	return temp;
}

Position Position::operator-(Position sub) {
	Position temp;
	temp.x = x - sub.x;
	temp.y = y - sub.y;
	temp.z = z - sub.z;
	return temp;
}

Position Position::operator*(Position mult) {
	Position temp;
	temp.x = x * mult.x;
	temp.y = y * mult.y;
	temp.z = z * mult.z;
	return temp;
}

Position Position::operator/(Position div) {
	Position temp;
	temp.x = x / div.x;
	temp.y = y / div.y;
	temp.z = z / div.z;
	return temp;
}

void Position::operator=(Position set) {
	x = set.x;
	y = set.y;
	z = set.z;
}

void Position::operator=(double set) {
	x = set;
	y = set;
	z = set;
}

void Position::operator+=(Position add) {
	x += add.x;
	y += add.y;
	z += add.z;
}

void Position::operator-=(Position sub) {
	x -= sub.x;
	y -= sub.y;
	z -= sub.z;
}

void Position::operator*=(Position mult) {
	x *= mult.x;
	y *= mult.y;
	z *= mult.z;
}

void Position::operator/=(Position div) {
	x /= div.x;
	y /= div.y;
	z /= div.z;
}

/*
* Comparision Operations
* Compares each individual values, all must be true to return true
*/

bool Position::operator==(Position equal) {
	if (x == equal.x && y == equal.y && z == equal.z)
		return true;
	return false;
}

bool Position::operator!=(Position notEqual) {
	return !(*this == notEqual);
}

bool Position::operator<(Position lessThan) {
	if (x < lessThan.x && y < lessThan.y && z < lessThan.z)
		return true;
	return false;
}

bool Position::operator>(Position greaterThan) {
	if (x > greaterThan.x && y > greaterThan.y && z > greaterThan.z)
		return true;
	return false;
}

bool Position::operator<=(Position lessEqual) {
	if (x <= lessEqual.x && y <= lessEqual.y && z <= lessEqual.z)
		return true;
	return false;
}

bool Position::operator>=(Position greaterEqual) {
	if (x >= greaterEqual.x && y >= greaterEqual.y && z >= greaterEqual.z)
		return true;
	return false;
}