//œ° Ëæÿ’Ûº∞∆‰—πÀı¥Ê¥¢
#pragma once

#include <vector>
#include <iostream>
using namespace std;

template<class T>
struct Triple
{
	size_t _r;
	size_t _c;
	T _value;


	Triple(size_t row, size_t col, const T& value)
		:_r(row)
		,_c(col)
		,_value(value)
	{}
};

template <class T>
class SparseMatrix
{
public:
	SparseMatrix(T* arr, size_t row, size_t col, const T& illegal)
		:_row(row)
		,_col(col)
		,_illegal(illegal)
	{
		for(size_t i = 0; i<row; ++i)
		{
			for(size_t j = 0; j<col; ++j)
			{
				if(arr[i*col+j] != illegal)
				{
					Triple<T> t(i,j,arr[i*col+j]);
					_matrix.push_back(t);
				}
			}
		}
	}

	void Display()
	{
		vector<Triple<T>>::iterator it = _matrix.begin();
		for(size_t i = 0; i<_row; ++i)
		{
			for(size_t j = 0; j<_col; ++j)
			{
				if(it!=_matrix.end()
					&&it->_r == i
					&&it->_c == j)
				{
					cout << it->_value <<" ";
					++it;
				}
				else
				{
					cout << _illegal <<" ";
				}
			}
			cout << endl;
		}
	cout << endl;
	}
protected:
	vector<Triple<T>> _matrix;
	size_t _row;
	size_t _col;
	T _illegal;
};