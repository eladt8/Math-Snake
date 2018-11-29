#include "SnakesGame.h"



void SnakesGame::run()
{
	srand(seedTime);

	int foodNum;
	Point oldTail;
	Point nextMove;
	int xNext, yNext;
	char nextChar;
	int k;
	
	hideCursor();
	Boards.printGame();
	mission.printMission();
	while (!exitGame)//����� �� ������ ESC ET
	{

		if (mission.getIsNewMission())
		{
					
			StartNewMission();
			Boards.printGameOnly();
			mission.updateIsNewMission(false);
			replayG.actForReplay();
			_flushall();
		}

		char keyPressed = 0;
		if (_kbhit()) {
			keyPressed = _getch();

			if (keyPressed == KEYS::ESC) {
				Boards.printPause();
				pauseMenu();

			}
		}
		countStepsForReplay++;//���� �� ���� ��������  ��� ���� �� ����� �������
		Sleep(130);//���� �� ������� (�� ��������)ET
		for (int i = 0; i < AMOUNTOFSNAKES && !exitGame ; ++i) {
			if (snakes[i].getGotShoot() == 0)//���� �� ���� ���� ���� ������
			{
				if (keyPressed == snakes[i].getKeyShot())
				{
					snakes[i].shooting();
					analBulletMove(snakes[i].returnBulletArr());
					keyPressed = 0;
				}
				nextMove = snakes[i].preMove(keyPressed);
				xNext = nextMove.getX();
				yNext = nextMove.getY();
				nextChar = Boards.getInfo(xNext, yNext);
				if ((nextChar >= '0') && (nextChar <= '9')) //�� ���� ��� ��� ����
				{
					foodNum = getNumber(nextMove);//���� �� ����
					if (correctAnswer(foodNum))//����� �� �� ���� �����
					{
						goodAnswer(i);
						endOfMission(i);

					}
					else
					{
						WorngAnswer((i + 1) % 2);
						endOfMission((i + 1) % 2);

					}

					reduceFood(countFood, false);
					mission.updateIsNewMission(true);
					break;
				}
				else if ( nextChar == '!' || nextChar == '$')
				{
					bangBang(-1,i);
				}
				else if (nextChar == '%')
				{
					//player i had been eated
					wasted(i);
					endOfMission((i + 1) % 2);
					addCharToScreen(' ', enemArr[4]->getbodyX(), enemArr[4]->getbodyY());
					enemArr[4]->setBodyX(10);
					enemArr[4]->setBodyX(19);

					break;

				}
				else if (nextChar == '@' || nextChar == '#')

					snakes[i].move(KEYS::NOMOVECHAR, oldTail);  //���� ����� 0 0 
				
				else
					snakes[i].move(keyPressed, oldTail);

				if (snakes[i].getGotShoot() == 0)
					printSnakeOnBoardArr(i, oldTail);

			}
			for ( k = 0;k <5;k++)
			{
				enemArr[k]->moveEnemy();
			
			}
			if (!enemArr[4]->getIsAlive())
				break;
			for ( k = 0; k < 2; k++)
			{
				analBulletMove(snakes[i].returnBulletArr());//################################################3
				printBulletsOnArr(i, ' ');//board
				snakes[i].moveBullet();//cout to the screen
				printBulletsOnArr(i, '*');//board
			}

			
				Boards.PrintScoreAmmoOnly();

				
			
			countSteps++;
			
			if (countSteps % 10 == 0) //���� �� ���� i ��� 10
			{
				addNumber();

				if (snakes[i].getGotShoot() > 0) //���� �� ��� 1
				{
					snakes[i].decGetShoot();
					if (snakes[i].getGotShoot() <= 0)//����� ����� ��� �� ���� ����� �����
					{
						snakes[i].upSnake(i, false);
						checkNumbersAroundNewLoc(i);
					}
				}
				if (snakes[(i + 1) % 2].getGotShoot() > 0) //���� �� ��� 0
				{
					snakes[(i + 1) % 2].decGetShoot();
					if (snakes[(i + 1) % 2].getGotShoot() <= 0)//����� ����� ��� �� ���� ����� �����
					{
						snakes[(i + 1) % 2].upSnake(i, false);
						checkNumbersAroundNewLoc(i);
					}
				}
			}
			
		}



		if (countFood == 60)
		{
			findCorrectAnswer(); //����� �� ����� ����� ������ ����
			reduceFood(countFood,false); //������ ���� �� ������� �� ����
			StartNewMission(); //������ ����� ����
			Boards.printGameOnly();
		}

	}
}



