#pragma once
#include <stdio.h>
#include <conio.h>
#include "windows.h" 
#include<stdbool.h>
#include<time.h>
int sl = 4;
bool Hit_Wall(int* coorX, int* coorY);
bool Self_Hit(int* coorX, int* coorY);
bool Snake_Eat_Fruit(int* coorX, int* coorY);
bool Snake_Hit_Fruit(int* coorX, int* coorY);
void Create_Fruit(int* coorX, int* coorY, int* Rx, int* Ry);
void Check_Fruit(int* coorX, int* coorY, int row, int col);
void Eat(int* coorX, int* coorY);
void After_Eat(int* coorX, int* coorY, int* Rx, int* Ry);
void Draw(int* Rx, int* Ry);


void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int random(int min, int max)
{
	srand(time(0));
	return min + rand() % (max + 1 - min);
}
