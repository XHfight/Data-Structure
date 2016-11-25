/*************************************************************************
	> File Name: FrindCircle.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Fri 25 Nov 2016 11:21:58 AM CST
 ************************************************************************/

#include<iostream>
#include "UnionFind.h"
using namespace std;
//小米笔试题：朋友圈问题

int friends(int n, int m, int r[][2])
{
	UnionFind friendCircle(n+1);
	for(int i = 0; i < m; ++i)
	{
		friendCircle.Union(r[i][0], r[i][1]);
	}
	return friendCircle.CountRoot()-1;
}
int main()
{
	int n = 5;
	int m = 5;
	
	int r[][2] = {{1, 2}, {2, 3}, {4, 5}, {1, 3}, {3, 4}};
	cout << friends(n, m, r) << endl;
	
	return 0;
}

