#pragma once
#include <stack> 
#include <iostream>
using namespace std;
	
enum PointerTag
{
	LINK,
	THREAD,
};

template<class T>
struct BinaryTreeNode_Thr
{
	T _data;
	BinaryTreeNode_Thr* _left;
	BinaryTreeNode_Thr* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNode_Thr(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template <class T>
class BinaryTree_Thr
{
	typedef BinaryTreeNode_Thr<T> Node;
public:
	BinaryTree_Thr()
		:_root(NULL)
	{}
	BinaryTree_Thr(T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(arr, size, index, invalid);
	}

	//递归版
	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	//非递归版
	/*void PrevOrderThreading()
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prevNode = NULL;
		while(cur || !s.empty())
		{
			while(cur)
			{
				if(cur->_left == NULL && cur->_leftTag == LINK)
				{
					cur->_leftTag = THREAD;
					cur->_left = prevNode;
				}
				
				if(prevNode && prevNode->_right == NULL && prevNode->_rightTag == LINK)
				{
					prevNode->_rightTag = THREAD;
					prevNode->_right = cur;
				}
					
				prevNode = cur;
			
				s.push(cur);
				if(cur->_leftTag == LINK)
					cur = cur->_left;
				else
					cur = NULL;

			}
			
			Node* t = s.top();
			s.pop();
			
			if(t->_rightTag == LINK)
				cur = t->_right;
		}
		prevNode->_rightTag = THREAD;
	}*/

	//递归版
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}
	
	//非递归版
	//void InOrderThreading()
	//{
	//	stack<Node*> s;
	//	Node* cur = _root;
	//	Node* prev = NULL;
	//	while(cur || !s.empty())
	//	{
	//		while(cur)
	//		{
	//			s.push(cur);
	//			cur = cur->_left;
	//		}
	//		
	//		Node* t = s.top();
	//		s.pop();
	//		
	//		//线索化 左
	//		if(t->_left == NULL && t->_leftTag == LINK)
	//		{
	//			t->_left = prev;
	//			t->_leftTag = THREAD;
	//		}
	//		//线索化 右
	//		if(prev && prev->_right == NULL && prev->_rightTag == LINK)
	//		{
	//			prev->_right = t;
	//			prev->_rightTag = THREAD;
	//		}

	//		prev = t;

	//		cur = t->_right;
	//	}
	//	prev->_rightTag = THREAD;
	//}
	
	//递归版
	void PostOrderThreading()
	{
		Node* prev = NULL;
		_PostOrderThreading(_root, prev);
	}

	//非递归版
	//void PostOrderThreading()
	//{
	//	Node* prevVisited = NULL;
	//	Node* cur = _root;
	//	stack<Node*> s;

	//	while(cur || !s.empty())
	//	{
	//		while(cur)
	//		{
	//			s.push(cur);
	//			cur = cur->_left;
	//		}

	//		Node* t = s.top();

	//		if(t->_right == NULL || prevVisited == t->_right)
	//		{
	//			if(t->_left == NULL)
	//			{
	//				t->_left = prevVisited;
	//				t->_leftTag = THREAD;
	//			}
	//			if(prevVisited && prevVisited->_right == NULL)
	//			{
	//				prevVisited->_right = t;
	//				prevVisited->_rightTag = THREAD;
	//			}
	//			s.pop(); // 注意:访问过后才可以pop
	//			prevVisited = t;
	//		}
	//		else
	//		{
	//			cur = t->_right;
	//		}
	//	}
	//}

	void PrevOrder()
	{
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			cur = cur->_right;
		}
		cout << endl;
	}

	void InOrder()
	{
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			
			while(cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				if(cur)
					cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}
	
	//线索化的后序遍历
	void PostOrder();

protected:
	void _PrevOrderThreading(Node* cur, Node*& prev)
	{
		if(cur == NULL)
			return;
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

		if(cur->_leftTag == LINK) //注意
			_PrevOrderThreading(cur->_left, prev);
		if(cur->_rightTag == LINK)	
			_PrevOrderThreading(cur->_right, prev);
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

	void _PostOrderThreading(Node* cur, Node*& prev)
	{
		if(cur == NULL)
			return;

		_PostOrderThreading(cur->_left, prev);
		_PostOrderThreading(cur->_right, prev);

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
	}

	Node* _CreateTree(T* arr, size_t size, size_t& index, const T& invalid)
	{
		Node* root = NULL;
		if(index<size && arr[index]!=invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreateTree(arr, size, ++index, invalid);
			root->_right = _CreateTree(arr, size, ++index, invalid);
		}
		return root;
	}
	
protected:
	Node* _root;
};
