#include "DoubleLinkList.h"

void Test1()
{
	pDulNode list = NULL;
	pDulNode find = NULL;

	InitDoubleLinkList(&list);
	PushBack(list, 1);
	PushBack(list, 2);
	PushBack(list, 3);
	PushBack(list, 4);
	PushBack(list, 5);
	PushBack(list, 6);
//	find = Find(list, 7);
//	printf("%d\n",find->data);
//	Insert(list, find, 7);
	Remove(list, 6);
	Remove(list, 1);
	Remove(list, 3);


	PrintDoubleLinkList(list);
	DistoryDoubleLinkList(&list);
}

int main()
{
	Test1();
	system("pause");
	return 0;
}