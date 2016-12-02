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
	GraphList<string, int> gl(v, sizeof(v)/sizeof(v[0]));
	gl.InsertArc("AAA", "DDD", 10);
	gl.InsertArc("AAA", "EEE", 20);
	gl.InsertArc("DDD", "BBB", 20);
	gl.InsertArc("BBB", "CCC", 10);
	gl.InsertArc("BBB", "EEE", 30);
	gl.InsertArc("EEE", "CCC", 40);
	gl.Print();
	gl.BFSTraverse("AAA");
	gl.DFSTraverse("AAA");
}

void TestMinTree()
{
	int v[] = {0, 1, 2, 3, 4, 5, 6};
	GraphList<int, int> gl(v, sizeof(v)/sizeof(v[0]));
	gl.InsertArc(0, 1, 28);
	gl.InsertArc(1, 2, 16);
	gl.InsertArc(1, 6, 14);
	gl.InsertArc(2, 3, 12);
	gl.InsertArc(3, 4, 22);
	gl.InsertArc(3, 6, 18);
	gl.InsertArc(4, 6, 24);
	gl.InsertArc(4, 5, 25);
	gl.InsertArc(5, 0, 10);
	gl.Print();

	GraphList<int, int> minTree;
	gl.Kruskal(minTree);
	minTree.Print();
}
int main()
{
//	TestGraphMatrix();
//	TestGraphList();
	TestMinTree();
	return 0;
}
