////////////////////////
// Collider.h         //
// Collider header    //
// Used for collision //
////////////////////////

#ifndef COLLIDER_H
#define COLLIDER_H

#include <array>

#include "vector3.h"
#include "position.h"

using namespace std;

struct Vertex {
	double x;
	double y;
	double z;

	Vertex();
	Vertex(double nX, double nY);
	Vertex(double nX, double nY, double nZ);

	void operator() ();

	Vertex operator+(Vertex add);
	Vertex operator+(double add);
	Vertex operator-(Vertex sub);
	Vertex operator-(double sub);
	Vertex operator*(Vertex mult);
	Vertex operator*(double mult);
	Vertex operator/(Vertex div);
	Vertex operator/(double div);

	void operator+=(Vertex add);
	void operator+=(double add);
	void operator-=(Vertex sub);
	void operator-=(double sub);
	void operator*=(Vertex mult);
	void operator*=(double mult);
	void operator/=(Vertex div);
	void operator/=(double div);
};

class Collider {
	public:
		Position center;
	protected:
		~Collider() {};
};

class Quad: virtual public Collider {
	private:
		array<Vertex, 4> vertices;
		Vector3 normal;
	public:
		Quad();
		Quad(Position c);
		Quad(array<Vertex, 4> verts);
		Quad(Position c, array<Vertex, 4> vert);
		void calculateNormal();
		Vector3 getNormal();
};

class Sphere : virtual public Collider {
	public:
		double radius;
		Sphere();
		Sphere(Position c);
		Sphere(double r);
		Sphere(Position c, double r);
};

#endif