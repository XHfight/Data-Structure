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
	int _ba; //ƽ������

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
		
		//���Ҳ���λ��
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
		
		//����
		cur = new Node(key, value);
		if(parent->_key > key) //parent�������
		{
			parent->_left = cur;
			cur->_parent = parent;
			//��ƽ������
			--parent->_ba;

			//���ƽ������
			while(parent)
			{
				if(parent->_ba == 0)//ƽ������Ϊ0��ֹͣ
					break;
				else if(parent->_ba == 1 ||parent->_ba == -1)//ƽ������Ϊ1/-1�������򸸽�����
				{
					parent = parent->_parent;
					if(parent)
						--parent->_ba;
				}
				else//ƽ������Ϊ2/-2����ת
				{
					if(parent->_ba==2 && parent->_right->_ba==1)
					{
						//����
						_RotateL(parent);
					}
					else if(parent->_ba==2 && parent->_right->_ba==-1)
					{
						//����˫��
						_RotateRL(parent);
					}
					else if(parent->_ba==-2 && parent->_left->_ba==-1)
					{
						//����
						_RotateR(parent);
					}
					else //parent->_ba==-2 && parent->_left->_ba==1
					{
						//����˫��
						_RotateLR(parent);
					}
					break;
				}	
			}
		}
		else	//parent���Ҳ���
		{
			parent->_right = cur;
			cur->_parent = parent;
			++parent->_ba;
			//���ƽ������
			while(parent)
			{
				if(parent->_ba == 0)//ƽ������Ϊ0��ֹͣ
					break;
				else if(parent->_ba == 1 ||parent->_ba == -1)//ƽ������Ϊ1/-1�������򸸽�����
				{
					parent = parent->_parent;
					if(parent)
						++parent->_ba;
				}
				else//ƽ������Ϊ2/-2����ת
				{
					if(parent->_ba==2 && parent->_right->_ba==1)
					{
						//����
						_RotateL(parent);
					}
					else if(parent->_ba==2 && parent->_right->_ba==-1)
					{
						//����˫��
						_RotateRL(parent);
					}
					else if(parent->_ba==-2 && parent->_left->_ba==-1)
					{
						//����
						_RotateR(parent);
					}
					else
					{
						//����˫��
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
	//����
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//subLR �� parent
		parent->_left = subLR;
		if(subLR) //ע�⣺�п���Ϊ��
			subLR->_parent = parent;

		//subL �� pp
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

		//subL �� parent
		subL->_right = parent;
		parent->_parent = subL;

		//��ƽ������
		subL->_ba = parent->_ba = 0;
	}
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//subRL �� parent
		parent->_right = subRL;
		if(subRL) //ע�⣺�п���Ϊ��
			subRL->_parent = parent;

		//pp �� subR
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
		//parent �� subR
		subR->_left = parent;
		parent->_parent = subR;

		//��ƽ������
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
