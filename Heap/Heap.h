#pragma once
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
struct CmpGreat   //建大堆
{
	bool operator()(const T& data1, const T& data2)
	{
		return data1>data2;
	}
};

template<class T>
struct CmpLess   //建小堆
{
	bool operator()(const T& data1, const T& data2)
	{
		return data1<data2;
	}
};

template<class T, class CMP = CmpGreat<T>>
class Heap
{
public:
	Heap(T* arr, size_t size)
	{
		for(size_t i=0; i<size; ++i)
		{
			_heap.push_back(arr[i]);
		}

		for(int i=(size-2)/2; i>=0; --i)
		{
			_AdjustDown(i);
		}

	}

	void Push(const T& data)
	{
		_heap.push_back(data);
		size_t size = _heap.size();
		//向上调整
		_AdjustUp(size-1);
	}

	void Pop()
	{
		assert(!_heap.empty());

		size_t size = _heap.size();
		swap(_heap[0], _heap[size-1]);
		_heap.pop_back();
		_AdjustDown(0);
	}
protected:
	//向下调整
	void _AdjustDown(size_t i)
	{
		size_t child = i*2+1;
		size_t parent = i;

		size_t size = _heap.size();

		while(child <= size)
		{
			//if(child+1 < size && _heap[child] < _heap[child+1])
			if(child+1 < size && CMP()(_heap[child+1],_heap[child]))
			{
				child++;
			}

			//if(_heap[parent] < _heap[child])
			if(CMP()(_heap[child], _heap[parent]))
			{
				swap(_heap[parent], _heap[child]);
				parent = child;
				child = parent*2+1;
			}

			else
				break;
		}
	}

	void _AdjustUp(size_t i)
	{
		size_t child = i;
		while(child > 0)
		{
			size_t parent = (child-1)/2;
			//if(_heap[child] > _heap[parent])
			if(CMP()(_heap[child],_heap[parent]))
			{
				swap(_heap[child], _heap[parent]);
			}
			else
				break;

			child = parent;
		}
	}
protected:
	vector<T> _heap;
};


template<class T>
void AdjustDown(T* a, size_t size, size_t root)
{
	size_t parent = root;
	size_t child = root*2+1;

	while(child < size)

	{
		if(child+1<size && a[child+1]<a[child])
		{
			child++;
		}
		if(a[child] < a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
			break;
	}

}
//降序 --》小堆
//时间复杂度：N*LgN
template<class T>
void HeapSort(T* arr, size_t size)
{
	//建堆
	for(int i = (size-2)/2; i>=0; --i)
	{
		AdjustDown(arr, size, i);	
	}
	
	//排序
	int index = size-1;  //index:记录当前排序的结点
	while(index)
	{ 
		swap(arr[0], arr[index]);
		AdjustDown(arr, --index, 0);
	}

}