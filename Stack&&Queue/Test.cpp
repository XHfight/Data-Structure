#include "Stack.h"
#include "Queue.h"
#include "Maze.h"
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

void TestQueue()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	while (!q1.Empty())
	{
		cout << q1.Front() << endl;
		q1.Pop();
	}

}

void TestMaze()
{
	int row = 10;
	int col = 10;

	char* Map = (char*)malloc((row*col)*sizeof(char));
	Pos mEnter(2, 0);
	InitMazeMap( Map, row, col);
	PrintMazeMap(Map, row, col);
	if(GetPath(Map, row, col, mEnter))
	{
		PrintMazeMap(Map, row, col);
	}
	else
	{
		cout << "没有通路"<<endl;
	}
	free(Map);
}
int main()
{
	//TestStack();
	//TestQueue();
	TestMaze();
	system("pause");
	return 0;
}