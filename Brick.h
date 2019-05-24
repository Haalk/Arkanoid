#pragma once
#include "Helper.h"
class Brick
{
public:
	Brick(Cord,char,int);
	Brick();
	~Brick();
	Cord return_brickCord();
	void show_brick();
	void setCursorPosition(int, int);
	void Destroy_brick();
	bool minus_health();
private:
	Cord brick_cord[SIZE_BRICK];
	int brick_health;
	int brick_color;
	std::vector<int> colors;
};

