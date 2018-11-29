#ifndef _REPLAYGAME_
#define _REPLAYGAME_

#include <iostream>
#include <queue>
#include "color.h"

class SnakesGame;

using namespace std;


typedef struct replay {
	int locX;
	int locY;
	char ch;
	int countForSleep;
}REPLAY;

class replayGame {

	queue<REPLAY> Qreplay;
	queue<REPLAY>beckupQreplay;
	SnakesGame *currGame;
	REPLAY node;

public:
	replayGame() { ; }
	void actForReplay();

	void makeReplay();
	void getMoveForReplay(int locX, int locY, char ch, int countForSleep);
	void clearQueue(queue<REPLAY>& q1);
	void draw(int x, int y, char c);
	void setReplayGame(SnakesGame *ptr) { currGame = ptr; }
	void restoreQueuAfterReplay();

};

#endif // !_REPLAYGAME_


