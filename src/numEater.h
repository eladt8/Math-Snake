#ifndef _NUMEATER_H
#define _NUMEATER_H

#include "Enemies.h"
#include "screen.h"
#include "Snake.h"

class numEater : public Enemies
{
public:
	virtual void move() override;
	virtual void NextMove() override;
	numEater(Point bodyPos, char c, SnakesGame * theGame, bool isAlive = true);

};

#endif