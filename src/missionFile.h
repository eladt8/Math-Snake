#ifndef  _MISSIONFILE_
#define _MISSIONFILE_

#include <iostream>
#include "screen.h"
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

typedef struct equation {
	int num[4];
	char op1, op2;
	int randPlace;
	int currentAnswer;

}EQUAITION;

typedef struct getmission {
	int numMission;
	int x = -1;
	int y = -1;

}GET_MISSION;

enum OP { PLUS, MINUS, MULTI, DIV };

class missionFile 
{
	vector<GET_MISSION> readVector;//need distractor?
	int readVectorSize;
	EQUAITION eq;
	bool IsnewMission;
	GET_MISSION resMission;
	
	int sqr[13] = { 1,4,9,16,25,36,49,64,81,100,121,144,169 };

public:

	missionFile();
	void readMissionFromText();
	void makeMission(GET_MISSION & temp);

	void setVectorSize() { readVectorSize = readVector.size(); }
	int randMission();
	void eqMission();
	char randOp();
	int randNum(int top, int low);
	int findNum4(int num1, int num2, int num3, char op1, char op2);
	void  printMission();
	bool getIsNewMission() {return IsnewMission;}
	void updateIsNewMission(bool newStatus) { IsnewMission = newStatus; }
	int reCorrectAnswer() { return eq.currentAnswer; }
	int getMissionNumber() { return resMission.numMission; }
	GET_MISSION getMIssion() { return resMission; }
	void putMissionInVector(string line);
};


#endif // ! _MISSIONFILE_
#pragma once
