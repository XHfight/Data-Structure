#pragma once
#include <iostream>
using namespace std;

enum PointerTag
{
	LINK,
	THREAD,
};

template<class T>
struct BinaryTreeThreadNode
{
	T _data;
	BinaryTreeThreadNode* _left;
	BinaryTreeThreadNode* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeThreadNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}

};

template<class T>
struct __BinaryTreeThreadIterator
{
	typedef BinaryTreeThreadNode<T> Node;
	typedef __BinaryTreeThreadIterator Iterator;

	Node* node;

	Iterator& operator++()
	{
		if(node->_rightTag == THREAD)
		{
			node = node->_right;
		}
		else
		{
			node = node->_right;
			while(node->_leftTag == LINK)
			{
				node = node->_left;
			}
		}
		return *this;
	}

	T& operator*()	const
	{
		return node->_data;
	}

	bool operator!=(const Iterator& it)
	{
		if(node != it.node)
			return true;
		else
			return false;
	}
};

template <class T>
class BinaryTreeThread
{
	typedef BinaryTreeThreadNode<T> Node;
public:
	typedef __BinaryTreeThreadIterator<T> Iterator;

public:
	BinaryTreeThread(T* arr, size_t size, const T& invalue)
	{
		size_t index = 0;
		_root = _CreatTree(arr, size, index, invalue);
	}

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
		prev->_rightTag = THREAD;
	}
	Iterator Begin()
	{
		Iterator it;
		Node* cur = _root;
		while(cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}
		it.node = cur;
		return it;
	}

	Iterator End()
	{
		Iterator it;
		it.node = NULL;
		return it;
	}
protected:
	Node* _CreatTree(T* arr, size_t size, size_t& index, const T& invalue)
	{
		Node* node = NULL;
		if(index<size && arr[index] != invalue)
		{
			node = new Node(arr[index]);
			node->_left = _CreatTree(arr, size, ++index, invalue);
			node->_right = _CreatTree(arr, size, ++index, invalue);
		}

		return node;
	}

	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if(cur == NULL)
			return;

		_InOrderThreading(cur->_left, prev);

		if(cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if(prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}
protected:
	Node* _root;
};