void SnakesGame::relocSnakes()
{
	for (int i = 0; i < 2; i++)
	{
		DeleteSnakesFromArr(i);
		snakes[i].upSnake(i, true);//gets true if need to rest the places
		checkNumbersAroundNewLoc(i);
	}
}

void SnakesGame::checkNumbersAroundNewLoc(int snakeNum)   //����� ������ ������ ������ �������
{
	
	int snakeSize = snakes[snakeNum].GetSnakeSize();
	int posX = snakes[snakeNum].currentPos(0).getX() + snakes[snakeNum].currentPos(0).getDirX() , posY= snakes[snakeNum].currentPos(0).getY() + snakes[snakeNum].currentPos(0).getDirY();
	int numberFirstDigit;


	if ((Boards.getInfo(posX, posY) <= '9') && (Boards.getInfo(posX, posY ) >= '0'))
	{
		numberFirstDigit = findNumber(posX , posY);

		for (int j = 0;j < countFood;++j)
		{
			if ((numberFirstDigit == food[j].XY.getX()) && (posY == food[j].XY.getY()))
			{
				removeFood(countFood, j);
			}
		}
	}



}

void SnakesGame::DeleteSnakesFromArr(int SnakeNumber)
{
	int snakeSize = snakes[SnakeNumber].GetSnakeSize();
	Point currPlace;

	for (int j = 0;j < snakeSize;j++)
	{

		currPlace = snakes[SnakeNumber].currentPos(j);
		if (snakes[SnakeNumber].currentPos(j).getX() >= 0)// ���� ���� ����� ����, ���� ������ ����

		{
			Boards.updateNumbersOnArr(currPlace.getX(), currPlace.getY(), ' ');
			replayG.getMoveForReplay(currPlace.getX(), currPlace.getY(), ' ',countStepsForReplay);
		}
	}

}


int drawNumber()   //����m�� ������� ���� �������
{
	int i = rand() % 3 + 1;
	if (i == 1)
	{
		return rand() % 26;
	}
	else if (i == 2)
	{
		return rand() % 56 + 26;
	}
	else
		return rand() % 88 + 82;

}
void  SnakesGame::addNumber()
{
	int newNum, newNumS, loc = 0;
	int loc_x, loc_y;
	newNum = drawNumber();//���� �� �������� (������ ����)
	newNumS = countDig(newNum);//������� ������ ����� �� �����
	while (loc != 1)
	{
		loc_x = rand() % (MAX_COLS) ;
		loc_y = rand() % 20 + 3;
		loc = checkLoc(loc_x, loc_y, newNumS);//����� �� ������ ������ ���� ������
	}
	putInTable(newNum, newNumS, loc_x, loc_y);//������ �� ����� �� ����
}
int SnakesGame::countDig(int num)//ET
{
	int i=0;
	if (num == 0)
		return 1;
	else
	{
		while (num != 0)
		{
			num /= 10;
			i++;
		}

		return i;
	}
}
//check if the position is good ET
int SnakesGame::checkLoc(int x, int y, int numSize)
{
	int flag = 1;
	int countX = x;
	Point posSnake, nextMoveOfHead;
	//check in the screen
	while (countX <= Point::max_x && numSize >= 0 && flag == 1)//check for the right
	{
		if (countX == Point::max_x)//check if at the line
		{
			flag = 0;
			break;
		}

		if ((getDigit(countX - 1, y) != -1) || (getDigit(countX, y - 1) != -1) || (getDigit(countX, y + 1) != -1))//check for the left up and down
			flag = 0;

		 if (getDigit(countX, y) == -1)
		{
			numSize--;
			countX++;
		}
		else
		{
			flag = 0;
			break;

		}
		 

	}


	//	check the snakes
	for (int i = 0; i < AMOUNTOFSNAKES && flag == 1; ++i)  //����� �� ��� ������
	{
		int SnakeSize = snakes[i].GetSnakeSize(); //����� �� ����� �� ����
	
		for (int j = 1; j < SnakeSize && flag == 1; ++j)  //����� �� ���� �� ���� ������ ��� ����� �� ���� ��� ����
		{
			posSnake = snakes[i].currentPos(j); //����� �� ������ �� ���� ����� ��'��
			if ((posSnake.getX() == x) && (posSnake.getY() == y))
				flag = 0;
		}
		Bullet * clip = snakes[i].returnBulletArr();
		for (int k = 0;k < AMMO;k++)
		{
			if (clip[k].fireInTheHole == true)
			{
				if (clip[k].Bull.getX() == x && clip[k].Bull.getY() == y) //�� �� �����
					flag = 0;
				if (clip[k].Bull.getDirX() + clip[k].Bull.getX() == x && clip[k].Bull.getDirY() + clip[k].Bull.getY() == x) //�� ���� �� ����
					flag = 0;
			}
		}

	}
	return flag;
}


