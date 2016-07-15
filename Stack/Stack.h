#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TURE 1
#define MAXSIZE 5

typedef int Status;
typedef int DataType;
typedef struct SqStack
{
	DataType data[MAXSIZE];
	int top; //’ª∂•÷∏’Î

}SqStack;

void InitStack(SqStack *s);
void ClearStack(SqStack *s);
int StackEmpty(const SqStack *s);
int GetTop(const SqStack *s);
Status Push(SqStack *s, DataType x);
Status Pop(SqStack *s);
int StackLength(const SqStack *s);

#endif