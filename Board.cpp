#include "Board.h"



Board::Board()
{	
}


Board::~Board()
{
}

bool Board::move_board()
{
	if (_kbhit())
	{
		int key = _getch();
		switch (key)
		{
		case Direction_board::RIGHT:
			{
			if (board_cord[SIZE_BOARD - 1].x < SIZE_WIDTH-2)
				{
					for (int i = 0; i < SIZE_BOARD; ++i)
						{
							setCursorPosition(board_cord[i].x, board_cord[i].y);
							cout << ' ';
							board_cord[i].x++;
						}
					board_dir = Direction_board::RIGHT;
					show_board();
				}
			};
			break;
		case Direction_board::LEFT:
			if (board_cord[0].x > 1)
			{
				for (int i = 0; i < SIZE_BOARD; ++i)
				{
					setCursorPosition(board_cord[i].x, board_cord[i].y);
					cout << ' ';
					board_cord[i].x--;
				}
				board_dir = Direction_board::LEFT;
				show_board();
			}
			break;
		case Direction_board::SPACE:
			{
			check_stop = true;
			return false;
			}
		}
		return true;
	}
}

void Board::show_board()
{
	for (int i = 0; i < SIZE_BOARD; ++i)
	{
		if (i == SIZE_BOARD / 2)
		{
			setCursorPosition(board_cord[i].x, board_cord[i].y);
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 5);
			std::cout << (char)177;
			SetConsoleTextAttribute(hConsole, 15);
		}
		else 
		{
			setCursorPosition(board_cord[i].x, board_cord[i].y);
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, board_color);
			std::cout << (char)177;
			SetConsoleTextAttribute(hConsole, 15);
		}
	}
}

void Board::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

Cord Board::return_boardCord()
{
	return board_cord[0];
}

void Board::Initialize_board()
{
	check_stop = false;
	int x = SIZE_WIDTH / 2 - 4;
	int y = SIZE_HEIGHT - 3;
	for (int i = 0; i < SIZE_BOARD; ++i)
	{
		board_cord[i].x = x++;
		board_cord[i].y = y;
	}
	board_color = 10;
}

Direction_board Board::get_boardDir()
{
	return board_dir;
}

bool Board::getSTOP()
{
	return check_stop;
}

void Board::setSTOP(bool stop)
{
	check_stop = stop;
}

void Board::hideBoard()
{
	for (int i = 0; i < SIZE_BOARD; ++i)
	{
			setCursorPosition(board_cord[i].x, board_cord[i].y);
			std::cout << ' ';
	}
}
