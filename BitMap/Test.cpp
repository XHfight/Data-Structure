/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 06 Nov 2016 09:11:07 PM CST
 ************************************************************************/

#include"BitMap.h"
#include<iostream>
using namespace std;

void TestBitMap()
{
	BitMap m1((size_t)-1); //传过去为size_t的最大值
	m1.Set(10);
	m1.Set(110);

	cout << "10 ? :" << m1.Test(10) << endl;
	cout << "110 ? :" << m1.Test(110) << endl;
	cout << "111 ? :" << m1.Test(111) << endl;
	m1.Reset(110);
	cout << "110 ? :" << m1.Test(110) << endl;
}
int main()
{
	TestBitMap();
	return 0;
}
