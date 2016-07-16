#ifndef __SQQUEUE_H__
#define __SQQUEUE_H__

#include <stdio.h>

#define MAXSIZE 5
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int DataType;
typedef int Status;

//ѭ�����е�˳��洢�ṹ
typedef struct SqQueue
{
	DataType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

void InitQueue(SqQueue *s);  //��ʼ������
void ClearQueue(SqQueue *s);  //��ն���
int QueueEmpty(const SqQueue *s);  //�ж϶����Ƿ�Ϊ��
Status GetHead(const SqQueue *s, DataType *head);  //���ض��еĶ�ͷԪ��
Status EnQueue(SqQueue *s, DataType x);  //β��
Status DeQueue(SqQueue *s);  //ͷɾ
int QueueLength(const SqQueue *s);  //���ض��еĳ���

#endif