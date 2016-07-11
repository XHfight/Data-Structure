#include "DoubleLinkList.h"

void InitDoubleLinkList(pDulNode* plist)
{
	pDulNode headNode = NULL; //设置头结点
	assert(plist);

	*plist = NULL;
	headNode = (pDulNode)malloc(sizeof(DulNode));
	if(headNode == NULL)
	{
		printf("out of memory!\n");
		exit(0);
	}
	headNode->next = NULL;
	headNode->prior = NULL;

	*plist = headNode;
}

pDulNode BuyNode(DataType x)
{
	pDulNode newNode = (pDulNode)malloc(sizeof(DulNode));
	if(newNode == NULL)
	{
		printf("out of memory!\n");
		exit(0);	
	}

	newNode->data = x;
	newNode->prior = NULL;
	newNode->next = NULL;

	return newNode;
}

void PushBack(pDulNode list, DataType x)
{
	pDulNode cur = list;
	pDulNode newNode = NULL;

	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	newNode = BuyNode(x);
	cur->next = newNode;
	newNode->prior = cur;
}

void PrintDoubleLinkList(pDulNode list)
{
	pDulNode prev = list;
	pDulNode cur = prev->next;

	while(cur)
	{
		if(cur->next == NULL)
		{
			printf("prior:%d [%d] next:NULL --> ", prev->data, cur->data);
			break;
		}
		printf("prior:%d [%d] next:%d --> ", prev->data, cur->data, cur->next->data);
		prev = cur;
		cur = cur->next;
	}
	printf("NULL\n");
}
void DistoryDoubleLinkList(pDulNode* plist)
{
	pDulNode cur = NULL;
	assert(plist);
	cur = *plist;
	while(cur)
	{
		pDulNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	*plist = NULL;
}

pDulNode Find(pDulNode list, DataType x)
{
	pDulNode cur = list;
	while(cur)
	{
		if(cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

void Insert(pDulNode list, pDulNode pos, DataType x)
{
	pDulNode prev = list;
	pDulNode cur = prev->next;

	while(cur)
	{
		if(cur == pos)
		{
			pDulNode newNode = BuyNode(x);
			prev->next = newNode;
			newNode->next = cur;
			cur->prior = newNode;
			newNode->prior = prev;
			return;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	printf("No Find!\n");
}

void Remove(pDulNode list, DataType x)
{
	pDulNode prev = list;
	pDulNode cur = list->next;

	while(cur)
	{
		if(cur->data == x)
		{
			pDulNode del = cur;
			prev->next = cur->next;
			if(prev->next != NULL)
			{
				prev->next->prior = prev;
			}
			free(del);
			del = NULL;

			cur = prev->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}