bool SnakesGame::correctAnswer(int numEaten)
{
	switch (mission.getMIssion().numMission)
	{
	case 1:
	{
		bool isPrime = true;
		if (numEaten <= 1)
			return false;
		for (int i = 2; i <= numEaten/2; ++i)
		{
			if (numEaten % i == 0)
			{
				isPrime = false;
				break;
			}
		}
		return isPrime;
		break;
	}
	case 2:
	{
		if (numEaten % mission.getMIssion().x == 0)
			return true;
		else
			return false;
		break;
	}

	case 3:
	{
		if (numEaten==pow(mission.getMIssion().x,2))
			return true;
		else
			return false;
		break;
	}
	case 4:
	{
		if (mission.reCorrectAnswer() == numEaten)
			return true;
		else
			return false;
	}
	case 5:
	{
		if (numEaten % mission.getMIssion().x == mission.getMIssion().y)
			return true;
		else
			return false;
		break;
	}
	case 6:
	{
		if ((numEaten != 0)&&(mission.getMIssion().x % numEaten == 0) && (mission.getMIssion().y % numEaten == 0))
				return true;
		else
			return false;
		break;
	}


	}
}

void  SnakesGame::putInTable(int newNum, int numSize, int loc_x, int loc_y)  //print the number to the screen and insert to the string table and to the food array
{
	
	gotoxy(loc_x, loc_y);
	cout << newNum;

	addNumToScreen(newNum, numSize, loc_x, loc_y);

	food[countFood].number = newNum;
	food[countFood].XY = { loc_x,loc_y };
	food[countFood].size = numSize;


	countFood++;

}
void SnakesGame::addNumToScreen(int number, int size, int loc_x, int loc_y)  //add number to the string array
{
	int i, temp = number, digit;
	if (number == 0)
	{
		Boards.updateNumbersOnArr(loc_x, loc_y, '0');
		replayG.getMoveForReplay(loc_x, loc_y, '0', countStepsForReplay);
	}
	else
	{
		for (i = 1; i <= size; i++)
		{
			digit = temp % 10;
			Boards.updateNumbersOnArr(loc_x + (size - i), loc_y, digit + '0');
			replayG.getMoveForReplay(loc_x + (size - i), loc_y, digit + '0',countStepsForReplay);
			temp /= 10;
		}
	}
}


void SnakesGame::reduceFood(int &countFood,bool all)  //reduce food from the food array bool for all the numbers or just half
{
	int i;
	int random;
	int size;
	if (!all)
		size = countFood / 2;
	else
		size = countFood;

	for (i = 0; i < size; i++)
	{
		random = rand() % countFood;
		removeFood(countFood, random);//������ ���� ����� ������� ������� �� ����
	
	}
	
}

