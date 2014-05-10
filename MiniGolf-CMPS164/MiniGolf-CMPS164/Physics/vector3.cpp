/////////////////////////////
// Vector3.cpp            //
// The vectors of objects //
////////////////////////////

#include <iostream>
#include <math.h>

#include "vector3.h"

using namespace std;

// Sets vectors to 0
Vector3::Vector3() : x(0), y(0), z(0) {
}

// Sets given x and y vectors and z to zero (2d possibilities)
Vector3::Vector3(double vX, double vY) : x(vX), y(vY), z(0) {
}

// Sets given x, y, and z vectors
Vector3::Vector3(double vX, double vY, double vZ) : x(vX), y(vY), z(vZ) {
}

// Checks if Vectors is not zero
bool Vector3::moving() {
	if (x == 0 && y == 0 && z == 0)
		return false;
	return true;
}

////////////////
// Operations //
////////////////

// Prints out all 3 vectors
void Vector3::operator()() {
	cout << "{" << x << ", " << y << ", " << z << "}" << endl;
}

// Returns a Vector3 that contains the absolute valus of this vector2
Vector3 Vector3::absolute() {
	return Vector3(abs(x), abs(y), abs(z));
}

// Returns a Vector3 
Vector3 Vector3::singedValues() {
	return *this / (absolute());
}

/*
* Basic Arithmetic operations
*/

Vector3 Vector3::operator+(Vector3 add) {
	return Vector3(x + add.x, y + add.y, z + add.z);
}

Vector3 Vector3::operator+(double add) {
	return Vector3(x + add, y + add, z + add);
}

Vector3 Vector3::operator-(Vector3 sub) {
	return Vector3(x - sub.x, y - sub.y, z - sub.z);
}

Vector3 Vector3::operator-(double sub) {
	return Vector3(x - sub, y - sub, z - sub);
}

Vector3 Vector3::operator*(Vector3 mult) {
	return Vector3(x * mult.x, y * mult.y, z * mult.z);
}

Vector3 Vector3::operator*(double mult) {
	return Vector3(x * mult, y * mult, z * mult);
}

Vector3 Vector3::operator/(Vector3 div) {
	return Vector3((div.x == 0 ? 0 : x / div.x), (div.y == 0 ? 0 : y / div.y), (div.z == 0 ? 0 : z / div.z));
}

Vector3 Vector3::operator/(double div) {
	return div == 0 ? Vector3() : Vector3(x / div, y / div, z / div);
}

void Vector3::operator=(Vector3 set) {
	x = set.x;
	y = set.y;
	z = set.z;
}

void Vector3::operator=(double set) {
	x = set;
	y = set;
	z = set;
}

void Vector3::operator+=(Vector3 add) {
	x += add.x;
    y += add.y;
	z += add.z;
}

void Vector3::operator+=(double add) {
	x += add;
	y += add;
	z += add;
}

void Vector3::operator-=(Vector3 sub) {
	x -= sub.x;
	y -= sub.y;
	z -= sub.z;
}

void Vector3::operator-=(double sub) {
	x -= sub;
	y -= sub;
	z -= sub;
}

void Vector3::operator*=(Vector3 mult) {
	x *= mult.x;
	y *= mult.y;
	z *= mult.z;
}

void Vector3::operator*=(double mult) {
	x *= mult;
	y *= mult;
	z *= mult;
}

void Vector3::operator/=(Vector3 div) {
	x = div.x == 0 ? 0 : (x / div.x);
	y = div.y == 0 ? 0 : (y / div.y);
	z = div.z == 0 ? 0 : (z / div.z);
}

void Vector3::operator/=(double div) {
	x = div == 0 ? 0 : (x / div);
	y = div == 0 ? 0 : (y / div);
	z = div == 0 ? 0 : (z / div);
}

/*
* Comparision Operations
* Compares each individual values, all must be true to return true
*/

bool Vector3::operator==(Vector3 equal) {
	if (x == equal.x && y == equal.y && z == equal.z)
		return true;
	return false;
}

bool Vector3::operator==(double equal) {
	if (x == equal && y == equal && z == equal)
		return true;
	return false;
}

bool Vector3::operator!=(Vector3 notEqual) {
	return !(*this == notEqual);
}

bool Vector3::operator!=(double notEqual) {
	return !(*this == notEqual);
}

bool Vector3::operator<(Vector3 lessThan) {
	if (x < lessThan.x && y < lessThan.y && z < lessThan.z)
		return true;
	return false;
}

bool Vector3::operator<(double lessThan) {
	if (x < lessThan && y < lessThan && z < lessThan)
		return true;
	return false;
}

bool Vector3::operator>(Vector3 greaterThan) {
	if (x > greaterThan.x && y > greaterThan.y && z > greaterThan.z)
		return true;
	return false;
}

bool Vector3::operator>(double greaterThan) {
	if (x > greaterThan && y > greaterThan && z > greaterThan)
		return true;
	return false;
}

bool Vector3::operator<=(Vector3 lessEqual) {
	if (x <= lessEqual.x && y <= lessEqual.y && z <= lessEqual.z)
		return true;
	return false;
}

bool Vector3::operator<=(double lessEqual) {
	if (x <= lessEqual && y <= lessEqual && z <= lessEqual)
		return true;
	return false;
}

bool Vector3::operator>=(Vector3 greaterEqual) {
	if (x >= greaterEqual.x && y >= greaterEqual.y && z >= greaterEqual.z)
		return true;
	return false;
}

bool Vector3::operator>=(double greaterEqual) {
	if (x >= greaterEqual && y >= greaterEqual && z >= greaterEqual)
		return true;
	return false;
}