#ifndef _FLYROW_H_
#define _FLYROW_H_

#include "Enemies.h"
#include "screen.h"
#include "Snake.h"

class flyrow : public Enemies
{
public:
//	char analMoveEnemis();
	virtual void move() override;
	virtual void NextMove() override;
	flyrow(Point bodyPos, char c, bool changeDir, SnakesGame * theGame, Direction dir, bool isAlive = true);
};



#endif // !_FLYROW_H_
