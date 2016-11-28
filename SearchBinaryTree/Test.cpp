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
	SearchBinaryTree<int, int> h1;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		h1.Insert(arr[i]);
	}
	h1.InOrder();
	SearchBinaryTree<int, int> h2(h1);
	h2.InOrder();

	h1.Remove(5);
	h1.InOrder();

	h1.Remove(1);
	h1.Remove(2);
	h1.Remove(3);
	h1.Remove(4);
	h1.Remove(5);
	h1.Remove(6);
	h1.Remove(7);
	h1.Remove(8);
	h1.Remove(9);
	h1.Remove(0);
	h1.InOrder();
}
void TestSearchBinaryTreeR()
{
	int arr[] = {5, 3, 4, 1, 7, 8, 2, 6, 0, 9};
	SearchBinaryTree<int, int> h1;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		h1.InsertR(arr[i]);
	}
	h1.InOrder();

	h1.RemoveR(5);
	h1.InOrder();

	h1.RemoveR(1);
	h1.RemoveR(2);
	h1.RemoveR(3);
	h1.RemoveR(4);
	h1.RemoveR(5);
	h1.RemoveR(6);
	h1.RemoveR(7);
	h1.RemoveR(8);
	h1.RemoveR(9);
	h1.RemoveR(0);
	h1.InOrder();

}

void TestToOrderedDoubleList()
{
	int arr[] = {5, 3, 4, 1, 7, 8, 2, 6, 0, 9};
	SearchBinaryTree<int, int> h1;
	for(int i = 0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		h1.InsertR(arr[i]);
	}

	SearchBinaryTreeNode<int, int>* cur = h1.ToOrderedDoubleList();
	SearchBinaryTreeNode<int, int>* last = NULL;
	//正向遍历
	while(cur)
	{
		cout << cur->_key << " ";
		last = cur;
		cur = cur->_right;
	}
	cout << endl;

	//反向遍历
	while(last)
	{
		cout << last->_key << " ";
		last = last->_left;
	}
	cout << endl;
}
int main()
{
	//TestSearchBinaryTree();
	//TestSearchBinaryTreeR();
	TestToOrderedDoubleList();
	return 0;
}
