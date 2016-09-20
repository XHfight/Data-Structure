//对称矩阵及其压缩存储

#pragma once
#include <iostream>
using namespace std;

template <class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* arr, size_t n)
		:_n(n)
		,_matrix(new T[n*(n+1)/2])
	{
		size_t index = 0;
		for(size_t i = 0; i<n; ++i)
		{
			for(size_t j=0; j<n;++j)
			{
				if(i >= j)
				{
					_matrix[index] = arr[i*n+j];
					++index;
				}
				else
				{
					continue;
				}
			}
		}
	}
	void Display()
	{
		for(size_t i =0; i < _n; ++i)
		{
			for(size_t j = 0; j < _n; ++j)
			{
			/*	if(i<j)
				{
					swap(i,j);
					cout<<_matrix[i*(i+1)/2+j]<<" ";
					swap(i,j);
				}
				else
					cout<<_matrix[i*(i+1)/2+j]<<" ";
			*/
				cout << Access(i,j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	T& Access(size_t row, size_t col)
	{
		if(row<col)
		{
			swap(row, col);
		}
		return _matrix[row*(row+1)/2+col];
	}
	~SymmetricMatrix()
	{
		if(_matrix != NULL)
		{
			delete[] _matrix;
			_matrix = NULL;
		}
	}
protected:
	T* _matrix;
	size_t _n; //对称矩阵的行列大小
};
