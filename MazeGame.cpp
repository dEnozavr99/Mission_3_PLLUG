// stud.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int mapRows = 20;
const int mapColums = 20;

bool userGotKey = false;

using Map = array<array<char, mapRows>, mapColums>;
Map map;
//array<array<char, mapRows>, mapColums> map;

const char mapCodeUser = '@';
const char mapCodeExit = 'E';
const char mapCodeWall = 'X';
const char mapCodeField = ' ';
const char mapCodeKey = '&';

int userCoordX = 0;
int userCoordY = 0;
int exitCoordX = 1;
int exitCoordY = 1;
int keyCoordX = 2;
int keyCoordY = 2;

bool doesPlayerWantToPlay()
{
	bool result = false;
	char answer = ' ';

	while (true)
	{
		std::cout << "\n\tMaze Game" << std::endl;
		std::cout << "Do you want to play a game? ((1) - Yes | (0) - No)" << std::endl;
		std::cin >> answer;

		if (answer == '1')
		{
			system("cls");
			result = true;
			break;
		}
		else if (answer == '0')
		{
			std::cout << "Bye Bye" << std::endl;

			break;
		}

		std::cout << "I dont understand you" << std::endl;

	}

	return result;

}

void generateUserPosition()
{
	srand(time(NULL));
	userCoordX = 1 + rand() % 18 ;
	userCoordY = 1 + rand() % 18 ;
	map[userCoordX][userCoordY] = mapCodeExit;
	
}

void generateExitCoord()
{
	srand(userCoordX);
	exitCoordX = 1 + rand() % 18;
	exitCoordY = 1 + rand() % 18;
	map[exitCoordX][exitCoordY] = mapCodeUser;
	
}

void generateKeyCoord()
{
	srand(userCoordY);
	keyCoordX = 1 + rand() % 18;
	keyCoordX = 1 + rand() % 18;
	map[keyCoordX][keyCoordY] = mapCodeKey;
}

void filler()
{  //заповнюємо поле стінами
	for (int row = 0; row < mapRows; ++row)
	{
		for (int column = 0; column < mapColums; ++column)
		{
			map[row][column] = mapCodeWall;
		}

	}
	//заповнюємо поле пустотою
	for (int row = 1; row < mapRows-1; ++row)
	{
		for (int column = 1; column < mapColums-1; ++column)
		{
			map[row][column] = mapCodeField;
		}

	}
	//розміщуємо гравця 
	map[userCoordX][userCoordY] = mapCodeUser;
	//розміщуємо вихід
	map[exitCoordX][exitCoordY] = mapCodeExit;
	//розміщеємо ключ
	if (userGotKey == false)
		map[keyCoordX][keyCoordY] = mapCodeKey;
	else
		map[keyCoordX][keyCoordY] = mapCodeField;
	
}

void control()
{
	char direction = ' ';
	cout << "\tEnter your direction: w--up, a--left, s--down, d--right" << endl;
	cin >> direction;


	switch (direction)
	{
		case 'w':
		{
			if (map[userCoordX - 1][userCoordY] != 'X')
				userCoordX -= 1;
		}
	break;

		case 'a':
		{
			if (map[userCoordY - 1][userCoordY] != 'X')
				userCoordY -= 1;
		}
	break;

		case 's':
		{
			if (map[userCoordX + 1][userCoordY] != 'X')
				userCoordX += 1;
		}
		break;

		case 'd':
		{
			if (map[userCoordY + 1][userCoordY] != 'X')
				userCoordY += 1;
		}
		break;

	}
	/*if (userCoordX <= 1)
	{
		userCoordX += 1;
	}
	else if (userCoordX >= 18)
	{
		userCoordX -= 1;
	}
	else if (userCoordY <= 1)
	{
		userCoordY += 1;
	}
	else if (userCoordY >= 18)
	{
		userCoordY -= 1;
	}*/

	/*if (direction == 'w')
	{
		userCoordX -= 1;
	}
	else if (direction == 'a')
	{
		userCoordY -= 1;
	}
	else if (direction == 's')
	{
		userCoordX += 1;
	}
	else if (direction == 'd')
	{
		userCoordY += 1;
	}
	else
	{
		cout << "Wrong operation" << endl;
	}*/

}

void display()
{
	for (int row = 0; row < mapRows; ++row)
	{
		for (int column = 0; column < mapColums; ++column)
		{
			std::cout << map[row][column];
			if (column == mapColums - 1)
			{
				std::cout << std::endl;
			}
		
		}

	}
}

bool checkTheWin()
{
	bool result = true;

	if ((userCoordX == keyCoordX) && (userCoordY == keyCoordY))
	{
		userGotKey = true;
		std::cout << "\tYou got a key!" << std::endl;
	}

	if (userGotKey == true)
	{
		if ((userCoordX == exitCoordX) && (userCoordY == exitCoordY))
		{
			cout << "\tYou win!" << endl;
			result = false;
		}
	}

	return result;
}

void startGame()
{
	
	std::cout << "\tPlaying" << std::endl;
	filler();
	display();
	control();
	system("cls");
}

int main()
{//дописти ключик
	//лабіринт 

	while (doesPlayerWantToPlay())
	{
		generateUserPosition();
		generateExitCoord();

		while (checkTheWin())
		{
			startGame();
			//cout << userCoordX << " " << userCoordY << endl;
			//cout << exitCoordX << " " << exitCoordY << endl;
		}
		
	}


	return 0;
}
