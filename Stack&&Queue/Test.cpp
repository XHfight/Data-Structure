#include "Stack.h"

void TestStack()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);

	while (!s1.Empty())
	{
		cout << s1.Top() << endl;
		s1.Pop();
	}

}

int main()
{
	TestStack();
	system("pause");
	return 0;
}