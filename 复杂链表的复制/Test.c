#include "ComplexList.h"

void Test1()
{
	pListNode list;
	pListNode newList;
	pListNode cur;
	InitComplexList(&list);
	InitComplexList(&newList);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);

	cur = list;
	cur->random = cur->next->next;  //1-->3
	cur = cur->next;
	cur->random = cur->next->next; //2-->4
	newList = CopyComplexList(list);

	PrintComplexList(list);

	PrintComplexList(newList);

//	DestoryComplexList(list);
//	DestoryComplexList(newList);
}

int main()
{
	Test1();
	system("pause");
	return 0;
}