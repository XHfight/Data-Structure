#pragma once
#include <cassert>
#include <iostream>
using namespace std;


template <class T>
class Stack
{
public:
	Stack()
		:_data(NULL)
		, _size(0)
		, _capacity(0)
	{}
	~Stack()
	{
		if (_data != NULL)
		{
			delete _data;
			_data = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
	void Push(const T& data)
	{
		CheckCapacity();
		_data[_size++] = data;
	}
	void Pop()
	{
		assert(_size > 0);
		_size--;
	}
	T& Top() const
	{
		assert(_size > 0);
		return _data[_size - 1];
	}
	bool Empty() const
	{
		return _size == 0;
	}
	size_t Size() const
	{
		return _size;
	}
protected:
	void CheckCapacity()
	{
		if (_size == _capacity)
		{
			size_t newCapacity = _capacity * 2 + 3;
			T* tmp = new T[newCapacity];
			for (size_t i = 0; i < _size; ++i)
			{
				tmp[i] = _data[i];
			}
			delete _data;
			_data = tmp;
			_capacity = newCapacity;
		}
	}
protected:
	T* _data;
	size_t _size;
	size_t _capacity;
};