void SnakesGame::removeFood(int &size, int index) //remove certin food from certin place
{
	int i ;
	removeFromScreen(food[index]);//����� �� ����� �����
	for (i = index; i < size; i++)
	{
		food[i] = food[i + 1];
	}
	food[size-1].number = food[size-1].size = -1;
	food[size-1].XY = {-1,-1} ;

	size-=1;
}

void SnakesGame::removeFromScreen(FOOD food) //���� ������ �� ����
{
	int i, numSize = food.size;
	Point pose = food.XY;
	for (i = 0; i < numSize; i++)
	{	
		Boards.updateNumbersOnArr(pose.getX() + i, pose.getY(), ' ');
		replayG.getMoveForReplay(pose.getX() + i, pose.getY(), ' ',countStepsForReplay);
	}
}

bool SnakesGame:: bumpFriend(Point head) //will check if the snake crush
{
	int x = head.getX() + head.getDirX();
	int y = head.getY() + head.getDirY();

	if (Boards.getInfo(x,y) == '@' || Boards.getInfo(x,y)=='#')
		return false;
	else
		return true;
}

void SnakesGame::printSnakeOnBoardArr(int SnakeNumber, Point oldTailToRemove)  //put in the string array the char of snakes in thier pos.
{
	if (oldTailToRemove.getX() >= 0)
	{
		Boards.updateNumbersOnArr(oldTailToRemove.getX(), oldTailToRemove.getY(), ' ');
		replayG.getMoveForReplay(oldTailToRemove.getX(), oldTailToRemove.getY(), ' ', countStepsForReplay);
	}
	Point PlaceOfSnakeOnBoard = snakes[SnakeNumber].currentPos(0);
	Boards.updateNumbersOnArr(PlaceOfSnakeOnBoard.getX(), PlaceOfSnakeOnBoard.getY(), snakes[SnakeNumber].getChar());
	replayG.getMoveForReplay(PlaceOfSnakeOnBoard.getX(), PlaceOfSnakeOnBoard.getY(), snakes[SnakeNumber].getChar(), countStepsForReplay);
}


void SnakesGame::LetsStart()
{
	Boards.printStart();
	bool end = false;
	while (!end)//����� �� ������ ESC ET
	{
		char keyPressed = 0;
		if (_kbhit()) {
			keyPressed = _getch();
			if (keyPressed == KEYS::ONE)
			{
				run();
				end = true;
			}
			if (keyPressed == KEYS::TWO)
				printInstractions();
			if (keyPressed == KEYS::THREE)
			{
				end = true;
				break;
			}

		}
	}
}

void SnakesGame::printInstractions() {
	Boards.printInstrac();
	while (true)//����� �� ������ ESC ET
	{
		char keyPressed = 0;
		if (_kbhit()) {
			keyPressed = _getch();
			if (keyPressed == KEYS::ONE)
			{
				Boards.printStart();
				break;
			}
		}
	}
}

void SnakesGame::pauseMenu() {
	bool stops = true;
	while (stops)
	{
		
		char keyPressed = 0;
		if (_kbhit()) {
			keyPressed = _getch();
			switch (keyPressed)
			{
			case KEYS::NINE: //exit game
				exitGame = true;
				stops = false;
				break;
			case KEYS::TWO:  //back to main menu
			{
				reduceFood(countFood, true);
				relocSnakes();
				deleteBullets();
				LetsStart();
				stops = false;
				exitGame = true;
				break;
			}
			case KEYS::THREE:  //countinue
			{
				Boards.printGame();
				mission.printMission();
				stops = false;
				break;
			}
			case KEYS::FOUR: // restart this misssion
			{
				reduceFood(countFood, true);
				relocSnakes();
				deleteBullets();
				Boards.printGame();
				mission.printMission();
				stops = false;
				break;
			}
			case KEYS::FIVE: //start a new mission
			{
				reduceFood(countFood, true);
				StartNewMission();
				mission.printMission();
				Boards.printGameOnly();
				stops = false;
				break;
			}
			case KEYS::SIX://start a new game
			{
				SnakesGame newGame;
				newGame.LetsStart();
				break;
			}
			case KEYS::SEVEN:
			{
				replayG.makeReplay();
				stops = false;
				Boards.printPause();
				pauseMenu();
				break;

			}
			}
		}
	}
}


