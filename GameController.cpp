#include "GameController.h"

GameController::GameController()
{
	m_field = new Field;
	m_board = new Board;
	m_ball = new Ball;
	hidecursor();
	play = true;
	level_complete = false;
	level = 0;
	lives = Health;
}

GameController::~GameController()
{
	delete m_field;
	delete m_board;
	delete m_ball;
}

void GameController::Initialize_brick(int lvl)
{
	m_bricks.clear();
	std::ifstream fin(levels[level]);  
	char brick_color;
	int count_bricks = 0;
	char temp_brick_color;
	int x = 0;
	int y = 0;
	Cord temp;
	while (!fin.eof())
	{
		fin.get(temp_brick_color);
		if (temp_brick_color > '0' && temp_brick_color < '6')
		{
			temp = { x,y };
			brick_color = temp_brick_color;
			count_bricks++;
			m_bricks.push_back(Brick{ temp, brick_color, SIZE_BRICK });	
			m_bricks[count_bricks-1].show_brick();
			x += 4;
			fin.get(temp_brick_color);
			fin.get(temp_brick_color);
			fin.get(temp_brick_color);
		}
		else
			x++;
		if (x >= SIZE_WIDTH+1)
		{
			y++;
			x = 0;
		}
	}
	/*for (int i = 0; i < count_bricks; ++i)
		m_bricks[i].show_brick();*/
}

void GameController::hidecursor()
{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(consoleHandle, &info);
}

void GameController::Game()
{
	while (play)
	{
		level_complete = false;
		load_Game();
		Logic_Game();
	}
	if (m_field->beat_record(m_score))
	{
		setName();
		m_field->set_record(getName(), m_score);
	}
	else
		_getch();
}

bool GameController::checkBrick(Cord cd)
{
	Direction_ball temp_dir = m_ball->return_ballDir();
	Cord temp = m_board->return_boardCord();
	for (int i = 0; i < SIZE_BOARD; ++i)
	{
		if (temp.x++ == cd.x && temp.y == cd.y)
			return true;
	}

	for (int i = 0; i < destroy_brick.size(); ++i)
	{
		temp = m_bricks[destroy_brick[i]].return_brickCord();
		for (int j = 0; j < SIZE_BRICK; ++j)
		{
			if (temp.x++ == cd.x && temp.y == cd.y)
				return false;
		}
	}

	for (int i = 0; i < m_bricks.size(); ++i)
	{
		temp = m_bricks[i].return_brickCord();
		for (int j = 0; j < SIZE_BRICK; ++j)
		{
			if (temp.x++ == cd.x && temp.y == cd.y)
				return true;
		}
	}
	return false;
}

