#include "Stack.h"
#include <assert.h>
#include <memory.h>

Status status = OK;

void InitStack(SqStack *s)
{
	assert(s);
	memset(s->data, 0, MAXSIZE);
	s->top = -1;
}

void ClearStack(SqStack *s)
{
	assert(s);
	if(s->top != -1)
	{
		s->top = -1;
	}
}

int StackEmpty(const SqStack *s)
{
	assert(s);
	if(s->top > -1)
	{
		return FALSE;
	}
	else
	{
		return TURE;
	}
}

int GetTop(const SqStack *s)
{
	assert(s);
	if(s->top > -1)
	{
		return s->data[s->top];
	}
	else
	{
		status = ERROR;
		return 0;
	}
}

Status Push(SqStack *s, DataType x)
{
	assert(s);
	if(s->top == MAXSIZE-1)
	{
		printf("Stack is Fulled\n");
		return ERROR;
	}
	else
	{
		s->data[++s->top] = x;
		return OK;
	}
}

Status Pop(SqStack *s)
{
	assert(s);
	if(s->top == -1)
	{
		printf("Stack is Empty\n");
		return ERROR;
	}
	else
	{
		s->top--;
		return OK;
	}
}

int StackLength(const SqStack *s)
{
	assert(s);
	return s->top+1;
}