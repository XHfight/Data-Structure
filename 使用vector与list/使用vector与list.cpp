#include <iostream>
using namespace std;

#include <vector>
#include <list>

void TestVector()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	cout << v1.size() << endl;
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	v1.pop_back();
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	//vector没有push_front和pop_front函数，因为效率低
	while (!v1.empty())
	{
		cout << v1.back() << " ";
		v1.pop_back();
	}
	cout << endl;


	//迭代器使用
	vector<int> v2;
	for (size_t i = 0; i < 5; ++i)
	{
		v2.push_back(i);
	}

	vector<int>::iterator it;
	for (it = v2.begin(); it < v2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void TestList()
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);

	while (!l1.empty())
	{
		cout << l1.front() << " ";
		l1.pop_front();
	}
	cout << endl;

	list<int> l2;
	for (size_t i = 1; i < 6; ++i)
	{
		l2.push_back(i);
	}

	list<int>::iterator it;
	for(it = l2.begin(); it != l2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
int main()
{
	//TestVector();
	TestList();
	system("pause");
	return 0;
}