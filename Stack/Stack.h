#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TURE 1
#define MAXSIZE 5
#define DOUBLE_MAXSIZE 5
typedef int Status;
typedef int DataType;

//˳��ջ
typedef struct SqStack
{
	DataType data[MAXSIZE];
	int top; //ջ��ָ��

}SqStack;

//��ջ����ռ�
typedef struct SqDoubleStack
{
	DataType data[DOUBLE_MAXSIZE];
	int top1;  //ջ1ջ��ָ��
	int top2;  //ջ2ջ��ָ��

}SqDoubleStack;

//˳��ջ��������
void InitStack(SqStack *s);
void ClearStack(SqStack *s);
int StackEmpty(const SqStack *s);
int GetTop(const SqStack *s);
Status Push(SqStack *s, DataType x);
Status Pop(SqStack *s);
int StackLength(const SqStack *s);

//��ջ����ռ��������
void InitDulStack(SqDoubleStack *s);
Status Push_Dul(SqDoubleStack *s, DataType x, int StackNumber);
Status Pop_Dul(SqDoubleStack *s, int StackNumber);

#endif