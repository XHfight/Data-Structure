/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Mon 17 Oct 2016 11:12:12 PM CST
 ************************************************************************/
#include "SearchBinaryTree.h"
#include <iostream>
using namespace std;


void TestSearchBinaryTree()
{
	int arr[] = {5, 3, 4, 1, 7, 8, 2, 6, 0, 9};
	SearchBinaryTree<int> h1;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		h1.Insert(arr[i]);
	}
	h1.InOrder();
	SearchBinaryTree<int> h2(h1);
	h2.InOrder();

	h1.Remove(5);
	h1.InOrder();
	h1.Remove(9);
	h1.InOrder();

}
int main()
{
	TestSearchBinaryTree();
	return 0;
}
