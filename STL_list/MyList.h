#pragma once

template <class T>
struct __ListNode
{
	T _data;
	void *_next;
	void *_prev;

	ListNode(T data)
	:_data(data)
	,_next(NULL)
	,_prev(NULL)
	{}
};

template<class T, class Ref, class Ptr>
struct __List_Iterator
{
	typedef __ListNode<T>* LinkType;

	LinkType _node;

	__List_Iterator(LinkType x)
	:_node(x)
	{}


};

template<class T>
class MyList
{
	typedef __ListNode<T>* LinkType;

public:

	MyList()
	:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& data)
	{

	}

	void Insert(LinkType pos, const T& data)
	{

	}
protected:
	Node* BuyNode(T data)
	{
		LinkType tmp = new(T);
		return tmp;
	}
protected:
	LinkType _head;

};