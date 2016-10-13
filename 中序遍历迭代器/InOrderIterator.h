#pragma once
#include <iostream>
#include <cassert>
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

template<class T, class Ref, class Ptr>
struct __BinaryTreeThreadIterator
{
	typedef BinaryTreeThreadNode<T> Node;
	typedef __BinaryTreeThreadIterator<T, Ref, Ptr> Self;
	Node* _node;

	__BinaryTreeThreadIterator()
		:_node(NULL)
	{}

	__BinaryTreeThreadIterator(Node* node)
		:_node(node)
	{}

	Self& operator++()
	{
		assert(_node);
		if(_node->_rightTag == THREAD)
		{
			_node = _node->_right;
		}
		else
		{
			_node = _node->_right;
			while(_node->_leftTag == LINK)
			{
				_node = _node->_left;
			}
		}
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}

	Self& operator--()
	{
		assert(_node);
		if(_node->_leftTag == LINK)
		{
			_node = _node->_left;
			while(_node->_rightTag == LINK)
			{
				_node = _node->_right;
			}
		}
		else
		{
			_node = _node->_left;
		}
	}

	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}

	Ref operator*()	const
	{
		assert(_node);
		return _node->_data;
	}

	bool operator!=(const Self& it) const
	{
		return (_node != it._node);
	}
};

template <class T, class Ref, class Ptr>
class BinaryTreeThread
{
	typedef BinaryTreeThreadNode<T> Node;
public:
	typedef __BinaryTreeThreadIterator<T, T&, T*> Iterator;
	typedef __BinaryTreeThreadIterator<T, const T&, const T*> ConstIterator;


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
		Node* cur = _root;
		while(cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}
		return cur;
	}

	Iterator End()
	{
		return (Node*)NULL;
	}

	ConstIterator Begin() const
	{
		Node* cur = _root;
		while(cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}
		return cur;
	}

	ConstIterator End() const
	{
		return (Node*)NULL;
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