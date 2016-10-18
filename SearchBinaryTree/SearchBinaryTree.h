/*************************************************************************
	> File Name: BinarySearchTree.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Mon 17 Oct 2016 10:52:07 PM CST
 ************************************************************************/

#pragma once
#include <iostream>
using namespace std;

template <class K>
struct SearchBinaryTreeNode
{
	K _key;
	SearchBinaryTreeNode<K>* _left;
	SearchBinaryTreeNode<K>* _right;

	SearchBinaryTreeNode(const K& key)
		:_key(key)
		 ,_left(NULL)
		 ,_right(NULL)
	{}
};

template <class K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}
	
	SearchBinaryTree(const SearchBinaryTree<K>& sTree)
	{
		_root = _CopyTree(sTree._root);
	}

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

    //key不支持修改
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
				//删除
				if(cur->_left == NULL)
				{
					if(parent->_key > key)
						parent->_left = cur->_right;
					else
						parent->_right = cur->_right;

					delete cur;
					cur = NULL;
				}
				else if(cur->_right == NULL)
				{
					if(parent->_key > key)
						parent->_left = cur->_left;
					else
						parent->_right = cur->_right;

					delete cur;
					cur = NULL;
				}
				else
				{
					//思路：找右树的最左结点或左树的最右结点，与cur交换，然后删除最右或最左结点
					Node* l = cur->_right; //右树的最左节点
					while(l->_left!=NULL)
					{
						l = l->_left;
					}
					
					K tmp = l->_key;
					l->_key = cur->_key;
					cur->_key = tmp;
					
					delete l;
					l = NULL;
				}
				return true;
			}
		}
		return false;
	}

	~SearchBinaryTree()
	{
		_DestoryTree(_root);
		_root = NULL;
	}
protected:
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
protected:
	Node* _root;
};
