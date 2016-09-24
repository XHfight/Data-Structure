#pragma once 
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

enum NodeType
{
	HEAD,
	VALUE,
	SUB,
};

struct GeneralListNode
{
	NodeType _type;
	struct GeneralListNode* _next;

	union
	{
		char _value;
		struct GeneralListNode* _sub;
	};

	GeneralListNode(NodeType type, char value = ' ')
		:_type(type)
		,_next(NULL)
	{
		if(_type == VALUE)
		{
			_value = value;
		}
		else if(_type == SUB)
		{
			_sub = NULL;
		}
	}
};

class GeneralList
{
	typedef GeneralListNode Node;
public:
	GeneralList()
		:_head(NULL)
	{}
	GeneralList(const char* str)
		:_head(NULL)
	{
		_head = CreatList(str);
	}
	GeneralList(const GeneralList& gl)
	{
		_head = Copy(gl._head);
	}
	~GeneralList()
	{
		Release(_head);
	}
	void Print()
	{
		Print(_head);
		cout << endl;
	}

	//传统写法
	/*
	GeneralList& operator=(const GeneralList& g)
	{
		if(this != &g)
		{
			Node* tmp = Copy(g._head);
			Release(_head);
			_head = tmp;
		}
		return *this;
	}
	*/

	//现代写法
	GeneralList& operator=(const GeneralList& g)
	{
		if(this != &g)
		{
			GeneralList tmp(g);
			//swap
			Node* t = _head;
			_head = tmp._head;
			tmp._head = t;
		}
		return *this;
	}

	size_t Size()
	{
		return Count(_head);
	}
	size_t Depth()
	{
		return Dep(_head);
	}

private:
	Node* CreatList(const char*& str);
	bool IsValue(char value);
	void Print(Node* head);
	Node* Copy(Node* head);
	void Release(Node* head);
	size_t Count(Node* head);
	size_t Dep(Node* node);
protected:
	Node* _head;
};
