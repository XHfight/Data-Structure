/*************************************************************************
	> File Name: UnionFind.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Fri 25 Nov 2016 10:44:45 AM CST
 ************************************************************************/
#pragma once
#include<iostream>
using namespace std;


class UnionFind
{
public:
	UnionFind()
	:_union(NULL)
	{}

	UnionFind(int num)
	:_union(new int[num])
	,_size(num)
	{
		for(int i = 0; i < num; ++i)
		{
			_union[i] = -1;
		}
	}

	~UnionFind()
	{
		if(_union != NULL)
		{
			delete[] _union;
			_union = NULL;
		}
	}

	void Union(size_t x, size_t y)
	{
		x = FindRoot(x);
		y = FindRoot(y);
		if(x != y)
		{
			_union[x] += _union[y];
			_union[y] = x;
		}
	
	}
	size_t FindRoot(size_t x)
	{
		while(_union[x] >= 0)
			x = _union[x];
		return x;
	}

	int CountRoot()
	{
		int count = 0;
		for(int i = 0; i < _size; ++i)
		{
			if(_union[i] < 0)
				++count;
		}
		return count;
	}
protected:
	int* _union;
	size_t _size;
};

