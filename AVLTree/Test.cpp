/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 23 Oct 2016 05:09:51 PM CST
 ************************************************************************/

#include<iostream>
#include"AVLTree.h"
using namespace std;

//测试用例一
void TestAVLTree1()
{
	int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	AVLTree<int, int> t1;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		t1.Insert(arr[i], i);
	}
	t1.InOrder();
	cout<<"IsBalance() ? "<<t1.IsBalance()<<endl;
}

//测试用例二
void TestAVLTree2()
{
	int arr[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int, int> t2;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		t2.Insert(arr[i], i);
	}
	t2.InOrder();
	cout<<"IsBalance() ? "<<t2.IsBalance()<<endl;
}

int main()
{
	TestAVLTree1();
	cout << endl;
	TestAVLTree2();
	return 0;
}
