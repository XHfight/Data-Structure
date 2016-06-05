#include "LinkList.h"

void Test1()
{
	LinkList list;
	InitLinkList(&list);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);
	PrintLinkList(&list);
	PopBack(&list);
	PrintLinkList(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);

	PrintLinkList(&list);
	DestoryLinkList(&list);
}
void Test2()
{
	LinkList list;
	InitLinkList(&list);
	PushFront(&list, 1);
	PushFront(&list, 2);
	PushFront(&list, 3);
	PushFront(&list, 4);
	PushFront(&list, 5);
	PrintLinkList(&list);

	PopFront(&list);
	PrintLinkList(&list);
	PopFront(&list);
	PrintLinkList(&list);
	PopFront(&list);
	PrintLinkList(&list);
	PopFront(&list);
	PrintLinkList(&list);
	PopFront(&list);
	PrintLinkList(&list);
	PopFront(&list);
	PrintLinkList(&list);

	DestoryLinkList(&list);
}

void Test3()
{
	LinkList list;
	InitLinkList(&list);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);
	PrintLinkList(&list);
//	Insert(&list, Find(&list, 4), 3);
	Insert(&list, Find(&list, 1), 3);
	Insert(&list, Find(&list, 5), 3);

	PrintLinkList(&list);
	DestoryLinkList(&list);

}

void Test4()
{
	LinkList list;
	InitLinkList(&list);
	PushBack(&list, 4);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);
	PushBack(&list, 4);
	PrintLinkList(&list);
//	Remove(&list, 1);
//	Remove(&list, 5);
//	Remove(&list, 3);
	RemoveAll(&list, 4);
	PrintLinkList(&list);
	DestoryLinkList(&list);
}

void Test5()
{
	LinkList list;
	InitLinkList(&list);
	PushBack(&list, 4);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);
	PushBack(&list, 4);
	PrintLinkList(&list);
	Erase(&list,Find(&list,3));
	PrintLinkList(&list);
	BubbleSort(&list);
	PrintLinkList(&list);

	DestoryLinkList(&list);
}
int main()
{
//	Test1();
//	Test2();
//	Test3();
//	Test4();
	Test5();

	system("pause");
	return 0;
}