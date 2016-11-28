/*************************************************************************
> File Name: BinarySearchTree.h
> Author: XH
> Mail: X_H_fight@163.com 
> Created Time: Mon 17 Oct 2016 10:52:07 PM CST
************************************************************************/

#pragma once
#include <iostream>
using namespace std;

template <class K, class V>
struct SearchBinaryTreeNode
{
	K _key; // �ؼ��֣�Ψһ��
	V _value;
	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	SearchBinaryTreeNode(const K& key)
		:_key(key)
		,_value(V())
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class K, class V>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K, V> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	SearchBinaryTree(const SearchBinaryTree<K,V>& sTree)
	{
		_root = _CopyTree(sTree._root);
	}
	//�ǵݹ��
	//����
	bool Insert(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		if(_root == NULL)
		{
			_root = new Node(key);
			return true;
		}

		while(cur)
		{
			if(cur->_key == key)
			{
				return false;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				parent = cur;
				cur = cur->_left;
			}
		}

		if(parent->_key > key)
			parent->_left = new Node(key);
		else
			parent->_right = new Node(key);

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//���ң�key��֧���޸�
	bool Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key == key)
				return true;
			else if(cur->_key < key)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		return false;
	}

	//ɾ��
	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//ɾ��cur
				Node* del  = cur;
				if(cur->_left == NULL)
				{
					if(cur == _root) //ɾ���Ľ��Ϊ����㣬����Ϊ�գ�������жϣ�parentΪNULL�������
						_root = cur->_right;
					else
					{
						if(parent->_key > key)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
					}
				}	
				else if(cur->_right == NULL)
				{
					if(cur == _root)
						_root = cur->_left;
					else
					{
						if(parent->_key > key)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_right;
					}
				}
				else
				{
					//˼·��������������������������ҽ�㣬��cur������Ȼ��ɾ�����һ�������
					parent = cur;
					Node* minR = cur->_right; //����������ڵ�
					while(minR->_left != NULL)
					{
						parent = minR;
						minR = minR->_left;
					}
					cur->_key = minR->_key;

					if(parent->_left == minR)
						parent->_left = minR->_right;
					else
						parent->_right = minR->_right;

					del = minR;
				}
				delete del;
				return true;
			}
		}
		return false;
	}

	//�ݹ��
	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}

	//������ToOrderedDoubleList()���������ڲ��ṹ�����ˣ�������������ִ��������ε�

	//~SearchBinaryTree()
	//{
	//	_DestoryTree(_root);
	//	_root = NULL;
	//}


	/*
	˼·�����������������ص㣨��<��<�ң������Եõ����������Ϊ���򡣽�����˫�������prevָ		�룬�ҿ���nextָ�롣
		
		����ݹ飬�������������������һ�������Ϊ��ǰ����left�����һ������rightΪ��			ǰ��㡣(�൱�ڽ����������ÿ��������β��뵽�����������)��
	*/
	Node* ToOrderedDoubleList() //������������ת���������˫�������ݹ飩
	{
		Node* lastNode = NULL;
		Node* head = _root;
		while(head && head->_left!=NULL)
		{
			head = head->_left;
		}
		_ToOrderedDoubleList(_root, lastNode);
		return head;
	}

protected:
	void _ToOrderedDoubleList(Node* root, Node*& lastNode)
	{
		if(root == NULL)
			return;
		if(root->_left != NULL)
			_ToOrderedDoubleList(root->_left, lastNode);

		root->_left = lastNode;
		if(lastNode != NULL)
			lastNode->_right= root;

		lastNode = root;

		if(root->_right != NULL)
			_ToOrderedDoubleList(root->_right, lastNode);
	}

	void _DestoryTree(Node* root)
	{
		if(root == NULL)
			return;
		_DestoryTree(root->_left);
		_DestoryTree(root->_right);
		delete root;
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* _CopyTree(Node* root)
	{
		if(root == NULL)
			return NULL;

		Node* r = new Node(root->_key);
		r->_left = _CopyTree(root->_left);
		r->_right = _CopyTree(root->_right);
		return r;
	}

	bool _FindR(Node* root,const K& key)
	{
		if(root == NULL)
			return false;
		if(key == root->_key)
			return true;
		else if(key < root->_key)
		{
			return _FindR(key->_left, key);
		}
		else
		{
			return _FindR(key->_right, key);
		}
	}
	bool _InsertR(Node*& root, const K& key) //ע�⣺��������ʹ�ڵ���������
	{
		if(root == NULL)
		{
			root = new Node(key);
			return true;
		}

		if(root->_key == key)
			return false;
		else if(root->_key > key)
			return _InsertR(root->_left, key);
		else
			return _InsertR(root->_right, key);
	}

	bool _RemoveR(Node*& root, const K& key)
	{
		if(root == NULL)
			return false;

		if(root->_key > key)
			return _RemoveR(root->_left, key);
		else if(root->_key < key)
			return _RemoveR(root->_right, key);
		else
		{
			//ɾ��
			Node* del = root;
			if(root->_left == NULL) //ɾ����Ϊ�ս��
				root = root->_right;
			else if(root->_right == NULL)//ɾ����Ϊ�ս��
				root = root->_left;
			else
			{
				Node* parent = root;
				Node* minR = root->_right;
				while(minR->_left != NULL)
				{
					parent = minR;
					minR = minR->_left;
				}
				root->_key = minR->_key;

				if(parent->_left == minR)
					parent->_left = minR->_right;
				else
					parent->_right = minR->_right;

				del = minR;
			}
			delete del;
			del = NULL;
			return true;
		}
	}
protected:
	Node* _root;
};
