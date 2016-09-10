#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

struct Pos
{
	Pos()
	{}

	Pos(int row, int col)
	:_row(row)
	, _col(col)
	{}
	int _row;
	int _col;
};

void InitMazeMap(char* map, int row, int col);
void PrintMazeMap(char* map, int row, int col);
bool GetPath(char* map, int row, int col, Pos enter);
bool IsExport(const Pos& pos, int row, int col);
bool IsAccess(const Pos& pos, char* map, int row, int col);
