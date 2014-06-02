////////////////////////
// Collider.h         //
// Collider header    //
// Used for collision //
////////////////////////

#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>

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

	void operator=(Vertex set);
	void operator=(double set);
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
		bool isPhysical = true;
		bool willCollide = false;
		Position center;
		Vector3 centerToVec(Position p);
		virtual bool sphereCollide(Position p, double r);
		virtual Vector3 getCollisionVector();
		virtual void onCollision();
		virtual void update();
		virtual ~Collider() {};
};

class Quad: public Collider {
	private:
		vector <Vertex> vertices;
		Vector3 normal;
	public:
		Position upperBounds;
		Position lowerBounds;

		Quad();
		Quad(Position c);
		Quad(vector <Vertex> verts);
		Quad(Position c, vector <Vertex> verts);

		virtual bool sphereCollide(Position p, double r);
		virtual Vector3 getCollisionVector();
		
		bool sphereTileEdgeCollide(Position p);
		
		void calculateNormal();
		void setVertices(vector <Vertex> verts);
		void findCenter();
		void setBounds();
		void onCollision();
		Vector3 getNormal();
		int getToTileNum();
};

class Sphere : public Collider {
	public:
		double radius;
		Sphere();
		Sphere(Position c);
		Sphere(double r);
		Sphere(Position c, double r); 

		virtual bool sphereCollide(Position p, double r);
		virtual Vector3 getCollisionVector();
		void onCollision();
};

#endif