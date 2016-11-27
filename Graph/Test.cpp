/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sat 26 Nov 2016 08:42:45 PM CST
 ************************************************************************/

#include "Graph.h"
#include<iostream>
#include<string>
using namespace std;

void TestGraphMatrix()
{
	string v[] = {"AAA", "BBB", "CCC", "DDD", "EEE"};
	GraphMatrix<string, int> gm(v, sizeof(v)/sizeof(v[0]));
	gm.InsertArc("AAA", "DDD", 10);
	gm.InsertArc("AAA", "EEE", 20);
	gm.InsertArc("DDD", "BBB", 20);
	gm.InsertArc("BBB", "CCC", 10);
	gm.InsertArc("BBB", "EEE", 30);
	gm.InsertArc("EEE", "CCC", 40);
	gm.Print();
}

void TestGraphList()
{
	string v[] = {"AAA", "BBB", "CCC", "DDD", "EEE"};
	GraphList<string, int> gm(v, sizeof(v)/sizeof(v[0]));
	gm.InsertArc("AAA", "DDD", 10);
	gm.InsertArc("AAA", "EEE", 20);
	gm.InsertArc("DDD", "BBB", 20);
	gm.InsertArc("BBB", "CCC", 10);
	gm.InsertArc("BBB", "EEE", 30);
	gm.InsertArc("EEE", "CCC", 40);
	gm.Print();
	gm.BFSTraverse("AAA");
	gm.DFSTraverse("AAA");
}
int main()
{
//	TestGraphMatrix();
	TestGraphList();
	return 0;
}
