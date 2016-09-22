/*************************************************************************
	> File Name: TransposeMatrix.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Thu 22 Sep 2016 09:03:11 AM CST
 ************************************************************************/
#pragma once
#include<iostream>
using namespace std;

template <class T>
class Matrix
{
public:
	Matrix(T* arr, size_t r, size_t c)
	:_Matrix(new T[r*c])
	 ,_row(r)
	 ,_col(c)
	{
		for(size_t i = 0; i<_row; ++i)
		{
			for(size_t j = 0; j<_col; ++j)
			{
				_Matrix[i*_col+j] = arr[i*c+j];
			}
		}
	}

	Matrix(const Matrix<T>& m)
		:_Matrix(new T[m._row*m._col])
		 ,_row(m._row)
		 ,_col(m._col)
	{
		if(this == &m)
		{
			return;
		}
		for(size_t i=0; i<_row; ++i)
		{
			for(size_t j=0; j<_col; ++j)
			{
				_Matrix[i*_col+j] = m._Matrix[i*_col+j];
			}
		}
	}
	void Print()
	{
		for(size_t i=0; i<_row; ++i)
		{
			for(size_t j=0; j<_col; ++j)
			{
				cout << _Matrix[i*_col+j]<<" ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void Transpose()
	{
		Matrix t(*this);
		for(size_t i = 0; i<t._row; ++i)
		{
			for(size_t j = 0; j<t._col; ++j)
			{
				_Matrix[j*t._row+i] = t._Matrix[i*t._col+j];
			}
		}
		swap(_row,_col);
	}

protected:
	T* _Matrix;
	size_t _row;
	size_t _col;
};
