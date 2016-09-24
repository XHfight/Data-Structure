#include "GeneralLists.h"


void TestGeneralList()
{
	//����
	GeneralList gl = "()";
	GeneralList g2 = "(a,b)";
	GeneralList g3 = "(a,(c,d))";
	g3.Print();
	 
	//��������
	GeneralList g4(g3);
	g4.Print();

	//��ֵ���������
	g2 = g3;
	g2.Print();

	//��Ԫ�ظ���
	cout << g3.Size() << endl;

	//�����
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
