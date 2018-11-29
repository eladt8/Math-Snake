#include "replayGame.h"
#include "SnakesGame.h"




void replayGame::actForReplay()//������ ������ �����
{
	currGame->getScreenP()->setReplayScreen();
	currGame->getScreenP()->setScoreScreen();
	clearQueue(Qreplay);//����� �� ����
}

void replayGame::makeReplay()
{
	//���� ������ �� ����� ������ ����� ������

	int i = 1;
	REPLAY rep;
	currGame->getScreenP()->printReplayGame();
	currGame->printMis();
	
	rep= Qreplay.front();

	while (!Qreplay.empty())
	{
		while (i == rep.countForSleep && !Qreplay.empty())
		{
			draw(rep.locX, rep.locY, rep.ch);
			beckupQreplay.push(rep);
			Qreplay.pop();
			if (!Qreplay.empty())
			{
				rep = Qreplay.front();

			}

		}
		Sleep(200);
		i++;
	}

	restoreQueuAfterReplay();
}

void replayGame::getMoveForReplay(int locX, int locY, char ch, int countForSleep)
{
	REPLAY res;
	res.ch = ch;
	res.locX = locX;
	res.locY = locY;
	res.countForSleep = countForSleep;

	Qreplay.push(res);

}

void replayGame::clearQueue(queue<REPLAY>& q1)
{
	while (!q1.empty())
		q1.pop();

}
void replayGame::draw(int x,int y,char c) {
	gotoxy(x, y);
	if (c == '@')
	{
		cout << Color(LIGHTAQUA, BLACK) << c;
		cout << Color(WHITE, BLACK);
	}
	else if (c == '#')
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

void replayGame::restoreQueuAfterReplay()
{
	REPLAY temp;

	while (!beckupQreplay.empty())
	{
		temp = beckupQreplay.front();
		Qreplay.push(temp);
		beckupQreplay.pop();
	}

}
