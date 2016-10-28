/*************************************************************************
	> File Name: RBTree.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Thu 27 Oct 2016 10:31:08 PM CST
 ************************************************************************/

#pragma once
#include<iostream>
using namespace std;

//记录结点的颜色
enum Color
{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K ,V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		 ,_value(value)
		 ,_left(NULL)
		 ,_right(NULL)
		 ,_parent(NULL)
		 ,_col(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		
		// 找插入结点的位置
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		//插入结点
		cur = new Node(key, value);
		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//调整树
		while(cur!=_root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;//由于父结点的颜色为红，所以祖父结点必不为空
			if(grandfather->_left == parent) //cur在左
			{
				Node* uncle = grandfather->_right;
				if(uncle && uncle->_col==RED)//（1）叔叔存在且为红
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else //（2）叔叔为空（3）叔叔存在且为黑
				{
					if(cur == parent->_right)
					{
						_RotateL(parent);
						swap(parent, cur);//注意：必须交换指针指向，否则后面颜色改变会出错
					}
					_RotateR(grandfather);
					//变色
					grandfather->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
			else//cur在右
			{
				Node* uncle = grandfather->_left;
				if(uncle && uncle->_col==RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_left)
					{
						_RotateR(parent);
						swap(parent, cur);
					}
					_RotateL(grandfather);
					//变色
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
		}
		//出来之后将根节点置为黑色
		_root->_col = BLACK;
		return true;
	}
	
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	
	bool IsBalance()
	{
		if(_root == NULL)
			return true;
		if(_root->_col == RED)
			return false;
		
		int count = 0;//记录黑色结点的个数
		Node* cur = _root;
		while(cur)
		{
			if(cur->_col == BLACK)
				++count;
			cur = cur->_left;
		}
		return _IsBalance(_root, count, 0);	
	}

	~RBTree()
	{
		_Release(_root);
	}
protected:
	bool _IsBalance(Node* root,const int count, int black)
	{
		if(root == NULL)
			return true;
		//判断是否有连续红结点
		if(root->_col==RED)
		{
			Node* parent = root->_parent;
			if(parent && parent->_col==RED)
			{
				cout << "连续红结点:" << parent->_key << " " << root->_key << endl;
				return false;
			}
		}

		//判断黑色结点数目相等
		if(root->_col == BLACK)
			++black;
	
		if(root->_right==NULL && root->_left==NULL)
		{
			if(black != count)
				return false;
			else
				return true;
		}

		return _IsBalance(root->_left, count, black) && _IsBalance(root->_right, count, black);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<< root->_key <<" ";
		_InOrder(root->_right);
	}

	void _Release(Node* root)
	{
		if(root == NULL)
			return;
		_Release(root->_left);
		_Release(root->_right);
		delete root;
		root = NULL;
	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if(ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if(ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}
protected:
	Node* _root;
};


