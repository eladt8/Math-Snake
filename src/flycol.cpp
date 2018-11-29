#include "flycol.h"
#include "SnakesGame.h"

void flycol::move()
{
	
	if (isAlive == true)
	{
		if (getIsCross() == true)
		{
			if (enemyBody.getY() + enemyBody.getDirY() == Point::min_y || enemyBody.getY() + enemyBody.getDirY() == Point::max_y)
			{
				changeDir();
			}
		}

		enemyBody.draw(' ');
		currGame->addCharToScreen(' ', enemyBody.getX(), enemyBody.getY());
		currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(), ' ', currGame->getCountSleep());
		enemyBody.moveBullet();
		currGame->addCharToScreen(c, enemyBody.getX(), enemyBody.getY());
		currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(),c, currGame->getCountSleep());
		enemyBody.draw(c);
	}
}

//char flycol::analMoveEnemis()
//{
//	
//	int nextX = enemyBody.getX() + enemyBody.getDirX();
//	int nextY = enemyBody.getY() + enemyBody.getDirY();
//
//	Point pos(nextX, nextY);
//
//	return currGame->getCharFromBoard(pos);
//}

void flycol::NextMove()
{

	Point nextPos = { enemyBody.getX() + enemyBody.getDirX(),enemyBody.getY()+ enemyBody.getDirY() };

	char nextMoveChar = analMoveEnemis();

	if (nextMoveChar == '@' || nextMoveChar == '#')
	{
		enemieBumpSnake(nextMoveChar);
	}
	if (nextMoveChar >= '0' && nextMoveChar <= '9')
	{
		int num =currGame->getNumber(nextPos);
		currGame->deleteNumberWhenBang(nextPos, num);
	}
	if (nextMoveChar == '*')  //not sure if needed
	{
		Bullet & HitMeBaby = currGame->returnBulletByPlace(nextPos.getX(),nextPos.getY());
	
		currGame->BangEnmey(HitMeBaby, -1);
		currGame->deleteBulet(HitMeBaby);
		enemyBody.draw(' ');
		currGame->addCharToScreen(' ', enemyBody.getX(), enemyBody.getY());
	}

}

flycol::flycol(Point bodyPos, char c, bool changeDir, SnakesGame * theGame,Direction dir, bool isAlive)
{

	enemyBody.setX(bodyPos.getX());
	enemyBody.setY(bodyPos.getY());
	enemyBody.changeDir(dir);
	setChar(c);
	setIsCrosDir(changeDir);
	setGameP(theGame);
}

