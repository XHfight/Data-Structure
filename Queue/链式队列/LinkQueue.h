#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TURE 1

typedef int Status;
typedef int DataType;
typedef struct QNode  //���ɶ��еĽ�㶨��
{
	DataType data;
	struct QNode *next;
}QNode;

typedef struct LinkQueue  //���ж���
{
	QNode *front, *rear;
}LinkQueue;

void InitLinkQueue(LinkQueue *lq);  //��ʼ������
void DistoryLinkQueue(LinkQueue *lq);  //���ٶ���
int QueueEmpty(const LinkQueue *lq);   //�ж϶����Ƿ�Ϊ��
int QueueLength(const LinkQueue *lq);  //������еĳ���
Status GetHead(const LinkQueue *lq, DataType *head); //���ض��еĶ�ͷԪ��
void EnQueue(LinkQueue *lq, DataType x); //���
Status DeQueue(LinkQueue *lq);   //����

#endif