/*************************************************************************
	> File Name: Test.cpp
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Tue 08 Nov 2016 10:30:28 AM CST
 ************************************************************************/
#include"BloomFilter.h"
#include<iostream>
using namespace std;

void TestBloomFilter()
{
	BloomFilter<string> b1(100);
	string s1 = "http://www.cnblogs.com/haippy/archive/2012/07/13/2590351.html";
	string s2 = "http://www.cnblogs.com/haippy/archive/2012/07/13/2590352.html";
	string s3 = "http://www.cnblogs.com/haippy/archive/2012/07/13/2590353.html";
	b1.Set(s1);
	b1.Set(s2);
	b1.Set(s3);
	cout << b1.Test(s1)<< endl;
	cout << b1.Test(s2)<< endl;
	cout << b1.Test(s3)<< endl;
}
int main()
{

	TestBloomFilter();
	return 0;
}

