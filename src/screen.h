#ifndef _SCREEN_H_
#define _SCREEN_H_


#include <iostream>
#include "const.h"
#include "Gotoxy.h"
#include "color.h"


using namespace std;

class Screen {

	char ScoreScreen[MASSAGE_ROWS][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
		//	     01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"|  @ PLAYER1: 0     AMMO: 5                            # PLAYER2: 0   AMMO: 5 |", // 0
		"|                   MISSION:                                                  |", // 1
		"-------------------------------------------------------------------------------", // 2
	};

	char GameScreen[ROWS_GAME_SCREEN][MAX_COLS] = {
	//	         10        20        30        40        50        60        70       79
	//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ", // 0
		"                                                                               ", // 1
		"                                                                               ", // 2
		"                                                                               ", // 3
		"                                                                               ", // 4
		"                                                                               ", // 5
		"                                                                               ", // 6
		"                                                                               ", // 7
		"                                                                               ", // 8
		"                                                                               ", // 9
		"                                                                               ", // 10
		"                                                                               ", // 11
		"                                                                               ", // 12
		"                                                                               ", // 13
		"                                                                               ", // 14
		"                                                                               ", // 15
		"                                                                               ", // 16
		"                                                                               ", // 17
		"                                                                               ", // 18
		"                                                                               ", // 19
		"                                                                               " // 20
   //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	};

	char replayScreen[ROWS_GAME_SCREEN][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
		//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ", // 0
		"                                                                               ", // 1
		"                                                                               ", // 2
		"                                                                               ", // 3
		"                                                                               ", // 4
		"                                                                               ", // 5
		"                                                                               ", // 6
		"                                                                               ", // 7
		"                                                                               ", // 8
		"                                                                               ", // 9
		"                                                                               ", // 10
		"                                                                               ", // 11
		"                                                                               ", // 12
		"                                                                               ", // 13
		"                                                                               ", // 14
		"                                                                               ", // 15
		"                                                                               ", // 16
		"                                                                               ", // 17
		"                                                                               ", // 18
		"                                                                               ", // 19
		"                                                                               " // 20
	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	};

	char replayScoreScreen[MASSAGE_ROWS][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
		//	     01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"|  @ PLAYER1: 0     AMMO: 5                            # PLAYER2: 0   AMMO: 5 |", // 0
		"|                   MISSION:                                                  |", // 1
		"-------------------------------------------------------------------------------", // 2
	};
	
	char MoveInstarcion[MOVE_ROWS_INS][MAX_COLS] = {
		"---------------------------------                                              ",
		"|Move keys player 1 (@) : up = w|                                              ",
		"|                       down = x|                                              ",
		"|                       left = a|                                              ",
		"|                      right = d|                                              ",
		"|-------------------------------|                                              ",
		"|Move keys player 2 (#) : up = i|                                              ",
		"|                       down = j|                                              ",
		"|                       left = l|                                              ",
		"|                      right = m|                                              ",
		"---------------------------------                                              "
	};
	char MissionIns[MISSION_ROWS_INS][MAX_COLS] = {
		"                                                                               ",
		"                                                                               ",
		"                                                                               ",
		"In each game the mission will apper next to the score,                         ",
		"The goal of each player is to be the first to collect the right number that    ",
		"answer the mission.                                                            ",
		"if the player collect the wrong number, the other player win a point.          ",
		"The gmae will end if one of the player reach to 12 points                      ",
		"GOOD LUCK ! ! ! !  May The Odd Be In Your Favor                                ",
		"                                                                               ",
		"                                                                               ",
		" Please Choose Your Action:                                                    ",
		" 1.Return to Main Menu                                                         "
	};

	char StartMenu[MASSAGE_ROWS][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
		//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"|Please choose your action:                                                   |", // 0
		"| 1.Let's Play     2.Instractions     3.Exit                                  |", // 1
		"-------------------------------------------------------------------------------", // 2
	};

	char MidMenu[MASSAGE_ROWS][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
		//	 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"|Choose Your Action: 9.Exit  2.Back to main manu  3.Countinue current mission |", // 0
		"|4. Restart this mission     5.Start a new mission   6.Start a new game       |", // 1
		"-------------------------------------------------------------------------------", // 2
	};

	char SnakeScreen[ROWS_GAME_SCREEN][MAX_COLS] = {
		//	         10        20        30        40        50        60        70       79
 //	     01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                               ", // 0
		"                                                                               ", // 1
		"     SsSsSsSsS    N n        N      Aa       K        k  eEeEeEeEeEeE          ", // 2
		"     s            n  N       n     a  A      k      K    E                     ", // 3
		"     S            N   n      N    A    a     K    k      e                     ", // 4
		"     s            n    N     n   a      A    k  K        E                     ", // 5
		"     SsSsSsSsS    N     n    N  A        a   Kk          eEeEeEeEeEeE          ", // 6
		"             s    n      N   n  aAaAaAaAaA   k  K        E                     ", // 7
		"             S    N       n  N  A        a   K    k      e                     ", // 8
		"             s    n        N n  a        A   k      K    E                     ", // 9
		"     SsSsSsSsS    N         nN  A        a   K        k  eEeEeEeEeEeE          ", // 10
		"                                                                               ", // 11
		"                                                                               ", // 12
		"                                                                               ", // 13
		"                                                                               ", // 14
		"                                                                               ", // 15
		"                                                                               ", // 16
		"                                                                               ", // 17
		"                                                                               ", // 18
		"                                                                               ", // 19
		"                                                                               " // 20

   //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	};
public:

	void printStart() {
		gotoxy(0, 0);
		for (int i = 0; i < MASSAGE_ROWS; ++i)
			cout << StartMenu[i]<< endl;
		gotoxy(0, MASSAGE_ROWS);
		for (int j = 0; j < ROWS_GAME_SCREEN - 1; ++j)
			cout << Color(GREEN,BLACK)<<SnakeScreen[j] << endl;
		cout << Color(GREEN, BLACK) << SnakeScreen[ROWS_GAME_SCREEN-1];

		cout << Color(WHITE, BLACK);

	}

	void printGame() {
		gotoxy(0, 0);
		for (int i = 0; i < MASSAGE_ROWS; ++i)
			cout << ScoreScreen[i] << endl;
		gotoxy(0, MASSAGE_ROWS);
		for (int i = 0; i < ROWS_GAME_SCREEN - 1; i++)
			cout << GameScreen[i] << endl;
		cout << GameScreen[ROWS_GAME_SCREEN - 1];
	}
	void printReplayGame() {
		gotoxy(0, 0);
		for (int i = 0; i < MASSAGE_ROWS; ++i)
			cout << replayScoreScreen[i] << endl;
		gotoxy(0, MASSAGE_ROWS);
		for (int i = 0; i < ROWS_GAME_SCREEN - 1; i++)
			cout << replayScreen[i] << endl;
		cout << replayScreen[ROWS_GAME_SCREEN - 1];
	}

	void printPause()
	{
		gotoxy(0, 0);
		for (int i = 0; i < MASSAGE_ROWS; ++i)
			cout << MidMenu[i] << endl;
	}

	void printGameOnly()
	{
		gotoxy(0, MASSAGE_ROWS);
		for (int i = 0; i < ROWS_GAME_SCREEN -1; i++)
			cout << GameScreen[i] << endl;
		cout << GameScreen[ROWS_GAME_SCREEN - 1];
	}

	void pirntScroeOnly()
	{
		gotoxy(0, 0);
		for (int i = 0; i < MASSAGE_ROWS; ++i)
			cout << ScoreScreen[i]<< endl;
	}

	void printInstrac()
	{
		gotoxy(0, 0);
		for (int i = 0; i < MOVE_ROWS_INS; ++i)
			cout << MoveInstarcion[i] << endl;
		gotoxy(0, MOVE_ROWS_INS);
		for (int j = 0;j < MISSION_ROWS_INS;++j)
		{
			cout << MissionIns[j] << endl;
		}
	}


	void updateNumbersOnArr(int loc_x, int loc_y, char number)
	{
		GameScreen[loc_y - MASSAGE_ROWS][loc_x] = number;

	}

	void updateScoreOnArr(int Player, int score)
	{
		int temp = score;
		if (score < 10)
		{
			char newScore = score + '0';
			if (Player == 0)
				ScoreScreen[SCORE_PLAYER1_ROW][SCORE_PLAYER_COL_TENS] = newScore;
			else
				ScoreScreen[SCORE_PLAYER2_ROW][SCORE_PLAYER2_COL_TENS] = newScore;
		}
		else
		{
			char Udigit = (temp % 10) + '0';
			temp /= 10;
			char Tdigit = (temp % 10) + '0';
			if (Player == 0)
			{
				ScoreScreen[SCORE_PLAYER1_ROW][SCORE_PLAYER_COL_TENS] = Tdigit;
				ScoreScreen[SCORE_PLAYER1_ROW][SCORE_PLAYER_COL_UNITS] = Udigit;
			}
			else
			{
				ScoreScreen[SCORE_PLAYER2_ROW][SCORE_PLAYER2_COL_TENS] = Tdigit;
				ScoreScreen[SCORE_PLAYER2_ROW][SCORE_PLAYER2_COL_UNITS] = Udigit;
			}
		}
	}

	
	char getInfo(int loc_x, int loc_y)
	{
		return GameScreen[loc_y - MASSAGE_ROWS][loc_x];
	}

	void ammoUpDateOnArr(int player,int ammo)
	{
		if (player == 0)
		{
			ScoreScreen[SCORE_PLAYER1_ROW][PLAYER1_AMMO_COL] = ammo + '0';
		}
		else
		{
			ScoreScreen[SCORE_PLAYER1_ROW][PLAYER2_AMMO_COL] = ammo + '0';
		}
	}

	
	void PrintScoreAmmoOnly()
	{
		gotoxy(0, SCORE_PLAYER1_ROW);
		cout << ScoreScreen[SCORE_PLAYER1_ROW];/* << endl;*/
	}

	void setReplayScreen()
	{
		for (int i = 0; i < ROWS_GAME_SCREEN; i++)
			for (int j = 0; j <MAX_COLS; j++)
				replayScreen[i][j] = GameScreen[i][j];
		
	}
	void setScoreScreen()
	{
		for (int i = 0; i < MASSAGE_ROWS; i++)
			for (int j = 0; j <MAX_COLS; j++)
				replayScoreScreen[i][j] = ScoreScreen[i][j];

	}

};
#endif // !_SCREEN_H_