void SnakesGame::findCorrectAnswer() {
	for (int i = 0;i < countFood;++i)
	{
		if (correctAnswer(food[i].number))
		{
			gotoxy(food[i].XY.getX(), food[i].XY.getY());
			cout << Color(RED, YELLOW) << food[i].number;
			break;
		}
	}
	cout << Color(WHITE,BLACK);
}

PATH SnakesGame::findCorrectAnswerForNumEater(Point point)//����� �� ������ ����  ����� ������ ������ ������
{
	int  min=105;
	PATH res,temp;

	res.Length = -1;

	if (countFood > 0)
	{
		

		for (int i = 0; i < countFood; ++i)
		{
				if (correctAnswer(food[i].number))

			{
				temp = pathFinder(food[i].XY.getX(), food[i].XY.getY(), point);
				if (temp.Length <= min)
				{
					res = temp;
					min = temp.Length;
					res.target = food[i];
				}
			}
		}
	}

	return res;

}

PATH SnakesGame::pathFinder(int posX, int posY, Point posOfNumeater)
{
	PATH res;
	int dirX = posX - posOfNumeater.getX();
	int dirY = posY - posOfNumeater.getY();

	if (abs(dirX) < MAX_COLS / 2) //���� ����� �� ���? ��� ����� ��� �� ���� �����
	{
		if (dirX < 0)  //�� ����� ����� �� ����� ����� ����� ������
			res.dirX = -1;
		else
			res.dirX = 1;
	}
	else
	{
		if (dirX < 0)  
			res.dirX = 1;
		else
			res.dirX = -1;
	}
	if (abs(dirY) < MAX_ROWS / 2)
	{
		if (dirY < 0)
			res.dirY = -1;
		else
			res.dirY = 1;
	}
	else
	{
		if (dirY < 0)
			res.dirY = 1;
		else
			res.dirY = -1;
	}

	res.Length = abs(dirX) + abs(dirY);

	return res;
}



void SnakesGame::StartNewMission()
{
	countSteps = 0;
	relocSnakes();
	resurrection();
	_flushall();
	deleteBullets();
	Boards.pirntScroeOnly();
	mission.randMission();
	mission.printMission();
}



void SnakesGame::deleteBullets()  //����� �� ��� ������� �����
{
	for (int i = 0;i < AMOUNTOFSNAKES;i++)
	{
		BULLET * res = snakes[i].returnBulletArr();

		for (int j = 0;j < AMMO;j++)
		{
			if (res[j].fireInTheHole == true)
			{
				Boards.updateNumbersOnArr(res[j].Bull.getX(), res[j].Bull.getY(), ' ');
				replayG.getMoveForReplay(res[j].Bull.getX(), res[j].Bull.getY(), ' ', countStepsForReplay);
				res[j].fireInTheHole = false;
			}
		}
		snakes[i].reloadAmmo(AMMO);
		Boards.ammoUpDateOnArr(i, AMMO);
	}
}

