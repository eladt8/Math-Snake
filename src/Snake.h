#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "const.h"
#include "Direction.h"

typedef struct Bullet {
	Point Bull;
	bool fireInTheHole = false;
	int whoShot;
}BULLET;


class Snake {
	Point * body;
	Direction direction;
	char c;
	int score;
	int SnSize;  //defult size of snake
	char dirKeys[5]; // the keys for the four possible directions
	BULLET Bullets[AMMO];
	int Ammo;
	int gotShoot;
public:
	Snake(const Point& head, char c1, Direction dir, int SnakeSize = 3, int sscore = 0);  // ���� �� ������
	void upSnake(int i,bool isReset);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown,char keyShot);  //����� �� ������ ������
	void changeDir(char keyPressed); //����� ����� �� ��� ��� �����
	Point move(char keyPressed,Point& oldTail);  //���� ���
	char getChar() const { return c; }
	Point& biggerBody(); //����� �� ����. ���� ����� �������� ���� �������� �� ����� �� ���� ������ ������ �� �� �� ��� ���� ���
	Point currentPos(int place) { return body[place]; }
	int GetSnakeSize() { return SnSize; }
	Direction getCurrDir() { return direction; }
	void setSnSize(int newSnakeSize) { SnSize = newSnakeSize; }
	void setScore(int sscore) { score = sscore; }
	void upScore() { score += 1;}
	int getScore() { return score; }
	Point preMove(char keyPressed);
	void changePos(int i);
	void shooting();
	void moveBullet();
	BULLET* returnBulletArr() { return Bullets; }
	char getKeyShot() { return dirKeys[4]; }
	void reloadAmmo(int newAmountOfAmmo) { Ammo = newAmountOfAmmo; }  // ������ �� ����� �� �������
	int getAmmo() { return Ammo; }   // ������ �� ����� �� �������
	int getGotShoot() { return gotShoot; }
	void decGetShoot() { gotShoot--; }
	void upgotShoot(int i){ gotShoot +=i; }
};
#endif
