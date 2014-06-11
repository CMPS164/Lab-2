#include "playerProfile.h"

playerProfile::playerProfile(string name) : playerName(name) {};

void playerProfile::setName(string name) {
	playerName = name;
}

void playerProfile::updateScores(int index, int shotNum) {
	scores.at(index)->setShotNum(shotNum);
}

vector <courseInfo*> playerProfile::returnScores() {
	return scores;
}