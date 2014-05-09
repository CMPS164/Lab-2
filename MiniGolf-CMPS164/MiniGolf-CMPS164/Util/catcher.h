///////////////////////////////
// Catcher.h                 //
// Catcher header            //
// Used for requesting input //
///////////////////////////////

#ifndef CATCHER_H
#define CATCHER_H

#include <string>

using namespace std;

class Catcher {
	public:
		// Asks if user would like to continue
		void cont(string question, string errorMessage);

		// Asks if user would like to renter input and returns user input as a string
		string reEnter(string question, string yStatement, string errorMessage);

		// Asks if user would like to renter input and returns user input as a double
		double reEnterNum(string question, string yStatement, string errorMessage);
};

#endif