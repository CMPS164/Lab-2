//////////////////////////////
// position.h               //
// Position header          //
// Used for position values //
//////////////////////////////

#ifndef POSITION_H
#define POSITION_H

class Position {
	public:
		double x, y, z;	// Velocity

		// Constructors
		Position();
		Position(double vX, double vY);
		Position(double vX, double vY, double vZ);

		// Functor functions of this object
		void operator()();

		// Math Operations
		Position operator+(Position add);
		Position operator-(Position sub);
		Position operator*(Position mult);
		Position operator/(Position div);

		void operator=(Position set);
		void operator=(double set);
		void operator+=(Position add);
		void operator+=(double add);
		void operator-=(Position sub);
		void operator-=(double sub);
		void operator*=(Position mult);
		void operator*=(double mult);
		void operator/=(Position div);
		void operator/=(double div);

		// Comparison Operations
		bool operator==(Position equal);
		bool operator!=(Position notEqual);
		bool operator<(Position lessThan);
		bool operator>(Position greaterThan);
		bool operator<=(Position lessEqual);
		bool operator>=(Position greaterEqual);
};

#endif