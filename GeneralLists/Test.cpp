#include "GeneralLists.h"


void TestGeneralList()
{
	//构造
	GeneralList gl = "()";
	GeneralList g2 = "(a,b)";
	GeneralList g3 = "(a,(c,d))";
	g3.Print();
	 
	//拷贝构造
	GeneralList g4(g3);
	g4.Print();

	//赋值运算符重载
	g2 = g3;
	g2.Print();

	//求元素个数
	cout << g3.Size() << endl;

	//求深度
	cout << "g3.depth:" << g3.Depth() << endl;
	GeneralList g5 = "(((),()),(),(a,(b,(c,d))))";
	g5.Print();
	cout << "g5.depth:"<< g5.Depth() << endl;

}
int main()
{
	TestGeneralList();
 //	system("pause");
	return 0;
}
