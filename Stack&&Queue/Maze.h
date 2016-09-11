#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "Stack.h"

using namespace std;

struct Pos
{

	Pos(int row = 0, int col = 0)
	:_row(row)
	, _col(col)
	{}
	int _row;
	int _col;
};

void InitMazeMap(char* map, int row, int col);
void PrintMazeMap(char* map, int row, int col);
bool GetPath(char* map, int row, int col, Pos enter,Stack<Pos>& path);
bool IsExport(const Pos& pos, int row, int col);
bool IsAccess(const Pos& pos, char* map, int row, int col);
void GetSize(int* prow, int* pcol);
