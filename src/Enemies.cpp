#include "Enemies.h"
#include "SnakesGame.h"



void Enemies::moveEnemy()
{

	if (isAlive == true)
	{
		NextMove();
		move();
		if (c == '!' || c == '%')
		{
			NextMove();
			move();
		}
	}
}

void Enemies::enemieBumpSnake(char symbol)
{
	Bullet dummy;
	int snakeNum;
	if (symbol == '@')
		snakeNum = 0;
	else
		snakeNum = 1;

	currGame->bangBang(-1, snakeNum);

}

void Enemies::changeDir()
{
	if (isCorssingTheBorder == true)
	{
		enemyBody.setDirX(enemyBody.getDirX() * -1);
		enemyBody.setDirY(enemyBody.getDirY() * -1);
	}
}
char Enemies::analMoveEnemis()
{
	int nextX = enemyBody.getX() + enemyBody.getDirX();
	int nextY = enemyBody.getY() + enemyBody.getDirY();

	Point pos(nextX, nextY);

	return currGame->getCharFromBoard(pos);
}