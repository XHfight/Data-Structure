#include "SolveRPN.h"

void TestRPN()
{
	//这里已知表达式，所以用结构体数组来存储，如果表达式为一个一个输入可以用顺序表来存储。
	Elem RPN[] =
	{
		{ NUM, 12 },
		{ NUM, 3 },
		{ NUM, 4 },
		{ OPERATORS, ADD },
		{ OPERATORS, MUL },
		{ NUM, 6 },
		{ OPERATORS, SUB },
		{ NUM, 8 },
		{ NUM, 2 },
		{ OPERATORS, DIV },
		{ OPERATORS, ADD },
	};
	size_t size = sizeof(RPN) / sizeof(Elem);

	cout << OperaRPN(RPN,size) << endl;
}
int main()
{
	TestRPN();
	system("pause");
	return 0;
}