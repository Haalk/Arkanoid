#pragma once
#include "Helper.h"

class Ball
{
public:
	void show_ball();
	void setCursorPosition(int, int);
	Cord move_ball();
	Direction_ball return_ballDir();
	void set_ballDir(Direction_ball);
	Ball();
	~Ball();
	void Initialize_ball();
	void change(Cord,int);
	void hideBall();
private:
	char ball_symb;
	Direction_ball ball_dir;
	Cord ball_cord;
};

