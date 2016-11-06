/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Wed 02 Nov 2016 11:47:00 PM CST
 ************************************************************************/

//#include "HashTable.h"
#include "HashTable_List.h"
 
//void TestHash()
 //{
 //   HashTable<int, int> hs;
 //   int arr[] = {89, 18, 49, 58, 9};
 //   for(size_t i=0; i<sizeof(arr)/sizeof(arr[0]); ++i)
 //   {
 //   	hs.Insert(arr[i], i);
 //   }
 //
 //   cout<<"89?" << hs.Find(89) << endl;
 //   cout<<"58?" << hs.Find(58) << endl;
 //   cout<<"7?" << hs.Find(7) << endl;
 //
 //   hs.Print();
 //   hs.Remove(9);
 //   hs.Print();
 //
 //   HashTable<string, int> hs2;
 //   const char* strs[] = {"hello", "hei", "hello","world"};
 //   for(size_t i=0; i<sizeof(strs)/sizeof(strs[0]); ++i)
 //   {
 //   	string str(strs[i]);
 //   	HashNode<string, int>* ret = hs2.Find(str);
 //   	if(ret)
 //   		++ret->_value;
 //   	else
 //   		hs2.Insert(str, 1);
 //   }
 //   hs2.Print();
 //}

void TestHash_List()
{
	HashTable_List<int , int> hs;
	int arr[] = {89, 18, 49, 58, 9};
	for(size_t i=0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		hs.Insert(arr[i], i);
	}
	hs.Print();
}

int main()
{
	//TestHash();
	TestHash_List();
	return 0;
}
