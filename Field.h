#pragma once
#include "Helper.h"
#include "Brick.h"
#include <utility>
class Field
{
public:
	Field();
	~Field();
	void setCursorPosition(int,int);
	void drawField();
	void score_table();
	void set_record(const std::string &, int);
	bool beat_record(int record);
	char get_symb(int, int);
private:
	std::vector<Cord> m_field;
	std::vector<Brick> bricks;
	std::vector<std::vector<char>> my_field;
	std::vector<std::pair<std::string, int>> m_scores;
	void rewrite_table();
};

