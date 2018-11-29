#ifndef _FLYCOL_H_
#define _FLYCOL_H_

#include "Enemies.h"
#include "screen.h"
#include "Snake.h"

class flycol : public Enemies
{
public:
	//char analMoveEnemis();
	virtual void move() override;
	virtual void NextMove() override;
	flycol(Point bodyPos, char c, bool changeDir,SnakesGame * theGame,Direction dir , bool isAlive = true);
};



#endif // !_FLYVOL_H_
