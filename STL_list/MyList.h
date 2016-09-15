#pragma once
#include <iostream>
using namespace std;
template <class T>
struct __ListNode
{
	T _data;
	void *_next;
	void *_prev;

	__ListNode(T data)
		:_data(data)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template<class T, class Ref, class Ptr>
struct __List_Iterator
{
	typedef __ListNode<T>* LinkType;
	typedef __List_Iterator<T, Ref, Ptr> self;
	typedef __List_Iterator<T, T&, T*> Iterator;

	LinkType _node;

	__List_Iterator()
	:_node(NULL)
	{}

	__List_Iterator(LinkType x)
		:_node(x)
	{}

	__List_Iterator(const Iterator& x)
		:_node(x._node)
	{}

	bool operator==(const self& x) const
	{
		return _node == x._node;
	}
	bool operator!=(const self& x) const
	{
		return _node != x._node;
	}

	self& operator++()
	{
		_node = (LinkType)_node->_next;
		return *this;
	}
	self operator++(int)
	{
		self tmp(*this);
		_node = (LinkType)_node->_next;
		return tmp;
	}
	self& operator--()
	{
		_node = _(LinkType)node->_prev;
		return *this;
	}
	self operator--(int)
	{
		Self tmp(*this);
		_node = (LinkType)_node->_prev;
		return tmp;
	}



	Ref operator*() const
	{
		return _node->_data;
	}


	Ptr operator->()
	{
		return &(operator*());
	}


};

template<class T>
class MyList
{
	typedef __ListNode<T>* LinkType;

public:
	typedef __List_Iterator<T, T&, T*> Iterator;
public:

	MyList()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin() const 
	{
		return (LinkType)_head->_next;
	}

	Iterator End() const
	{
		return (LinkType)_head;
	}
	bool Empty()
	{
		return _head->_next == _head;
	}

	size_t Size()
	{
		LinkType cur(_head->_next);
		size_t count = 0;
		while (cur != _head)
		{
			count++;
			cur = cur->_next;
		}
	}

	Iterator Insert(const Iterator& pos, const T& data)
	{
		LinkType newNode = BuyNode(data);
		newNode->_next = pos._node;
		newNode->_prev = pos._node->_prev;

		LinkType(pos._node->_prev)->_next = newNode;
		pos._node->_prev = newNode;
		return newNode;    //为什么返回值传参可以传过去？？
	}
	void PushBack(const T& data)
	{
		Insert(End(), data);
	}

protected:
	LinkType BuyNode(const T& data)
	{
		LinkType tmp = new __ListNode<T>(data);
		return tmp;
	}

protected:
	LinkType _head;
};