#include "missionFile.h"


missionFile::missionFile()
{
	readMissionFromText();
	randMission();
	
}

//read the text file and update the vector.
void missionFile::readMissionFromText()
{
	
	string line;
	ifstream myFile("mission.txt", ios_base::in);
	if (!myFile.is_open())
	{
		cout << "FILE ERROR";
		exit(1);
	}
	while (!myFile.eof())
	{
		getline(myFile, line);
		putMissionInVector(line);
		
	}

	setVectorSize();
	myFile.close();
}

void missionFile::makeMission( GET_MISSION&res)
{
	
	switch (res.numMission)
	{
	case 1:
	{
		
		break;
	}
	case 2:
	{
		
		res.x = rand() % 80;
		break;
	}
	case 3:
	{
		
		res.x = sqr[rand() % 13];
		break;
	}
	case 4:
	{
		
		eqMission();
		break;
	}
	case 5:
	{
		res.x = rand() % 50+1;
		do {
			res.y = rand() % 10+1;

		} while (res.y >= res.x || ((res.x%res.y) == 0));
		break;
	}
	case 6:
	{		
		res.x = rand() % 100+1;
		res.y = rand() % 100+1;
	break;
	}

	default:
		break;
	}


	
}



int missionFile::randMission()
{
	int res = rand() % readVectorSize;
	resMission = readVector[res];
	makeMission(resMission);
	IsnewMission = false;
	return res;
}




void missionFile::eqMission()
{
	eq.op1 = randOp();
	if (eq.op1 == '*')
		eq.num[0] = randNum(21, 0);
	else
		eq.num[0] = randNum(101, 0);

	eq.num[1] = randNum(21, 0);

	if (eq.op1 == '/')
	{
		if (eq.num[1] == 0)
			eq.num[1] = randNum(101, 2);

		while ((eq.num[0] % eq.num[1]) != 0)
			eq.num[1] = randNum(101, 2);


	}
	if (eq.op1 == '-')
	{
		while ((eq.num[0] - eq.num[1]) < 0)
		{
			eq.num[1] = randNum(101, 0);
		}
	}

	eq.op2 = randOp();
	if (eq.op2 == '*')
		eq.num[2] = randNum(21, 1);
	else
		eq.num[2] = randNum(21, 0);

	if (eq.op2 == '/')
	{
		if (eq.op1 != '/')
		{
			if (eq.num[2] == 0)
				eq.num[2] = randNum(101, 2);

			while ((eq.num[1] % eq.num[2]) != 0)
				eq.num[2] = randNum(101, 2);

		}
		else
		{
			int temp = eq.num[0] / eq.num[1];// ������ �������� ����� �� �� �������!!!
			if (eq.num[2] == 0)
				eq.num[2] = randNum(21, 2);

			while ((temp % eq.num[2]) != 0)
				eq.num[2] = randNum(21, 2);
		}


	}
	if (eq.op2 == '-')
	{
		while ((eq.num[1] - eq.num[2]) < 0)
		{
			eq.num[2] = randNum(101, 0);
		}
	}
	eq.num[3] = findNum4(eq.num[0], eq.num[1], eq.num[2], eq.op1, eq.op2);//������ �� 4
	do {
		eq.randPlace = rand() % 4;
		eq.currentAnswer = eq.num[eq.randPlace];

	} while (eq.num[eq.randPlace] > 169 || eq.num[eq.randPlace] < 0);

}

char missionFile::randOp()
{
	int rando = rand() % 4;
	if (rando == OP::PLUS)
		return '+';
	if (rando == OP::MINUS)
		return '-';
	if (rando == OP::MULTI)
		return '*';
	if (rando == OP::DIV)
		return '/';
}

int missionFile::randNum(int top, int low)//����� �� ���� �������
{
	int res = rand() % top + low;
	return res;
}
int missionFile::findNum4(int num1, int num2, int num3, char op1, char op2)
{
	if ((op1 == '+') && (op2 == '+'))
		return num1 + num2 + num3;
	if ((op1 == '+') && (op2 == '-'))
		return num1 + num2 - num3;
	if ((op1 == '+') && (op2 == '*'))
		return num1 + num2 * num3;
	if ((op1 == '+') && (op2 == '/'))
		return num1 + num2 / num3;
	if ((op1 == '-') && (op2 == '+'))
		return num1 - num2 + num3;
	if ((op1 == '-') && (op2 == '-'))
		return num1 - num2 - num3;
	if ((op1 == '-') && (op2 == '*'))
		return num1 - num2 * num3;
	if ((op1 == '-') && (op2 == '/'))
		return num1 - num2 / num3;
	if ((op1 == '*') && (op2 == '+'))
		return num1 * num2 + num3;
	if ((op1 == '*') && (op2 == '-'))
		return num1 * num2 - num3;
	if ((op1 == '*') && (op2 == '*'))
		return num1 * num2 * num3;
	if ((op1 == '*') && (op2 == '/'))
		return num1 * num2 / num3;
	if ((op1 == '/') && (op2 == '+'))
		return num1 / num2 + num3;
	if ((op1 == '/') && (op2 == '-'))
		return num1 / num2 - num3;
	if ((op1 == '/') && (op2 == '*'))
		return num1 / num2 * num3;
	if ((op1 == '/') && (op2 == '/'))
		return num1 / num2 / num3;
}

void  missionFile::printMission()//����� �� ������ ����
{
	gotoxy(MISSION_PRINT_COL, MISSION_PRINT_ROW);
	switch (resMission.numMission)
	{
	case 1:
	{
		cout << "collect a prime number ";
		break;
	}
	case 2:
	{
		cout << "collect multiply of " << resMission.x;
		break;
	}
	case 3:
	{
		cout << "collect the root of " << resMission.x;
		break;
	}
	case 4:
	{
		if (eq.randPlace == 0)
			cout << "___" << eq.op1 << eq.num[1] << eq.op2 << eq.num[2] << "=" << eq.num[3];
		else if (eq.randPlace == 1)
			cout << eq.num[0] << eq.op1 << "___" << eq.op2 << eq.num[2] << "=" << eq.num[3];
		else if (eq.randPlace == 2)
			cout << eq.num[0] << eq.op1 << eq.num[1] << eq.op2 << "___" << "=" << eq.num[3];
		else
			cout << eq.num[0] << eq.op1 << eq.num[1] << eq.op2 << eq.num[2] << "=" << "___";

		break;
	}
	case 5:
	{
		cout << "collect a number that div in " << resMission.x << " with carry " << resMission.y;
		break;
	}
	case 6:
	{
		cout << "collect a common divider of "<< resMission.x<<" and "<< resMission.y;
		break;
	}


	}
}

void missionFile::putMissionInVector(string line )
{
	GET_MISSION mis;
	switch (line[0])
	{
	case 'p':
	{
		mis.numMission = 1;
		break;
	}
	case 'm':
	{
		mis.numMission = 2;
		
		break;
	}
	case 's':
	{
		mis.numMission = 3;
		
		break;
	}
	case 'e':
	{
		mis.numMission = 4;
		
		break;
	}
	case 'd':
	{
		mis.numMission = 5;

		break;
	}
	case 'c':
	{		mis.numMission = 6;

	break;
	}

	default:
		break;
	}

	readVector.push_back(mis);
}
