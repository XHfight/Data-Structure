#include "BinaryTree_Thr.h"

void TestPrevThread()
{
	int arr[10] = {1, 2, 3,'#','#', 4,'#','#', 5, 6};
	int arr2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree_Thr<int> t(arr, sizeof(arr)/sizeof(arr[0]), '#');
	BinaryTree_Thr<int> t2(arr2, sizeof(arr2)/sizeof(arr2[0]), '#');

	t.PrevOrderThreading();
	t.PrevOrder();

	t2.PrevOrderThreading();
	t2.PrevOrder();
}

void TestInThread()
{
	int arr[10] = {1, 2, 3,'#','#', 4,'#','#', 5, 6};
	BinaryTree_Thr<int> t(arr, sizeof(arr)/sizeof(arr[0]), '#');

	int arr2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree_Thr<int> t2(arr2, sizeof(arr2)/sizeof(arr2[0]), '#');


	t.InOrderThreading();
	t.InOrder();

	t2.InOrderThreading();
	t2.InOrder();
}

void TestPostThread()
{
	int arr[10] = {1, 2, 3,'#','#', 4,'#','#', 5, 6};
	BinaryTree_Thr<int> t(arr, sizeof(arr)/sizeof(arr[0]), '#');
	t.PostOrderThreading();	
	//t.PostOrder();
}

int main()
{
	//TestPrevThread();
	TestInThread();
	//TestPostThread();
	return 0;
}

