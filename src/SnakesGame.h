#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "screen.h"
#include <time.h>
#include "Snake.h"
#include "color.h"
#include "missionFile.h"
#include "Enemies.h"
#include "numEater.h"
#include "flycol.h"
#include "flyrow.h"
#include <list>
#include <vector>
#include "replayGame.h"


using namespace std;


typedef struct Food {
	Point XY;
	int number;
	int size;
}FOOD;

typedef struct Path {
	int dirX;
	int dirY;
	int Length;
	FOOD target;
}PATH;

typedef struct replayKey {
	char key;
	int keyStep;

}REPLAYKEY;



class SnakesGame {

	Snake snakes[AMOUNTOFSNAKES] = {
		{ { 10, 9 }, '@',Direction::RIGHT }, // snake 1
		{ { 70 ,9 }, '#' ,Direction::LEFT}, // snake 2
	};

	Enemies * enemArr[5] = {
		{new flycol {{ 45,23 },'$',true,this,Direction::UP,true }},
		{new flycol {{ 55,15 },'$',false,this,Direction::DOWN,true }},
		{new flyrow {{30,23},'!',false,this,Direction::RIGHT,true}},
		{new flyrow{ { 50,15 },'!',true,this,Direction::LEFT,true } },
		{new numEater{ { 19,10 },'%',this,true } },
	};

	time_t seedTime=time(&seedTime);
	int countSteps = 0;
	int countFood = 0;
	Screen Boards;
	replayGame replayG;
	bool exitGame = false;
	missionFile mission;
	int countStepsForReplay=0;


	FOOD food[FOODSIZE];

	int getDigit(int x, int y) {    //���� �� ����� ����� ������ �������
		char c = Boards.getInfo(x, y);
		if (c == ' ') {//ET
			return -1;
		}
		return c - '0';
	}

	void addNumber();//ET
	int countDig(int num);
	int checkLoc(int x, int y, int numSize);
	bool correctAnswer(int numEaten);
	void putInTable(int newNum, int numSize, int loc_x, int loc_y);
	bool bumpFriend(Point head);
public:
	SnakesGame() {
		snakes[0].setKeys('a', 'd', 'w', 'x','z');
		snakes[1].setKeys('j', 'l', 'i', ',','n');
		replayG.setReplayGame(this);
		
	}
	void run();

	

	int getNumber(Point& pos)
	{
		int x = pos.getX();
		int y = pos.getY();
		int number = -1;

		int posFirstDigit = findNumber(x, y);  //����� �� ����� ������� �� �����

		for (int i = 0;i < countFood; ++i)
		{
			if ((posFirstDigit == food[i].XY.getX()) && (y == food[i].XY.getY()))
			{
				number = food[i].number;
				removeFood(countFood, i);
			}
		}
		pos.setX(posFirstDigit);
		return number;
	}
	char getCharFromBoard(Point pos) { return Boards.getInfo(pos.getX(), pos.getY()); }
	void reduceFood(int &countFood,bool all);
	void removeFood(int &size, int index);
	void removeFromScreen(FOOD food);
	void addCharToScreen(char c, int loc_x, int loc_y) { Boards.updateNumbersOnArr(loc_x, loc_y, c); }
	void addNumToScreen(int number, int size, int loc_x, int loc_y);
	void printSnakeOnBoardArr(int SnakeNumber, Point oldTailToRemove);
	void DeleteSnakesFromArr(int SnakeNumber);
	void LetsStart();
	void pauseMenu();
	void printInstractions();
	void checkNumbersAroundNewLoc(int snakeNum);
	void goodAnswer(int i);
	int findNumber(int x, int y);
	void checkScore(int i);
	void findCorrectAnswer();
	void relocSnakes();
	void StartNewMission();
	void WorngAnswer(int i);
	void printBulletsOnArr(int i,char c);
	void deleteBullets();
	void analBulletMove(Bullet * arr);
	void bangBang(int whoShot,int hurt);
	void deleteBulet(Bullet& b);
	bool deleteWhenCrushed2Bullets(Bullet * arr, Point Pos);
	Bullet & returnBulletByPlace(int loc_x, int loc_y);
	void BangEnmey(Bullet b, int hurt);
	void resurrection();
	void wasted(int i);
	void deleteNumberWhenBang(Point temp,int num);
	void endOfMission(int snakeNum);
	PATH findCorrectAnswerForNumEater(Point point);
	PATH pathFinder(int posX, int posY, Point posOfNumeater);
	Screen* getScreenP() { return &Boards; }
	replayGame * getRplayP() { return &replayG; }
	int getCountSleep() { return countStepsForReplay; }
	void printMis();

};

#endif


