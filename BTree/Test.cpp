#include "BTree.h"

int main()
{
	int arr[] = {53, 75, 139, 49, 145, 36, 101};
	BTree<int, 3> b1;
	for(size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{

 		b1.Insert(arr[i]);
	}
	return 0;
}