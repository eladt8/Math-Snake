#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "Direction.h"
#include "color.h"
#include "const.h"

using namespace std;

class Point
{
	int x;
	int y;
	int dir_x;
	int dir_y;

	void moveImpl() {//������� �� ������ �� ������ ��� ���� �� ���� ET
		x = ((x + dir_x + max_x) % max_x);
		if (y + dir_y == max_y)
			y = min_y + 1;//ET
		else if (y + dir_y == min_y)
			y = max_y - 1;//ET
		else
			y = ((y + dir_y + max_y) % max_y);
	}
public:
	enum { min_x = 1, max_x = 79, min_y = 2, max_y = 24 };

	Point() {};

	Point(int x1 , int y1) {
		x = x1;
		y = y1;
	}

	int getX() const { return x; }
	int getY() const { return y; }
	int getDirX() const { return dir_x; }
	int getDirY() const { return dir_y; }

	void draw(char c) {
		gotoxy(x, y);
		if (c == '@')
		{
			cout <<Color(LIGHTAQUA,BLACK)<< c ;
			cout << Color(WHITE, BLACK);
		}
		else if (c =='#')
		{
			cout << Color(LIGHTGREEN, BLACK) << c;
			cout << Color(WHITE, BLACK);
		}
		else if (c == '*')
		{
			cout << Color(LIGHTRED, BLACK) << c;
			cout << Color(WHITE, BLACK);
		}
		else if (c == '$')
		{
			cout << Color(PURPLE, BLACK) << c;
			cout << Color(WHITE, BLACK);
		}
		else if (c == '!')
		{
			cout << Color(AQUA, BLACK) << c;
			cout << Color(WHITE, BLACK);
		}
		else if (c == '%')
		{
			cout << Color(LIGHTYELLOW, BLACK) << c;
			cout << Color(WHITE, BLACK);
		}
		else
			cout << c;
	}


	void changeDir(Direction dir);//��������� �� ��������

	void move(Direction dir) {
		changeDir(dir);
		moveImpl();
	}

	void moveBullet() { moveImpl(); }

	void setX(int x1) { x = x1; }
	void setY(int y1) { y = y1; }
	void setDirX(int x) { dir_x = x; }
	void setDirY(int y) { dir_y = y; }
};


#endif
