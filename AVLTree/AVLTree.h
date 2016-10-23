/*************************************************************************
	> File Name: AVLTree.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 23 Oct 2016 05:10:21 PM CST
 ************************************************************************/

#pragma once
#include<iostream>
using namespace std;

template <class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _ba; //平衡因子

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		 ,_value(value)
		 ,_left(NULL)
		 ,_right(NULL)
		 ,_parent(NULL)
		 ,_ba(0)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	
	bool Insert(const K& key, const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		
		//查找插入位置
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
		
		//插入
		cur = new Node(key, value);
		if(parent->_key > key) //parent的左插入
		{
			parent->_left = cur;
			cur->_parent = parent;
			//改平衡因子
			--parent->_ba;

			//检查平衡因子
			while(parent)
			{
				if(parent->_ba == 0)//平衡因子为0，停止
					break;
				else if(parent->_ba == 1 ||parent->_ba == -1)//平衡因子为1/-1，继续向父结点调整
				{
					parent = parent->_parent;
					if(parent)
						--parent->_ba;
				}
				else//平衡因子为2/-2，旋转
				{
					if(parent->_ba==2 && parent->_right->_ba==1)
					{
						//左旋
						_RotateL(parent);
					}
					else if(parent->_ba==2 && parent->_right->_ba==-1)
					{
						//右左双旋
						_RotateRL(parent);
					}
					else if(parent->_ba==-2 && parent->_left->_ba==-1)
					{
						//右旋
						_RotateR(parent);
					}
					else //parent->_ba==-2 && parent->_left->_ba==1
					{
						//左右双旋
						_RotateLR(parent);
					}
					break;
				}	
			}
		}
		else	//parent的右插入
		{
			parent->_right = cur;
			cur->_parent = parent;
			++parent->_ba;
			//检查平衡因子
			while(parent)
			{
				if(parent->_ba == 0)//平衡因子为0，停止
					break;
				else if(parent->_ba == 1 ||parent->_ba == -1)//平衡因子为1/-1，继续向父结点调整
				{
					parent = parent->_parent;
					if(parent)
						++parent->_ba;
				}
				else//平衡因子为2/-2，旋转
				{
					if(parent->_ba==2 && parent->_right->_ba==1)
					{
						//左旋
						_RotateL(parent);
					}
					else if(parent->_ba==2 && parent->_right->_ba==-1)
					{
						//右左双旋
						_RotateRL(parent);
					}
					else if(parent->_ba==-2 && parent->_left->_ba==-1)
					{
						//右旋
						_RotateR(parent);
					}
					else
					{
						//左右双旋
						_RotateLR(parent);
					}
					break;
				}
			}

		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	~AVLTree()
	{
		_Release(_root);
	}
protected:
	void _Release(Node* root)
	{
		if(root == NULL)
			return;
		_Release(root->_left);
		_Release(root->_right);

		delete root;
		root = NULL;
	}
	//右旋
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//subLR 和 parent
		parent->_left = subLR;
		subLR->_parent = parent;

		//subL 和 pp
		Node* pp = parent->_parent;
		subL->_parent = pp;
		if(pp)
		{
			if(pp->_left == parent)
				pp->_left = subL;
			else
				pp->_right = subL;
		}
		else
		{
			_root = subL;
			subL->_parent = NULL;
		}

		//subL 和 parent
		subL->_right = parent;
		parent->_parent = subL;

		//改平衡因子
		subL->_ba = parent->_ba = 0;
	}
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//subRL 和 parent
		parent->_right = subRL;
		subRL->_parent = parent;

		//pp 和 subR
		Node* pp = parent->_parent;
		subR->_parent = pp;
		if(pp)
		{
			if(pp->_left == parent)
				pp->_left = subR;
			else
				pp->_right = subR;
		}
		else
		{
			_root = subR;
			subR->_parent = NULL;
		}
		//parent 和 subR
		subR->_left = parent;
		parent->_parent = subR;

		//改平衡因子
		subR->_ba = parent->_ba = 0;
	}

	void _RotateRL(Node* parent)
	{
		_RotateR(parent->_right);
		_RotateL(parent);
	}

	void _RotateLR(Node* parent)
	{
		_RotateL(parent->_left);
		_RotateR(parent);
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
protected:
	Node* _root;
};
