#include"Header.h"

///////////////////////////////////////////////////////////////// Wall
void Wall()
{
	for (int row = 10; row <= 95; row++)
	{
		gotoXY(row, 1);
		printf("-");
		gotoXY(row, 25);
		printf("-");
	}
	for (int col = 1; col <= 25; col++)
	{
		gotoXY(10, col);
		printf("|");
		gotoXY(95, col);
		printf("|");
	}
}

///////////////////////////////////////////////////////////////// Snake
void Create_Snake(int* coorX, int* coorY)
{
	int* row = random(20, 70);
	int* col = random(5, 20);

	for (int i = 0; i < sl; i++)
	{
		*(coorX + i) = row--;
		*(coorY + i) = col;
	}
}
void Draw_Snake(int* coorX, int* coorY)
{
	for (int i = 0; i < sl; i++)
	{
		gotoXY(*(coorX + i), *(coorY + i));
		if (i == 0)
		{
			printf("0");
		}
		else
		{
			printf("o");
		}
	}
}

///////////////////////////////////////////////////////////////// Fruit
void Create_Fruit(int* coorX, int* coorY, int* Rx, int* Ry)
{
	do
	{
		*Rx = random(10, 95);
		*Ry = random(1, 25);
	} while (Snake_Hit_Fruit(coorX, coorY, Rx, Ry));
}
void Draw(int Rx, int Ry)
{
	gotoXY(Rx, Ry);
	printf("$");
}

///////////////////////////////////////////////////////////////// Conditions
void Move(int* coorX, int* coorY, int newX, int newY) {
	for (int i = sl; i > 0; i--)
	{
		*(coorX + i) = *(coorX + i - 1);
		*(coorY + i) = *(coorY + i - 1);
	}
	*(coorX + 0) = newX;
	*(coorY + 0) = newY;


}
void After_Eat(int* coorX, int* coorY, int* Rx, int* Ry)
{
	if (Snake_Eat_Fruit(coorX, coorY, Rx, Ry))
	{
		sl++;
		Create_Fruit(coorX, coorY, Rx, Ry);
		*Rx += random(10, 20);
		*Ry -= random(1, 5);
		if (*Rx >= 95 || *Rx <= 10 && *Ry >= 25 || *Ry <= 1)
		{
			*Rx = 50;
			*Ry = 20;
		}
	}
}

///////////////////////////////////////////////////////////////// Game_Over Conditions
bool Snake_Hit_Fruit(int* coorX, int* coorY, int* Rx, int* Ry)
{
	for (int i = 0; i < sl; i++)
	{
		if (*Rx == *(coorX + i) && *Ry == *(coorY + i)) {
			return true;
		}
	}
	return false;
}
bool Snake_Eat_Fruit(int* coorX, int* coorY, int* Rx, int* Ry)
{
	return *Rx == *(coorX + 0) && *Ry == *(coorY + 0);
}
bool Hit_Wall(int* coorX, int* coorY)
{
	if (*(coorX + 0) == 10 || *(coorX + 0) == 95 || *(coorY + 0) == 1 || *(coorY + 0) == 25)
	{
		return true;

	}
	return false;
}
bool Self_Hit(int* coorX, int* coorY)
{
	for (int i = 0; i <= sl; i++)
	{
		if (*(coorX + 0) == *(coorX + i) && *(coorY + 0) == *(coorY + i))
		{
			return true;
		}
		return false;
	}
}

///////////////////////////////////////////////////////////////// Gameplay
void Play(int* coorX, int* coorY) {
	int check = 0;
	Create_Snake(coorX, coorY);
	int xx = *(coorX + 0);
	int yy = *(coorY + 0);
	int Rx = random(15, 90);
	int Ry = random(5, 20);
	while (!Hit_Wall(coorX, coorY) || !Self_Hit(coorX, coorY))
	{
		gotoXY(*(coorX + sl), *(coorY + sl));
		printf(" ");
		gotoXY(Rx, Ry);
		printf(" ");
		Draw_Snake(coorX, coorY);
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && check != 0)
				{
					check = 1;
				}
				else if (c == 80 && check != 1)
				{
					check = 0;
				}
				else if (c == 75 && check != 2)
				{
					check = 3;
				}
				else if (c == 77 && check != 3)
				{
					check = 2;
				}
			}
		}
		if (check == 0)
		{
			(yy++);
		}
		else if (check == 1)
		{
			(yy--);
		}
		else if (check == 2)
		{
			(xx++);
		}
		else if (check == 3)
		{
			(xx--);
		}
		Move(coorX, coorY, xx, yy);
		Draw(Rx, Ry);
		After_Eat(coorX, coorY, &Rx, &Ry);
		Sleep(100);
	}
}

///////////////////////////////////////////////////////////////// Main Function
int main()
{
	int* coorX = (int*)malloc(100 * sizeof(int));
	int* coorY = (int*)malloc(100 * sizeof(int));
	Wall();
	Play(coorX, coorY);
	_getch();
	return 0;
}