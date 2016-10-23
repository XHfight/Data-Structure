/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 23 Oct 2016 05:09:51 PM CST
 ************************************************************************/

#include<iostream>
#include"AVLTree.h"
using namespace std;

void TestAVLTree()
{
	int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	AVLTree<int, int> t;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		t.Insert(arr[i], i);
	}
	t.InOrder();
}

int main()
{
	TestAVLTree();
	return 0;
}
