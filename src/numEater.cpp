#include "numEater.h"
#include "SnakesGame.h"


void numEater::move()
{
	enemyBody.draw(' ');
	currGame->addCharToScreen(' ', enemyBody.getX(), enemyBody.getY());
	currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(), ' ', currGame->getCountSleep());
	enemyBody.moveBullet();
	currGame->addCharToScreen(c, enemyBody.getX(), enemyBody.getY());
	currGame->getRplayP()->getMoveForReplay(enemyBody.getX(), enemyBody.getY(), c, currGame->getCountSleep());
	enemyBody.draw(c);

}

void numEater::NextMove()
{
	PATH path;

	path = currGame->findCorrectAnswerForNumEater(enemyBody);

	if (path.Length==-1)

		enemyBody.changeDir(Direction::NOMOVE);
	else
	{
		if (path.target.XY.getY() != enemyBody.getY())
			if (path.dirY == -1)
				enemyBody.changeDir(Direction::UP);
			else
				enemyBody.changeDir(Direction::DOWN);
		else
			if (path.dirX == -1)
				enemyBody.changeDir(Direction::LEFT);
			else
				enemyBody.changeDir(Direction::RIGHT);
	}
	Point nextPos ={ ((enemyBody.getX() + enemyBody.getDirX())%MAX_COLS),((enemyBody.getY() + enemyBody.getDirY())%MAX_ROWS)};

	char nextMoveChar = analMoveEnemis();

	if (nextMoveChar == '@' || nextMoveChar == '#')
	{
		if (nextMoveChar == '@')
		{
			currGame->wasted(0);//����� ����� ����
			currGame->endOfMission(1);//������� ������� ����� ����� ��� 
			
		}
		else
		{
			currGame->wasted(1);
			currGame->endOfMission(0);
		}
		currGame->addCharToScreen(' ', enemyBody.getX(), enemyBody.getY());

		enemyBody.setX(10);
		enemyBody.setY(19);
		setIsAlive(false);
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

numEater::numEater(Point bodyPos, char c, SnakesGame * theGame, bool isAlive)
{

	enemyBody.setX(bodyPos.getX());
	enemyBody.setY(bodyPos.getY());
	setIsAlive(isAlive);
	setChar(c);
	setGameP(theGame);
}



