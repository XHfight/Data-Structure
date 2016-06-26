#include "ComplexList.h"

void InitComplexList(pListNode* phead)
{
	assert(phead);
	*phead = NULL;
}

pListNode BuyNode(DataType x)
{
	pListNode newNode = (pListNode)malloc(sizeof(ListNode));
	newNode->data = x;
	newNode->next = NULL;
	newNode->random = NULL;
}

void PushBack(pListNode* phead, DataType x)
{
	pListNode cur = *phead;
	pListNode newNode = NULL;
	if(cur == NULL)  //链表为空
	{
		newNode = BuyNode(x);
		*phead = newNode;
	}
	else            //链表不为空
	{
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		newNode = BuyNode(x);
		cur->next = newNode;
	}
}

void PrintComplexList(pListNode head)
{
	pListNode cur = head;
	while(cur)
	{
		if(cur->random != NULL)
		{
			printf("[%d]:random(%d)-->",cur->data, cur->random->data);
		}
		else
		{
			printf("[%d]:random(%s)-->",cur->data, NULL);
		}
		cur = cur->next;
	}
	printf("NULL\n");
}

void DestoryComplexList(pListNode head)
{
	pListNode cur = head;
	while(cur)
	{
		pListNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	head = NULL;
}

pListNode CopyComplexList(pListNode head)
{
	pListNode newHead = NULL;
	pListNode tail = NULL;
	pListNode cur = head;
	pListNode newNode = NULL;
	
	//1.将新链表与旧链表合并在一起
	while(cur)    
	{
		newNode = BuyNode(cur->data);
		newNode->next = cur->next;
		cur->next = newNode;
		cur = newNode->next;
	}

	//2.给新链表的random域赋值
	cur = head;
	while(cur)
	{
		if(cur->random != NULL)
		{
			cur->next->random = cur->random->next;
		}
		cur = cur->next->next;
	}

	//3.拆分链表
	cur = head;
	newHead = cur->next;
	tail = cur->next;
	while(cur)
	{
		cur->next = tail->next;
		if(cur->next != NULL)
		{
			tail->next = cur->next->next;
		}
		cur = cur->next;
		tail = tail->next;
	}
	return newHead;
}