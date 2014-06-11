#ifndef PLAYERPROFILE_H
#define PLAYERPROFILE_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "courseInfo.h"

using namespace std;

class playerProfile {
public:
	playerProfile(string name);
	void setName(string name);
	void updateScores(int index, int shotNum);
	vector<courseInfo*> returnScores();
private:
	string playerName;
	vector<courseInfo*> scores;

};

#endif