#include "SolveRPN.h"
#include <cassert>

int OperaRPN(Elem *RPN,size_t size)
{


	stack<Elem> num;
	for (size_t i = 0; i < size; ++i)
	{
		if (RPN[i]._symbol == NUM)
		{
			num.push(RPN[i]);
		}
		else
		{
			int right = num.top()._value;
			num.pop();

			switch (RPN[i]._value)
			{
			case ADD:
				num.top()._value += right;
				break;
			case SUB:
				num.top()._value -= right;

				break;
			case MUL:
				num.top()._value *= right;

				break;
			case DIV:
				num.top()._value /= right;

				break;
			default:
				assert(false);
				break;
			}
		}
	}
	return num.top()._value;

}