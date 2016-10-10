#include "InOrderIterator.h"

void TestBinaryTreeThread()
{
	int array [10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6}; 
	BinaryTreeThread<int> t(array, sizeof(array)/sizeof(array[0]), '#');
	t.InOrderThreading();
}

void TestIter()
{
	int array [10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6}; 
	BinaryTreeThread<int> t(array, sizeof(array)/sizeof(array[0]), '#');
	t.InOrderThreading();

	BinaryTreeThread<int>::Iterator it;
	it = t.Begin();
	while(it != t.End())
	{
		cout<< *it << " ";
		++it;
	}
	cout <<endl;
}	

int main()
{
	TestBinaryTreeThread();
	TestIter();
	return 0;
}