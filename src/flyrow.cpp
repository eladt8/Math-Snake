#include "flyrow.h"
#include "SnakesGame.h"

void flyrow::move()
{
	if (isAlive == true)
	{
		if (getIsCross() == true)
		{
			if (enemyBody.getX() + enemyBody.getDirX() == Point::min_x || enemyBody.getY() + enemyBody.getDirY() == Point::max_x)
			{
				changeDir();
			}
		}

		enemyBody.draw(' ');
		currGame->addCharToScreen(' ', enemyBody.getX(), enemyBody.getY());
		currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(), ' ', currGame->getCountSleep());
		enemyBody.moveBullet();
		currGame->addCharToScreen(c, enemyBody.getX(), enemyBody.getY());
		currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(), c, currGame->getCountSleep());
		enemyBody.draw(c);
	}
}



void flyrow::NextMove()
{
	
	Point nextPos = { enemyBody.getX() + enemyBody.getDirX(),enemyBody.getY() + enemyBody.getDirY() };

	char nextMoveChar = analMoveEnemis();

	if (nextMoveChar == '@' || nextMoveChar == '#')
	{
		enemieBumpSnake(nextMoveChar);
	}
	if (nextMoveChar >= '0' && nextMoveChar <= '9')
	{
		int num = currGame->getNumber(nextPos);
		currGame->deleteNumberWhenBang(nextPos, num);
	}
	if (nextMoveChar == '*')  
	{
		Bullet & HitMeBaby = currGame->returnBulletByPlace(nextPos.getX(), nextPos.getY());
		currGame->deleteBulet(HitMeBaby);
	
	}

}

flyrow::flyrow(Point bodyPos, char c, bool changeDir, SnakesGame * theGame, Direction dir, bool isAlive)
{

	enemyBody.setX(bodyPos.getX());
	enemyBody.setY(bodyPos.getY());
	enemyBody.changeDir(dir);
	setChar(c);
	setIsCrosDir(changeDir);
	setGameP(theGame);
}

