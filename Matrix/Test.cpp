#include "SymmetricMatrix.h"
#include "SparseMatrix.h"
void TestSymmetricMatrix()
{
	 int a [5][5]=  
	 {
		 {0,1,2,3,4},
		 {1,0,1,2,3},
		 {2,1,0,1,2},
		 {3,2,1,0,1},
		 {4,3,2,1,0},
	 };

	SymmetricMatrix<int> sm((int*)a, 5);
	sm.Display();
}

void TestSparseMatrix()
{
	int array [6][5] =     
	{{1, 0, 3, 0, 5},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 3, 0, 5},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}};
	SparseMatrix<int> sm((int *)array,6,5,0);
	sm.Display();
}

void TestTranspose()
{
	int array [6][5] =     
		        {{1, 0, 3, 0, 5},
			     {0, 0, 0, 0, 0},
			     {0, 0, 0, 0, 0},
			     {1, 0, 3, 0, 5},
			     {0, 0, 0, 0, 0},
				 {0, 0, 0, 0, 0}};
	SparseMatrix<int> sm((int*)array,6,5,0);
	sm.Display();
	SparseMatrix<int> tm = sm.Transpose();
	tm.Display();
}

void TestFastTranspose()
{
	int array [6][5] =     
		        {{1, 0, 3, 0, 5},
			     {0, 0, 0, 0, 0},
			     {0, 0, 0, 0, 0},
			     {1, 0, 3, 0, 5},
			     {0, 0, 0, 0, 0},
				 {0, 0, 0, 0, 0}};
	SparseMatrix<int> sm((int*)array,6,5,0);
	sm.Display();
	SparseMatrix<int> tm = sm.FastTranspose();
	tm.Display();
}


int main()
{
	//TestSymmetricMatrix();
	//TestSparseMatrix();
	//TestTranspose();
	TestFastTranspose();
	system("pause");
	return 0;
}
