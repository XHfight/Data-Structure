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
	int _bf; //平衡因子

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
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

			//调整平衡因子
			--parent->_bf;
			_AdjustTree(parent);
		}
		else	//parent的右插入
		{
			parent->_right = cur;
			cur->_parent = parent;
			++parent->_bf;
			_AdjustTree(parent);
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	
	/*bool IsBalance()
	{
		return _IsBalance(_root);
	}*/

	bool IsBalance()
	{
		size_t height = 0;
		return _IsBalance(_root, height);
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
	void _AdjustTree(Node* parent)
	{
		//检查平衡因子
		while(parent)
		{
			if(parent->_bf == 0)//平衡因子为0，停止
				break;
			else if(parent->_bf == 1 ||parent->_bf == -1)//平衡因子为1/-1，继续向父结点调整
			{
				Node* sub = parent;
				parent = parent->_parent;
				if(parent)
				{
					if(parent->_left == sub)
						--parent->_bf;
					else
						++parent->_bf;
				}
			}
			else//平衡因子为2/-2，旋转
			{
				if(parent->_bf==2 && parent->_right->_bf==1)
				{
					//左旋
					_RotateL(parent);
				}
				else if(parent->_bf==2 && parent->_right->_bf==-1)
				{
					//右左双旋
					_RotateRL(parent);
				}
				else if(parent->_bf==-2 && parent->_left->_bf==-1)
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
	//右旋
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//subLR 和 parent
		parent->_left = subLR;
		if(subLR) //注意：有可能为空
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
		subL->_bf = parent->_bf = 0;
	}
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//subRL 和 parent
		parent->_right = subRL;
		if(subRL) //注意：有可能为空
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
		subR->_bf = parent->_bf = 0;
	}

	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		_RotateR(parent->_right);
		_RotateL(parent);

		if(bf == 0)
		{
			parent->_bf = subR->_bf = subRL->_bf;
		}
		else if(bf == 1)
		{
			parent->_bf = -1;
			subRL->_bf = 0;
			subR->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subRL->_bf = 0;
			subR->_bf = 1;
		}
	}

	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);

		if(bf == 0)
		{
			subLR->_bf = subL->_bf = parent->_bf = 0;
		}
		else if(bf == 1)
		{
			parent->_bf = 0;
			subLR->_bf = 0;
			subL->_bf = -1;
		}
		else
		{
			parent->_bf = 1;
			subLR->_bf = 0;
			subL->_bf = 0;
		}
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	size_t _Height(Node* root)
	{
		if(root == NULL)
			return 0;
		size_t LHeight = _Height(root->_left);
		size_t RHeight = _Height(root->_right);

		return (LHeight>RHeight) ? (LHeight+1) : (RHeight+1);
	}

	//bool _IsBalance(Node* root)
	//{
	//	if(root == NULL)
	//		return true;

	//	int bf = _Height(root->_right)-_Height(root->_left);
	//	if(bf != root->_bf)
	//		cout << "平衡因子异常 key:"<<root->_key<< endl;

	//	if(abs(bf) < 2)
	//		return _IsBalance(root->_left) && _IsBalance(root->_right);
	//	else
	//		return false;
	//}

	//优化
	bool _IsBalance(Node* root, size_t& height)
	{
		if(root == NULL)
		{
			return true;
		}

		size_t leftHeight = 0;
		size_t rightHeight = 0;

		if(_IsBalance(root->_left, leftHeight) && _IsBalance(root->_right, rightHeight))
		{
			height = leftHeight>rightHeight?(leftHeight+1):(rightHeight+1);
			return abs(leftHeight-rightHeight)<2;
		}
		else
			return false;
	}
protected:
	Node* _root;
};
