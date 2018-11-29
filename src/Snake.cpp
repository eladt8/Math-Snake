#include "Snake.h"

Snake::Snake(const Point& head, char c1, Direction dir, int SnSize, int sscore) {
	c = c1;
	setScore(sscore);
	setSnSize(SnSize);
	Ammo = 5;
	gotShoot = 0;
	body = new Point[SnSize];
	direction = dir;
	body[0] = head;
	body[0].draw(c);
	for (int i = 1; i < SnSize; ++i) {
		body[i] = body[i - 1];
		body[i].move(dir);
		body[i].draw(c);
	}
}

void Snake::upSnake(int i, bool isReset)
{
	if (isReset == true)
	{
		gotShoot = 0;
		if (i == 0)
		{
			{
				body[0] = { 10,9 };
				direction = Direction::RIGHT;
				body[0].changeDir(Direction::RIGHT);
			}
		}
		else
			{
				body[0] = { 70 ,9 };
				direction = Direction::LEFT;
				body[0].changeDir(Direction::LEFT);
			}
	}

	else
	{
		int newX = rand() % (MAX_COLS);
		int newY = rand() % 21 + 3;

		if (direction == Direction::RIGHT)
		{
			body[0] = { newX, newY };
			body[0].changeDir(Direction::RIGHT);
		}

		else if (direction == Direction::LEFT)
		{
			body[0] = { newX,newY };
			body[0].changeDir(Direction::LEFT);
		}

		else if (direction == Direction::UP)
		{
			body[0] = { newX , newY };
			body[0].changeDir(Direction::UP);
		}

		else if (direction == Direction::DOWN)
		{
			body[0] = { newX,newY };
			body[0].changeDir(Direction::DOWN);
		}

	}
		
}
void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown,char keyShot) {
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
	dirKeys[Direction::BULLETSMOVE] = keyShot;
}

void Snake::changeDir(char keyPressed) {
	for (const auto& key : dirKeys) {
		if (key == keyPressed) {
			direction = (Direction)(&key - dirKeys);
			return;
		}
	}
}
Point Snake::move(char keyPressed, Point &oldTail) {
	if (keyPressed != KEYS::NOMOVECHAR)
	{
		if (body[SnSize - 1].getX() != -1)
			body[SnSize - 1].draw(' ');
		oldTail = body[SnSize - 1];
		for (int i = SnSize - 1; i > 0; --i) {
			body[i] = body[i - 1];
		}
		changeDir(keyPressed);
		body[0].move(direction);
		body[0].draw(c);
	}
		return body[0];
}

Point& Snake::biggerBody() {  //����� ���� ����� ������
	SnSize++;
	Point* nArr;   //���� ���

	if (SnSize < 15)
	{
		nArr = new Point[SnSize];   //����� ���� ���� �1,
		for (int i = 0;i < SnSize - 1;++i)
		{
			nArr[i] = body[i];
		}
		nArr[SnSize - 1].setX(-1);//why?
		delete[] body;
		body = nArr;
	}
	return body[0];
}


Point Snake::preMove(char keyPressed)
{
	Direction preDir = getCurrDir();
	Point temp;

	if (keyPressed != 0) {
		for (const auto& key : dirKeys) {
			if (key == keyPressed) {
				preDir = (Direction)(&key - dirKeys);
			}
		}
	}
		
		
		temp.changeDir(preDir);
		int x = body[0].getX() + temp.getDirX();
		int y = body[0].getY() + temp.getDirY();

		Point res(x, y); //����� �� ���� ����� �� ������ �����
		return res;
}

void Snake::changePos(int i)
{
	Point s1(10, 9);
	Point s2(70, 9);

	if (i == 0)
	{
		body[0].changeDir(Direction::RIGHT);
		body[0] = s1;
	}
	else if (i = 1)
	{
		body[0].changeDir(Direction::LEFT);
		body[0] = s2;
	}

}

void Snake::shooting()
{
	
	if (Ammo > 0)
	{
		if (getChar() == '@')
			Bullets[5 - Ammo].whoShot = 0;
		else
			Bullets[5 - Ammo].whoShot = 1;

		Bullets[5 - Ammo].Bull.setX(body[0].getX() + (body[0].getDirX()));

		if ((body[0].getY() < 4) && (body[0].getDirY() == -1))
		{
				Bullets[5 - Ammo].Bull.setY(MAX_ROWS - 1);
		}
		else
			Bullets[5 - Ammo].Bull.setY(body[0].getY() + (body[0].getDirY()));


		Bullets[5 - Ammo].Bull.setDirX(body[0].getDirX());
		Bullets[5 - Ammo].Bull.setDirY(body[0].getDirY());
		Bullets[5 - Ammo].fireInTheHole = true;
		Ammo--;
	}

}


void Snake::moveBullet()
{
	for (auto &b : Bullets)
	{
		if (b.fireInTheHole == true)
		{
			if (body[0].getX() != b.Bull.getX() || body[0].getY() != b.Bull.getY())
				b.Bull.draw(' ');
			b.Bull.moveBullet();
			b.Bull.draw('*');
		}
	}
}


