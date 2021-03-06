/////////////////////////////////////////////
// Catcher.cpp                             //
// Used for requesting if problem is found //
/////////////////////////////////////////////

#include <iostream>

#include "catcher.h"

// Asks if user would like to continue
void Catcher::cont(string question, string errorMessage) {
	char response;

	while (true) {
		cin >> response;
		switch (response) {
		case 'Y':
		case 'y':
			break;
		case 'N':
		case 'n':
			throw errorMessage;
		default:
			cout << "Please enter either 'y' for yes or 'n' for no" << endl;
		}
		continue;
	}
}

// Asks if user would like to renter input and returns user input as a string
string Catcher::reEnter(string question, string yStatement, string errorMessage) {
	char response;
	string input;

	while (true) {
		cout << question;
		cin >> response;
		switch (response) {
			case 'Y':
			case 'y':
				cout << yStatement;
				cin >> input;
				return input;
			case 'N':
			case 'n':
				throw errorMessage;
			default:
				cout << "Please enter either 'y' for yes or 'n' for no" << endl;
		}
		continue;
	}
}

//Asks if user would like to renter input and returns user input as a double
double Catcher::reEnterNum(string question, string yStatement, string errorMessage) {
	char response;
	double input;

	while (true) {
		cout << question;
		cin >> response;
		switch (response) {
		case 'Y':
		case 'y':
			cout << yStatement;
			cin >> input;
			return input;
		case 'N':
		case 'n':
			throw errorMessage;
		default:
			cout << "Please enter either 'y' for yes or 'n' for no" << endl;
		}
		continue;
	}
}