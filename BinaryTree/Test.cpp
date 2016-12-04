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
	cout << "t1.PostOrder_NonR:" << endl;
	t1.PostOrder_NonR();

	cout << "t1.PrevOrder_NonR:" << endl;
	t1.PrevOrder_NonR();

	cout << "t1.InOrder_NonR:" << endl;
	t1.InOrder_NonR();
	
	cout << "t1.LevelOrder:" << endl;
	t1.LevelOrder();

	cout << "t1.GetKLevel(2):" << t1.GetKLevel(2)<< endl;


	cout << "t1.Size():" << t1.Size() << endl;
	cout << "t3.Size():" << t3.Size() << endl;

		cout << "t1.Depth():" << t1.Depth() << endl;
	cout << "t3.Depth():" << t3.Depth() << endl;

	cout << "t1.LeafSize():" << t1.LeafSize() << endl;
	cout << "t3.LeafSize():" << t3.LeafSize() << endl;

}

void TestDistance()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int arr2[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	t1.PrevOrder();
	BinaryTree<int> t2(arr2, sizeof(arr2) / sizeof(arr2[0]), '#');
	t2.PrevOrder();

	cout << t1.GetFarthestDistance1() << endl;
	cout << t2.GetFarthestDistance1() << endl;

	cout << t1.GetFarthestDistance2() << endl;
	cout << t2.GetFarthestDistance2() << endl;

}


void TestCreateBinaryTree()  //测试前序和中序重建二叉树
{
	int prev[] = { 1, 2, 3, 4, 5, 6 };
	int in[] = { 3, 2, 4, 1, 6, 5 };
	BinaryTree<int> tree;
	tree.CreateBinaryTree(prev, in, sizeof(prev) / sizeof(prev[0]), sizeof(in)/sizeof(in[0]));
	tree.PrevOrder();
}

int main()
{
//	TestBinaryTree();
	//TestDistance();
	TestCreateBinaryTree();
	system("pause");
	return 0;
}