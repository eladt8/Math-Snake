#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include "Point.h"
#include "Direction.h"
#include <iostream>
class SnakesGame;

using namespace std;

class Enemies
{
protected:
	SnakesGame * currGame;
	Point enemyBody;
	char c;
	bool isAlive = true;
	bool isCorssingTheBorder;
	

public:

	void setGameP(SnakesGame * ptr) { currGame = ptr; }
	SnakesGame * getSnakeGameP() { return currGame; }
	void setBodyX(int pointX) { enemyBody.setX(pointX); }
	void setBodyY(int pointY) { enemyBody.setY(pointY); }
	void setDirX(int dir_x) { enemyBody.setDirX(dir_x); }
	void setDirY(int dir_y) { enemyBody.setDirY(dir_y); }
	int getbodyX() { return enemyBody.getX(); }
	int getbodyY() { return enemyBody.getY(); }
	int getDirX() {return enemyBody.getDirX(); }
	int getDirY() { return enemyBody.getDirY(); }
	void setChar(char symbol) { c = symbol; }
	char getChar() { return c; }
	void setIsAlive(bool isIt) { isAlive = isIt; }
	bool getIsAlive() { return isAlive;}
	void setIsCrosDir(bool change) { isCorssingTheBorder = change; }
	bool getIsCross() { return isCorssingTheBorder; }
	virtual void NextMove() = 0;
	char analMoveEnemis();
	virtual void move() = 0;
	void moveEnemy();
	void enemieBumpSnake(char symbol);
	void changeDir();

};


#endif // !_ENEMIES_H_
