#pragma once
#include "Helper.h"
#include "Brick.h"
#include "Field.h"
#include "Board.h"
#include "Ball.h"
class GameController
{
public:
	GameController();
	~GameController();
	void Initialize_brick(int);
	void hidecursor();
	void Game();
	bool checkBrick(Cord);
	void move_ball(Direction_ball, Cord);
	bool checkBoard(Cord);
	void load_Game();
	void Logic_Game();
	void show_score();
	void Menu();
	void Score();
	void Exit();
	void setName();
	std::string getName();
	void GAME();
	void Win();
	void show_lives();
private:
	std::string m_name;
	std::vector<Brick> m_bricks;
	Field* m_field;
	Board* m_board;
	Ball* m_ball;
	std::vector<int> destroy_brick;
	Direction_ball ball_check;
	int m_score;
	bool play;
	bool level_complete;
	int level;
	int lives;
	void reset_play();
};