void SnakesGame::analBulletMove(Bullet * arr)  //������� ������ �� ���� ��� �� ����� ������ ����� �����
{
	int count=0;
	int nextX, nextY;
	for (int i = 0;i < AMMO;i++)
	{
		if (arr[i].fireInTheHole == true)
		{
			if ((arr[i].Bull.getX() - arr[i].Bull.getDirX() == snakes[arr[i].whoShot].currentPos(0).getX()) &&  //to eliminate double moving bullet when get firing.
				(arr[i].Bull.getY() - arr[i].Bull.getDirY() == snakes[arr[i].whoShot].currentPos(0).getY()))
			{
				nextX = arr[i].Bull.getX();
				nextY = arr[i].Bull.getY();
			}
			else
			{
				nextX = arr[i].Bull.getX() + arr[i].Bull.getDirX();
				nextY = arr[i].Bull.getY() + arr[i].Bull.getDirY();
				if (nextY < 3)
				{
					nextY = (nextY + ROWS_GAME_SCREEN) % MAX_ROWS;
				}
			}
			char nextCharForBullets = Boards.getInfo(nextX, nextY);
			Point temp(nextX, nextY);

			if (nextCharForBullets == '@')
			{
				bangBang(arr[i].whoShot, 0);
				deleteBulet(arr[i]);
			}
			else if (nextCharForBullets == '$'  )
			{
				
				BangEnmey(arr[i], -1);
				deleteBulet(arr[i]);

			}
			else if (nextCharForBullets == '%')
			{
				BangEnmey(arr[i], -2);
				deleteBulet(arr[i]);
			}
			else if (nextCharForBullets == '!')
				deleteBulet(arr[i]);
			else if (nextCharForBullets == '#')
			{
				bangBang(arr[i].whoShot, 1);
				deleteBulet(arr[i]);
			}

			else if (nextCharForBullets >= '0' && nextCharForBullets <= '9')
			{
				int num = getNumber(temp);
				deleteNumberWhenBang(temp, num);
				deleteBulet(arr[i]);

			}
			for (int k = 0; k < AMOUNTOFSNAKES; k++)
			{
				if (deleteWhenCrushed2Bullets(snakes[k].returnBulletArr(), arr[i].Bull))
					deleteBulet(arr[i]);
			}
			
		}
	}
}
bool SnakesGame::deleteWhenCrushed2Bullets(Bullet * arr, Point Pos)
{
	bool res = false;
	for (int i = 0;i < AMMO;i++)
	{
		if (arr[i].fireInTheHole == true)
		{
			if ((arr[i].Bull.getX() == Pos.getX()+Pos.getDirX()) && (arr[i].Bull.getY() == Pos.getY()+Pos.getDirY()))
				if (arr[i].Bull.getDirX() != Pos.getDirX() || arr[i].Bull.getDirY() != Pos.getDirY())
				{
					deleteBulet(arr[i]);
					res = true;
				}
		}
	}
	return res;
}




void SnakesGame::WorngAnswer(int i)
{
	gotoxy(MISSION_PRINT_COL, SCORE_PLAYER2_ROW);
	cout <<Color(RED,YELLOW) << "Player " << snakes[(i+1)%2].getChar()<< " WRONG ANSWER!!";
	cout << Color(WHITE, BLACK);
	findCorrectAnswer();
	Sleep(3500);

}

void SnakesGame::wasted(int i)
{
	gotoxy(MISSION_PRINT_COL, SCORE_PLAYER2_ROW);
	cout << Color(RED, YELLOW) << "Player " << snakes[i].getChar() << " Has been eaten";
	cout << Color(WHITE, BLACK);
	Sleep(2500);
}
void SnakesGame::deleteNumberWhenBang(Point temp, int num)
{
	int count = 0;
	if (num == 0)
	{
		gotoxy(temp.getX() , temp.getY());
		cout << ' ';
	}


	else
		for (num; num > 0; num /= 10)
		{
			if (Boards.getInfo(temp.getX() + count, temp.getY()) != '@' || Boards.getInfo(temp.getX() + count, temp.getY()) != '#')
			{
				gotoxy(temp.getX() + count, temp.getY());
				cout << ' ';

			}
			count++;

		}
}
void SnakesGame::endOfMission(int snakeNum)
{
	char key = 0;
	if (_kbhit())
		key = _getch();

	if (key == KEYS::ESC)
	{
		Boards.printPause();
		pauseMenu();
	}

	checkScore(snakeNum);// ����� �� ����� ���� �12 ������. ������� �� �����
	snakes[snakeNum].biggerBody();
	snakes[snakeNum].upScore();
	Boards.updateScoreOnArr(snakeNum, snakes[snakeNum].getScore());
	reduceFood(countFood, false);
	mission.updateIsNewMission(true);
	countStepsForReplay = 0;

}
void SnakesGame::goodAnswer(int i)
{
	gotoxy(MISSION_PRINT_COL, SCORE_PLAYER2_ROW);
	cout << Color(RED, YELLOW) << "Player " << snakes[i].getChar() << " WELL DONE!!";
	cout << Color(WHITE, BLACK);
	Sleep(3500);
}

