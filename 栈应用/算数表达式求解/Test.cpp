#include "SolveRPN.h"

void TestRPN()
{
	//������֪���ʽ�������ýṹ���������洢��������ʽΪһ��һ�����������˳������洢��
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