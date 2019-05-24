#include "Ball.h"

void Ball::show_ball()
{
	setCursorPosition(ball_cord.x, ball_cord.y);
	cout << ball_symb;
}

void Ball::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

Cord Ball::move_ball()
{
	setCursorPosition(ball_cord.x, ball_cord.y);
	cout << ' ';
	if (ball_dir == Direction_ball::NW)
	{
		--ball_cord.x;
		--ball_cord.y;
	}
	else if (ball_dir == Direction_ball::NE)
	{
		++ball_cord.x;
		--ball_cord.y;
	}
	else if (ball_dir == Direction_ball::SW)
	{
		--ball_cord.x;
		++ball_cord.y;
	}
	else if (ball_dir == Direction_ball::SE)
	{
		++ball_cord.x;
		++ball_cord.y;
	}
	else if (ball_dir == Direction_ball::UP)
		--ball_cord.y;
	else if (ball_dir == Direction_ball::DOWN)
		++ball_cord.y;
	
	show_ball();
	Sleep(70);
	return ball_cord;
}

Direction_ball Ball::return_ballDir()
{
	return ball_dir;
}

void Ball::set_ballDir(Direction_ball dir)
{
	ball_dir = dir;
}

Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::Initialize_ball()
{
	ball_cord.x = SIZE_WIDTH / 2 - 1;
	ball_cord.y = SIZE_HEIGHT - 4;
	ball_symb = 'O';
	ball_dir = Direction_ball::NW;
}

void Ball::change(Cord xy,int dir)
{
	ball_cord.x = xy.x + SIZE_BOARD / 2+dir;
}

void Ball::hideBall()
{
	setCursorPosition(ball_cord.x, ball_cord.y);
	cout << ' ';
}