int SnakesGame::findNumber(int x, int y) {
	while ((Boards.getInfo(x, y) <= '9') && (Boards.getInfo(x, y) >= '0'))
		x--;
	++x;
	return x;
}

void SnakesGame::checkScore(int i) {
	int score = snakes[i].getScore();


	if (score == 11)
	{
		system("cls");
		gotoxy(23, 8);
		cout << Color(LIGHTGREEN, PURPLE) << "The Winner Is Player " << i + 1 << "snake sign '" << snakes[i].getChar() << "'" << endl;
		gotoxy(28, 9);
		cout << "Cya Next Time... GOOD BYE!" <<Color(WHITE,BLACK)<< endl;
		Sleep(3000);
		exitGame = true;
	}
}

void SnakesGame::printBulletsOnArr(int i,char c)  //������ �� ������� ����� �� ����� ������
{
	BULLET * res = snakes[i].returnBulletArr();
	
	for (int j = 0;j < AMMO;j++)
	{
		if (res[j].fireInTheHole == true)
		{
			int posX = res[j].Bull.getX();  
			int posY = res[j].Bull.getY();

			if (snakes[i].currentPos(0).getX() != posX || snakes[i].currentPos(0).getY() != posY)
			{
				Boards.updateNumbersOnArr(posX, posY, c);
				replayG.getMoveForReplay(posX, posY, c, countStepsForReplay);
			}
		}
	}
	Boards.ammoUpDateOnArr(i, snakes[i].getAmmo()); 
}

void SnakesGame::bangBang(int whoShot,int hurt)
{

	if (hurt != whoShot && whoShot >=0)
		snakes[whoShot].reloadAmmo(snakes[whoShot].getAmmo()+1);
	
		DeleteSnakesFromArr(hurt);
		snakes[hurt].upgotShoot(5);

		for (int k = 0; k < snakes[hurt].GetSnakeSize();k++)
		{
			gotoxy(snakes[hurt].currentPos(k).getX(), snakes[hurt].currentPos(k).getY());
			cout << ' ';


		}
	}
	

void SnakesGame::deleteBulet(Bullet& b)
{
	if (snakes[b.whoShot].currentPos(0).getX() != b.Bull.getX() || snakes[b.whoShot].currentPos(0).getY() != b.Bull.getY() || snakes[b.whoShot].currentPos(0).getDirX() != b.Bull.getDirX() || snakes[b.whoShot].currentPos(0).getDirY() != b.Bull.getDirY())
		
		{
			Boards.updateNumbersOnArr(b.Bull.getX(), b.Bull.getY(), ' ');
			replayG.getMoveForReplay(b.Bull.getX(), b.Bull.getY(), ' ',countStepsForReplay);
			gotoxy(b.Bull.getX(), b.Bull.getY());
			cout << ' ';
		}
		b.fireInTheHole = false;

}

Bullet & SnakesGame::returnBulletByPlace(int loc_x, int loc_y)
{
	Bullet *arr;
	

	for (int i = 0;i < 2;i++)
	{
		arr = snakes[i].returnBulletArr();
		for (int k = 0;k < AMMO;k++)
		{
			if (arr[k].fireInTheHole == true)
				if (arr[k].Bull.getX() == loc_x && arr[k].Bull.getY() == loc_y)
					return arr[k];
		}
			
	}
	
}

void SnakesGame::BangEnmey(Bullet b,int hurt)//-1 while flycol and -2 while numeater
{
	if (hurt == -1) //������ ������ 
	{
		snakes[b.whoShot].reloadAmmo(snakes[b.whoShot].getAmmo() + 1);
		for (int k = 0;k < 2;k++)
		{
			if (enemArr[k]->getbodyX() == b.Bull.getX() )
			{
				enemArr[k]->setIsAlive(false);
			}

		}
	}
	//else if (hurt==-2)
	//{
	//	enemArr[4]->setIsAlive(false);
	//}
}

void SnakesGame::resurrection()
{
	for (auto & b : enemArr)
	{
		b->setIsAlive(true);
	}
}

void SnakesGame::printMis()
{
	mission.printMission();
}
