#pragma once
#include <stack>
#include <iostream>
using namespace std;

enum SYM
{
	NUM,
	OPERATORS
};

enum OP
{
	ADD,
	SUB,
	MUL,
	DIV
};

struct Elem
{
	SYM _symbol;
	int _value;
};

int OperaRPN(Elem *RPN, size_t size);