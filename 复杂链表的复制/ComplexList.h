#ifndef __COMPLEXLIST_H__
#define __COMPLEXLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;
typedef struct ComplexListNode
{
	DataType data;
	struct ComplexListNode* next;
	struct ComplexListNode* random;
}ListNode,*pListNode;

void InitComplexList(pListNode* head);
void PushBack(pListNode* phead, DataType x);
void PrintComplexList(pListNode head);
void DestoryComplexList(pListNode head);
pListNode CopyComplexList(pListNode head);
#endif
