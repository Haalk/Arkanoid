#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

const int SIZE_HEIGHT_BRICKS = 11;
const int SIZE_HEIGHT = 28;
const int SIZE_WIDTH = 62;
const int SIZE_BRICK = 4;
const int SIZE_BOARD = 7;
const int level_num = 5;
const int size_levelName = 11;
const int Health = 3;

const char File_name[] = "records.txt";

const char levels[level_num][size_levelName] = { "level1.txt" , "level2.txt" , "level3.txt", "level4.txt", "level5.txt" };

const int SIZE_SCORES = 15;

enum Direction_board{RIGHT=77,LEFT=75,SPACE=32};

enum Direction_ball{STOP=0,NW=1,NE=2,SW=3,SE=4,UP=5,DOWN=6};

struct Cord
{
	int x;
	int y;
};
