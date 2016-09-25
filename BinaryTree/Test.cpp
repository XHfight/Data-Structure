#include "BinaryTree.h"

void TestBinaryTree()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int arr2[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	BinaryTree<int> t2(t1);
	t1.PrevOrder();
	t2.PrevOrder();

	BinaryTree<int> t3(arr2, sizeof(arr2) / sizeof(arr2[0]), '#');
	t2 = t3;	
	t3.InOrder();
	t2.InOrder();

	t1.PostOrder();
	cout << "t1.Size():" << t1.Size() << endl;
	cout << "t3.Size():" << t3.Size() << endl;

	cout << "t1.Depth():" << t1.Depth() << endl;
	cout << "t3.Depth():" << t3.Depth() << endl;

	cout << "t1.LeafSize():" << t1.LeafSize() << endl;
	cout << "t3.LeafSize():" << t3.LeafSize() << endl;

}
int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}