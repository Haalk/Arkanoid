#pragma once
#include "Brick.h"
#include "Helper.h"
//class Board : public Brick


class Board
{
public:
Board();
~Board();
bool move_board();
void show_board();
void setCursorPosition(int, int);
Cord return_boardCord();
void Initialize_board();
Direction_board get_boardDir();
bool getSTOP();
void setSTOP(bool);
void hideBoard();
private:
	Cord board_cord[SIZE_BOARD];
	int board_color;
	Direction_board board_dir;
	bool check_stop;
};
