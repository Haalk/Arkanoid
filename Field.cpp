#include "Field.h"

#include <algorithm>
#include <iomanip>
using namespace std;


Field::Field()
{
	my_field.resize(SIZE_HEIGHT);
	for (int i=0; i < SIZE_HEIGHT; ++i)
		my_field[i].resize(SIZE_WIDTH);

	m_scores.resize(SIZE_SCORES);
	std::ifstream fin;
	fin.open(File_name);
	if (!fin.is_open())
	{
		std::ofstream fout;
		fout.open(File_name);
		fout.close();
	}
	std::string temp;
	int temp_val;
	int i = 0;
	while (i != SIZE_SCORES)
	{
		if (fin >> temp)
			fin >> temp_val;
		else
		{
			temp = "noname";
			temp_val = 0;
		}
		m_scores[i].first = temp;
		m_scores[i++].second = temp_val;
	}
	fin.close();
}

Field::~Field()
{
}

void Field::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Field::drawField()
{
	for (int i = 0; i < SIZE_WIDTH; ++i)
	{
		for (int j = 0; j < SIZE_HEIGHT; ++j)
		{
			if (i == 0 || i == SIZE_WIDTH-1 || j == 0 || j == SIZE_HEIGHT-1)
			{
				setCursorPosition(i, j);
				std::cout << '#';
			}
		}
	}
}

char Field::get_symb(int x, int y)
{
	return my_field[x][y];
}

void Field::score_table()
{
	std::ifstream fin;
	fin.open(File_name);
	std::string temp;
	int temp_val;
	int i = 0;
	while (i != SIZE_SCORES)
	{
		if (fin >> temp)
			fin >> temp_val;
		else
		{
			temp = "noname";
			temp_val = 0;
		}
		m_scores[i].first = temp;
		m_scores[i++].second = temp_val;
	}
	system("cls");
	std::cout << "\n\t\t\tSCORE" << std::endl;
	for (int i = 0; i <SIZE_SCORES; ++i)
		std::cout << '\t' << m_scores[i].first << std::setw(40 - m_scores[i].first.size()) << m_scores[i].second << std::endl;
	fin.close();
	_getch();
	_getch();
}

void Field::set_record(const std::string & name, int score)
{
	std::pair<std::string, int> temp_pair;
	temp_pair.first = name;
	temp_pair.second = score;
	m_scores.push_back(temp_pair);
	rewrite_table();
}

void Field::rewrite_table()
{
	sort(m_scores.begin(), m_scores.end(), [](const std::pair<std::string, int>&a, const std::pair<std::string, int>&b)
	{
		if (a.second == b.second)
			return a.first > b.first;
		return a.second > b.second;
	});
	std::ofstream fout(File_name);
	for (int i = 0; i < SIZE_SCORES; ++i)
		fout << m_scores[i].first << " " << m_scores[i].second << std::endl;
	fout.close();
}

bool Field::beat_record(int record)
{
	bool beat = false;
	for (int i = 0; i < SIZE_SCORES; ++i)
	{
		if (record > m_scores[i].second)
			return true;
	}
	return false;
}