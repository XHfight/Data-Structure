/*************************************************************************
	> File Name: Test.c
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Thu 22 Sep 2016 01:07:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include "TransposeMatrix.h"

void TestTranspose()
{
	int arr[6][5] =
			  {{1, 0, 3, 0, 5},
			   {0, 0, 0, 0, 0},
			   {0, 0, 0, 0, 0},
			   {1, 0, 3, 0, 5},
			   {0, 0, 0, 0, 0},
			   {0, 0, 0, 0, 0}};
	Matrix<int> m((int*)arr,6,5);
	m.Print();
	m.Transpose();
	m.Print();
}
int main()
{
	TestTranspose();
	return 0;
}
