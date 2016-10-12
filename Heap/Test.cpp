#include "Heap.h"

void TestMaxHeap()
{
	int a[] = {10,11, 13, 12, 16, 18, 15, 17, 14, 19};
	Heap<int, CmpLess<int>> h1(a, sizeof(a)/sizeof(a[0]));
	h1.Push(30);
	h1.Pop();
}

int main()
{
	TestMaxHeap();
	return 0;
}