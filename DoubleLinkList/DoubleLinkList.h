#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;
typedef struct DulNode
{
	DataType data;
	struct DulNode* prior;
	struct DulNode* next;
}DulNode, *pDulNode;

void InitDoubleLinkList(pDulNode* plist);
void PushBack(pDulNode lsit, DataType x);
void PrintDoubleLinkList(pDulNode list);
void DistoryDoubleLinkList(pDulNode* plist);
pDulNode Find(pDulNode list, DataType x);

void Insert(pDulNode list, pDulNode pos, DataType x);
void Remove(pDulNode list, DataType x);
#endif