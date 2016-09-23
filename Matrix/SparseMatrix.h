//稀疏矩阵及其压缩存储
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


	Triple(size_t row = 0, size_t col = 0, const T& value = T())
		:_r(row)
		,_c(col)
		,_value(value)
	{}
};

template <class T>
class SparseMatrix
{
public:
	SparseMatrix()
	:_row(0)
	 ,_col(0)
	 ,_illegal(T())
	{}

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

		vector<Triple<T> >::iterator iter;
		iter = _matrix.begin();
		for(size_t i = 0; i<_row; ++i)
		{
			for(size_t j = 0; j<_col; ++j)
			{
				if(iter!=_matrix.end()
					&&iter->_r == i
					&&iter->_c == j)
				{
					cout << iter->_value <<" ";
					++iter;
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
	//普通转置(行优先存储)
	//列变行，从0列开始，将列数据一个一个放进转置矩阵
	SparseMatrix<T> Transpose() 
	{
		SparseMatrix<T> tm;
		tm._row = _col;
		tm._col = _row;
		tm._illegal = _illegal;
		tm._matrix.reserve(_matrix.size());

		for(size_t i = 0; i<_col; ++i)
		{
			size_t index = 0;
			while(index < _matrix.size())
			{
				if(_matrix[index]._c == i)
				{
					Triple<T> t(_matrix[index]._c, _matrix[index]._r, _matrix[index]._value);
					tm._matrix.push_back(t);
				}
				++index;
			}
		}
		return tm;
	}

	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> tm;
		tm._row = _col;
		tm._col = _row;
		tm._illegal = _illegal;
		tm._matrix.resize(_matrix.size());

		int* count = new int[_col];//记录每行的元素个数
		memset(count, 0, sizeof(int)*_col);
		int* start = new int[_col];//转置矩阵中元素的位置
		start[0] = 0;
		
		size_t index = 0;
		while(index < _matrix.size())
		{
			count[_matrix[index]._c]++;
			++index;		
		}

		for(size_t i=1; i<_col; ++i)
		{
			start[i] = start[i-1] + count[i-1]; 
		}
		
		index = 0;
		while(index < _matrix.size())
		{
			Triple<T> t(_matrix[index]._c, _matrix[index]._r, _matrix[index]._value);
			tm._matrix[start[_matrix[index]._c]++] = t;   //核心代码
			++index;
		}

		delete[] count;
		delete[] start;
		return tm;
	}
protected:
	vector<Triple<T> > _matrix;
	size_t _row;
	size_t _col;
	T _illegal;
};
