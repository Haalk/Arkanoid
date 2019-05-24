#include "Brick.h"

Brick::Brick(Cord cord,char numb,int value)
{
	for (int i = 0; i < value; ++i)
	{
		brick_cord[i].x = cord.x++;
		brick_cord[i].y = cord.y;
	}
	switch (numb)
	{
	case '1':brick_health = 1; brick_color = 14; break;
	case '2':brick_health = 2; brick_color = 12; break;
	case '3':brick_health = 3; brick_color = 4; break;
	case '4':brick_health = 4; brick_color = 2; break;
	case '5':brick_health = 5; brick_color = 1; break;
	}
}

Brick::Brick()
{
}


Brick::~Brick()
{
}

Cord Brick::return_brickCord()
{
	return brick_cord[0];
}

void Brick::show_brick()
{
	for (int i = 0; i < SIZE_BRICK; ++i)
	{
		setCursorPosition(brick_cord[i].x, brick_cord[i].y);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, brick_color);
		std::cout << (char)177;
		SetConsoleTextAttribute(hConsole, 15);
	}
}

void Brick::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Brick::Destroy_brick()
{
	for (int i = 0; i < SIZE_BRICK; ++i)
	{
		setCursorPosition(brick_cord[i].x, brick_cord[i].y);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, brick_color);
		std::cout << ' ';
		SetConsoleTextAttribute(hConsole, 15);
	}
}

bool Brick::minus_health()
{
	brick_health--;
	switch (brick_health)
	{
	case 4:brick_color = 2; break;
	case 3:brick_color = 4; break;
	case 2:brick_color = 12; break;
	case 1:brick_color = 14; break;
	}
	if(brick_health>0)
		return true;
	return false;
}
