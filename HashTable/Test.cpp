/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Wed 02 Nov 2016 11:47:00 PM CST
 ************************************************************************/

#include "HashTable.h"
#include<iostream>
using namespace std;

void TestHash()
{
	HashTable<int, int> hs;
	int arr[] = {89, 18, 49, 58, 9};
	for(size_t i=0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		hs.Insert(arr[i], i);
	}

	cout<<"89?" << hs.Find(89) << endl;
	cout<<"58?" << hs.Find(58) << endl;
	cout<<"7?" << hs.Find(7) << endl;
}
int main()
{
	TestHash();
	return 0;
}
