/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Thu 27 Oct 2016 10:30:21 PM CST
 ************************************************************************/

#include<iostream>
#include "RBTree.h"
using namespace std;

void TestRBTree()
{
	int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	RBTree<int, int> t;
	int i = 0;
	int size = sizeof(arr)/sizeof(arr[0]);
	for(int i = 0; i<size; ++i)
	{
		t.Insert(arr[i], i);
	}
	t.InOrder();
	cout << "IsBalance:" << t.IsBalance() << endl;
}
int main()
{
	TestRBTree();
	return 0;
}