void GameController::move_ball(Direction_ball temp_ballDir,Cord temp_ballCord)
{
	if (temp_ballDir == Direction_ball::NW)
	{
		if (temp_ballCord.x == 1)
			m_ball->set_ballDir(Direction_ball::NE);
		if (temp_ballCord.y == 1)
		{
			m_ball->set_ballDir(Direction_ball::SW);
			return;
		}
		if (checkBrick(Cord{ temp_ballCord.x - 1,temp_ballCord.y - 1 }))
		{
			m_ball->set_ballDir(Direction_ball::SW);
			Cord temp;
			for (int i = 0; i < m_bricks.size();++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x - 1 == temp.x++ && temp_ballCord.y - 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick();
							m_score += 10;
						}
						m_score += 10;
						i = m_bricks.size();
					}
				}
				
			}
		}
	}
	else if (temp_ballDir == Direction_ball::NE)
	{
		if (temp_ballCord.x == SIZE_WIDTH - 2)
			m_ball->set_ballDir(Direction_ball::NW);
		if (temp_ballCord.y == 1)
		{
			m_ball->set_ballDir(Direction_ball::SE);
			return;
		}
		if (checkBrick(Cord{ temp_ballCord.x + 1,temp_ballCord.y - 1 }))
		{
			m_ball->set_ballDir(Direction_ball::SE);
			Cord temp;
			for (int i = 0; i < m_bricks.size(); ++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x + 1 == temp.x++ && temp_ballCord.y - 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick();
							m_score += 10;
						}
						m_score += 10;
						i = m_bricks.size();
					}
				}
			}
		}
	}
	else if (temp_ballDir == Direction_ball::SW)
	{
		if (temp_ballCord.x == 1)
			m_ball->set_ballDir(Direction_ball::SE);
		if (checkBrick(Cord{ temp_ballCord.x - 1,temp_ballCord.y + 1 }))
		{
			if (checkBoard(Cord{ temp_ballCord.x,temp_ballCord.y + 1 }))
				m_ball->set_ballDir(ball_check);
			else
				m_ball->set_ballDir(Direction_ball::NW);
			
			Cord temp;
			for (int i = 0; i < m_bricks.size(); ++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x - 1 == temp.x++ && temp_ballCord.y + 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick();
							m_score += 10;
						}
						i = m_bricks.size();
						m_score += 10;
					}
				}
			}
		}
	}
	else if (temp_ballDir == Direction_ball::SE)
	{
		if (temp_ballCord.x == SIZE_WIDTH - 2)
			m_ball->set_ballDir(Direction_ball::SW);
		if (checkBrick(Cord{ temp_ballCord.x + 1,temp_ballCord.y + 1 }))
		{
			
			if (checkBoard(Cord{ temp_ballCord.x,temp_ballCord.y + 1 }))
				m_ball->set_ballDir(ball_check);
			else
				m_ball->set_ballDir(Direction_ball::NE);
			Cord temp;
			for (int i = 0; i < m_bricks.size(); ++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x + 1 == temp.x++ && temp_ballCord.y + 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick();
							m_score += 10;
						}
						m_score += 10;
						i = m_bricks.size();
					}
				}
			}
		}
	}
	else if (temp_ballDir == Direction_ball::UP)
	{
		if (temp_ballCord.y == 1)
		{
			m_ball->set_ballDir(Direction_ball::DOWN);
			return;
		}
		if (checkBrick(Cord{ temp_ballCord.x,temp_ballCord.y - 1 }))
		{
			if (checkBoard(Cord{ temp_ballCord.x,temp_ballCord.y - 1 }))
				m_ball->set_ballDir(ball_check);
			else
				m_ball->set_ballDir(Direction_ball::DOWN);
			Cord temp;
			for (int i = 0; i < m_bricks.size(); ++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x== temp.x++ && temp_ballCord.y - 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick(); 
							m_score += 10;
						}
						m_score += 10;
						i = m_bricks.size();
					}
				}
			}
		}
	}
	else if (temp_ballDir == Direction_ball::DOWN)
	{

		if (checkBrick(Cord{ temp_ballCord.x,temp_ballCord.y + 1 }))
		{
			if (checkBoard(Cord{ temp_ballCord.x,temp_ballCord.y + 1 }))
				m_ball->set_ballDir(ball_check);
			else
				m_ball->set_ballDir(Direction_ball::UP);
			Cord temp;
			for (int i = 0; i < m_bricks.size(); ++i)
			{
				temp = m_bricks[i].return_brickCord();
				for (int j = 0; j < SIZE_BRICK; ++j)
				{
					if (temp_ballCord.x == temp.x++ && temp_ballCord.y + 1 == temp.y)
					{
						if (m_bricks[i].minus_health())
							m_bricks[i].show_brick();
						else
						{
							destroy_brick.push_back(i);
							m_bricks[i].Destroy_brick();
							m_score += 10;
						}
						m_score += 10;
						i = m_bricks.size();
					}
				}
			}
		}
	}
	if (temp_ballCord.y > SIZE_HEIGHT - 3)
	{
		_getch();
		if(!lives--)
			play = false;
		else
		{
			m_board->hideBoard();
			m_ball->hideBall();
			m_board->Initialize_board();
			m_ball->Initialize_ball();
			m_board->show_board();
			m_ball->show_ball();
			show_lives();
		}
	}
}

bool GameController::checkBoard(Cord cd)
{
	Direction_ball temp_dir = m_ball->return_ballDir();
	Cord temp = m_board->return_boardCord();

	for (int i = 0; i < SIZE_BOARD; ++i)
	{
		if (temp.x == cd.x && temp.y == cd.y)
		{
			if (i == SIZE_BOARD / 2)
				ball_check = Direction_ball::STOP;
			else
			{
				if (i < SIZE_BOARD / 2)
					ball_check = Direction_ball::NW;
				else if (i > SIZE_BOARD / 2)
					ball_check = Direction_ball::NE;
			}
			return true;
		}
		temp.x++;
	}
	return false;
}

