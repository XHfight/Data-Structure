#include "LinkList.h"

void InitLinkList(pLinkList plist)
{
	assert(plist);
	plist->pHead = NULL;
}
void DestoryLinkList(pLinkList plist)
{
	pListNode cur = NULL;
	assert(plist);
	cur = plist->pHead;
	while(cur)
	{
		pListNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	plist->pHead = NULL;
}

pListNode BuyNode(DataType x) //创建一个结点
{
	pListNode newNode = (pListNode)malloc(sizeof(ListNode));
	if(NULL == newNode)
	{
		printf("out of memory!");
		exit(0);
	}
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}
void PushBack(pLinkList plist, DataType x)
{
	pListNode cur = NULL;
	pListNode newNode = NULL;
	assert(plist);
	cur = plist->pHead;
	newNode = BuyNode(x);
	if(NULL == cur)   //空链表
	{
		plist->pHead = newNode;
	}
	else              //链表不为空
	{
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}
void PopBack(pLinkList plist)
{
	pListNode cur = NULL;
	assert(plist);
	cur = plist->pHead;
	if(NULL == cur)    //链表为空
	{
		printf("LinkList is Empty\n");
	}
	else if(NULL == cur->next) //链表只有一个结点
	{
		free(cur);
		cur = NULL;
		plist->pHead = NULL;
	}
	else    //链表有两个及以上结点
	{
		while(cur->next->next != NULL)
		{
			cur = cur->next;
		}
		free(cur->next);
		cur->next = NULL;
	}
}
void PushFront(pLinkList plist, DataType x)
{
	pListNode newNode = NULL;
	assert(plist);
	newNode = BuyNode(x);
	newNode->next = plist->pHead;
	plist->pHead = newNode;
}
void PopFront(pLinkList plist)
{
	assert(plist);
	if(NULL == plist->pHead)
	{
		printf("LinkList is Empty\n");
		return;
	}
	else
	{
		pListNode del = plist->pHead;
		plist->pHead = del->next;
		free(del);
		del = NULL;
	}
}
void PrintLinkList(pLinkList plist)
{
	pListNode cur = NULL;
	assert(plist);
	cur = plist->pHead;
	while(cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
pListNode Find(pLinkList plist, DataType x)
{
	pListNode cur = NULL;
	assert(plist);
	cur = plist->pHead;
	while(cur)
	{
		if(cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
void Insert(pLinkList plist, pListNode pos, DataType x) //在pos之前插入
{
	pListNode newNode = NULL;
	assert(plist);
	assert(pos);
	newNode = BuyNode(x);
	if(pos == plist->pHead)
	{
		PushFront(plist, x);
	}
	else
	{
		pListNode cur = plist->pHead;
		while(cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = newNode;
		newNode->next = pos;
	}
}
void Remove(pLinkList plist, DataType x)  //删除数据为x的结点
{
	pListNode pos = NULL;
	assert(plist);
	pos = Find(plist, x);
	if(pos == NULL)
	{
		printf("no find\n");
	}
	else if(pos == plist->pHead)
	{
		PopFront(plist);
	}
	else
	{
		pListNode cur = plist->pHead;
		while(cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = pos->next;
		free(pos);
		pos = NULL;
	}
}
void RemoveAll(pLinkList plist, DataType x)
{
	pListNode cur = NULL;
	assert(plist);
	cur = plist->pHead;
	if(plist->pHead == NULL)//空链表
	{
		return;
	}
	else if(plist->pHead->next == NULL)  //只有一个结点
	{
		free(cur);
		cur = NULL;
		plist->pHead =NULL;
		return;
	}
	while(cur->data == x)  //头
	{
		pListNode del = cur;
		cur = cur->next;
		plist->pHead = cur;
		free(del);
		del = NULL;
	}
	while(cur && cur->next)                  //中间和尾
	{
		if(cur->next->data == x)
		{
			
			pListNode del = cur->next;
			cur->next = del->next;
			free(del);
			del = NULL;
		}
		cur = cur->next;
	}
}
void Erase(pLinkList plist, pListNode pos)
{

	assert(pos);
	assert(plist);
	if(pos == plist->pHead)
	{
		PopFront(plist);
	}
	else
	{
		pListNode cur = plist->pHead;
		while(cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = pos->next;
		free(pos);
		pos = NULL;
	}
}
void BubbleSort(pLinkList plist)
{
	int flag = 0;
	pListNode cur = NULL;   //控制外循环排序的趟数
	pListNode log= NULL;   //记录内循环上一次交换的最后一个数
	pListNode cmp = NULL;  //记录内循环的当前比较值
	assert(plist);
	log = plist->pHead;
	cur = plist->pHead;

	while(log)
	{
		log = log->next;
	}
	while(cur->next != NULL)
	{
		pListNode node = NULL;
		cmp = plist->pHead;
		log = node;
		flag = 0;
		while(cmp->next!=log)
		{
			if(cmp->data > cmp->next->data)
			{
				DataType tmp = cmp->data;
				cmp->data = cmp->next->data;
				cmp->next->data = tmp;
				node = cmp;
				flag = 1;
			}
			cmp = cmp->next;
		}
		if(flag == 0)
		{
			return;
		}
		cur = cur->next;
	}
}
