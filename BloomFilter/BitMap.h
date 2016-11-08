/*************************************************************************
	> File Name: BitMap.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 06 Nov 2016 04:40:58 PM CST
 ************************************************************************/

#pragma once
#include<vector>
#include<iostream>
using namespace std;

class BitMap
{
public:
	BitMap(size_t range)	
	{
		_map.resize(range>>3+1);
	}
	void Set(size_t data) //对应位置1
	{
		size_t index = data >> 3; //第几个数
		size_t bit = data % 8; //第几位
		_map[index] |= ( 1 << bit);
	}
	void Reset(size_t data)
	{
		size_t index = data >> 3;
		size_t bit = data % 8;
		_map[index] &= (~(1 << bit));
	}
	bool Test(size_t data)
	{
		size_t index = data >> 3;
		size_t bit = data % 8;
		return (_map[index]&(1<<bit));
	}
protected:
	vector<char> _map;
};
