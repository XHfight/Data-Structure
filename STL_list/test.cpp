#include "MyList.h"
#include <iostream>
using namespace std;

void Test()
{
	MyList<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.PushBack(5);

	MyList<int>::Iterator it;
	it = l1.Begin();
	while (it != l1.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}