void GameController::load_Game()
{
	if (level == level_num)
	{
		Win();
		return;
	}
	system("cls");
	m_field->drawField();
	m_board->Initialize_board();
	Initialize_brick(level);
	
	m_ball->Initialize_ball();
	m_board->show_board();
	m_ball->show_ball();
	show_score();
	show_lives();
	_getch();
	int key = _getch();
	if (key == Direction_board::LEFT)
		m_ball->set_ballDir(Direction_ball::NW);
	else
		m_ball->set_ballDir(Direction_ball::NE);
}

void GameController::Logic_Game()
{
	Direction_ball temp_ballDir = m_ball->return_ballDir();
	Cord temp_ballCord = m_ball->move_ball();
	int count_board = 0;
	bool isGame = true;
	int reset_cord=lives;
	while (!level_complete && play)
	{
		int count_moveball = 0;
		if (m_ball->return_ballDir() == Direction_ball::STOP)
		{
			while (!m_board->getSTOP())
			{
				if (m_board->move_board())
				{
					if (count_moveball == 0)
					{
						count_moveball++;
						Cord temp = m_board->return_boardCord();
						if (m_board->get_boardDir() == Direction_board::LEFT && temp.x > 1)
						{
							m_ball->hideBall();
							m_ball->change(m_board->return_boardCord(), -1);
						}
						else if (m_board->get_boardDir() == Direction_board::RIGHT && temp.x < SIZE_WIDTH)
						{
							m_ball->hideBall();
							m_ball->change(m_board->return_boardCord(), 1);
						}
						m_ball->move_ball();
					}
					else if (count_moveball == 1)
						count_moveball = 0;
				}		
			}
			m_ball->set_ballDir(Direction_ball::UP);
			m_board->setSTOP(false);
			continue;
		}
		else
		{	
			move_ball(temp_ballDir, temp_ballCord);
			if (lives < reset_cord)
			{
				reset_cord = lives;
				m_ball->set_ballDir(Direction_ball::STOP);
				temp_ballCord = m_ball->move_ball();
			}
			m_board->move_board();
			if (count_board == 50)
			{
				temp_ballCord = m_ball->move_ball();
				count_board = 0;
			}
			count_board++;
			temp_ballDir = m_ball->return_ballDir();
			show_score();
			
			if (destroy_brick.size() == m_bricks.size())
			{
				if (level < level_num)
					level++;
				level_complete = true;
			}
		}
	}
}

void GameController::show_score()
{
	m_field->setCursorPosition(0, SIZE_HEIGHT);
	cout << "SCORE: " << m_score;
}

void GameController::Menu()
{
	int key='1';
	while (key <= '3' && key >='1') 
	{
		system("cls");
		cout << "1.Play" << endl;
		cout << "2.Score" << endl;
		cout << "3.Exit" << endl;
		key = _getch();
		switch (key)
		{
		case '1':_getch(); reset_play(); Game(); break;
		case '2':_getch(); Score(); break;
		case '3':Exit();
		}
	}
}

void GameController::Score()
{
	m_field->score_table();
}

void GameController::Exit()
{
	system("cls");
	m_field->setCursorPosition(15, 10);
	cout << "Bye";
	_getch();
	exit(1);
}

void GameController::setName()
{
	m_field->setCursorPosition(10, 10);
	cout << "Enter your name: ";
	cin >> m_name;
}

std::string GameController::getName()
{
	return m_name;
}

void GameController::GAME()
{
	while (play)
	{
		Menu();
	}
	_getch();
}

void GameController::Win()
{
	system("cls");
	m_field->setCursorPosition(SIZE_WIDTH/2 - 5,SIZE_HEIGHT / 2);
	cout << "CONGRATULATION! You WIN!" << endl;
	m_field->setCursorPosition(SIZE_WIDTH / 2 - 5, SIZE_HEIGHT / 2+1);
	cout << "Your score: " << m_score;
	play = false;
	_getch();
	return;
}

void GameController::show_lives()
{
	m_field->setCursorPosition(strlen("SCORE:  ")+15, SIZE_HEIGHT);
	cout << "LIVES: ";
	for (int i = 0; i < Health; ++i)
	{
		m_field->setCursorPosition(strlen("SCORE:  ") + 23+i, SIZE_HEIGHT);
		cout << "  ";
	}
	for (int i = 0; i < lives; ++i)
	{
		m_field->setCursorPosition(strlen("SCORE:  ") + 23 + i, SIZE_HEIGHT);
		cout << "X ";
	}
}

void GameController::reset_play()
{
	play = true;
	level_complete = false;
	lives = Health;
	m_score = 0;
	destroy_brick.clear();
}
