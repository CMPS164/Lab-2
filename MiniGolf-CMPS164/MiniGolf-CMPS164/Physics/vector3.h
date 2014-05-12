////////////////////////////
// Vector3.h              //
// Vector3 header         //
// Used for vector values //
////////////////////////////

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
	public:
		double x, y, z;	// Vectors

		// Constructors
		Vector3();
		Vector3(double vX, double vY);
		Vector3(double vX, double vY, double vZ);

		bool moving();
		Vector3 absolute();
		Vector3 singedValues();
		double dotProduct(Vector3 dot);

		// Functor functions of this object
		void operator()();

		// Math Operations
		Vector3 operator+(Vector3 add);
		Vector3 operator+(double add);
		Vector3 operator-(Vector3 sub);
		Vector3 operator-(double sub);
		Vector3 operator*(Vector3 mult);
		Vector3 operator*(double mult);
		Vector3 operator/(Vector3 div);
		Vector3 operator/(double div);

		void operator=(Vector3 set);
		void operator=(double set);
		void operator+=(Vector3 add);
		void operator+=(double add);
		void operator-=(Vector3 sub);
		void operator-=(double sub);
		void operator*=(Vector3 mult);
		void operator*=(double mult);
		void operator/=(Vector3 div);
		void operator/=(double div);

		// Comparison Operations
		bool operator==(Vector3 equal);
		bool operator==(double equal);
		bool operator!=(Vector3 notEqual);
		bool operator!=(double notEqual);
		bool operator<(Vector3 lessThan);
		bool operator<(double lessThan);
		bool operator>(Vector3 greaterThan);
		bool operator>(double greaterThan);
		bool operator<=(Vector3 lessEqual);
		bool operator<=(double lessEqual);
		bool operator>=(Vector3 greaterEqual);
		bool operator>=(double greaterEqual);
};

#endif