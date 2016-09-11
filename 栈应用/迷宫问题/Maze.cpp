#include "Maze.h"
#include <cassert>

void InitMazeMap(char* map, int row, int col)
{
	FILE* f1 = fopen("MazeMap.txt", "r");
	assert(f1);
	//跳过第一行
	int ch = fgetc(f1);
	while (ch != '\n')
	{
		ch = fgetc(f1);
	}

	//开始读取迷宫地图
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col;)
		{
			ch = fgetc(f1);
			if (ch == '0' || ch == '1')
			{
				map[i*col + j] = ch;
				++j;
			}
		}
	}
	fclose(f1);
}


void PrintMazeMap(char* map, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << map[i*col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

bool GetPath(char* map, int row, int col, Pos enter, Stack<Pos>& path)
{
	map[enter._row*col + enter._col] = '2';
	path.Push(enter);

	while (!path.Empty())
	{
		Pos cur = path.Top();
		if (cur._col!= enter._col && cur._row!=enter._row && IsExport(cur,row,col))
		{
			return true;
		}
		//上
		Pos next = cur;
		next._row -= 1;
		if (IsAccess(next,map,row,col))
		{
			map[next._row*col + next._col] = '2';

			path.Push(next);
			continue;
		}

		//右
		next = cur;
		next._col += 1;
		if (IsAccess(next, map, row, col))
		{
			map[next._row*col + next._col] = '2';

			path.Push(next);
			continue;
		}

		//下
		next = cur;
		next._row += 1;
		if (IsAccess(next, map, row, col))
		{
			map[next._row*col + next._col] = '2';

			path.Push(next);
			continue;
		}
		//左
		next = cur;
		next._col -= 1;
		if (IsAccess(next, map, row, col))
		{
			map[next._row*col + next._col] = '2';

			path.Push(next);
			continue;
		}
		map[cur._row*col + cur._col] = '3';
		path.Pop();
	}
	return false;
}

bool IsAccess(const Pos& pos, char* map, int row, int col)
{
	if (pos._row >= 0 && pos._row < row
		&&pos._col >= 0 && pos._col < col
		&&map[pos._row*col + pos._col] == '0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsExport(const Pos& pos, int row ,int col)
{
	if (pos._col == 0 || pos._row == 0 || pos._col == (col - 1) || pos._row == (row - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GetSize(int* prow, int* pcol)
{
	FILE* f = fopen("MazeMap.txt", "r");
	assert(f);
	int ch = fgetc(f);

	while (ch != '\n' && (ch <= '0' || ch >= '9'))//跳过非数字字符
	{
		ch = fgetc(f);
	}
	while (ch >= '0'&&ch <= '9') //row
	{
		*prow = *prow * 10 + (ch - '0');
		ch = fgetc(f);
	}
	while (ch != '\n'&& (ch<='0' || ch>='9'))
	{
		ch = fgetc(f);
	}
	while (ch >= '0' && ch <= '9')//col
	{
		*pcol = *pcol * 10 + (ch - '0');
		ch = fgetc(f);
	}
	fclose(f);
}
