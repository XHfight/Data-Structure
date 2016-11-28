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
	K _key; // 关键字（唯一）
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
	//非递归版
	//插入
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

	//查找：key不支持修改
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

	//删除
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
				//删除cur
				Node* del  = cur;
				if(cur->_left == NULL)
				{
					if(cur == _root) //删除的结点为根结点，且左为空（如果不判断，parent为NULL，会出错）
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
					//思路：找右树的最左结点或左树的最右结点，与cur交换，然后删除最右或最左结点
					parent = cur;
					Node* minR = cur->_right; //右树的最左节点
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

	//递归版
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

	//调用了ToOrderedDoubleList()，将树的内部结构调整了，所以析构会出现错误，先屏蔽掉

	//~SearchBinaryTree()
	//{
	//	_DestoryTree(_root);
	//	_root = NULL;
	//}


	/*
	思路：由搜索二叉树的特点（左<根<右），可以得到当中序遍历为有序。将左看作双向链表的prev指		针，右看作next指针。
		
		中序递归，将左子树（链表）的最后一个结点作为当前结点的left，最后一个结点的right为当			前结点。(相当于将中序遍历的每个结点依次插入到有序的链表中)。
	*/
	Node* ToOrderedDoubleList() //将搜索二叉树转换成有序的双向链表（递归）
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
	bool _InsertR(Node*& root, const K& key) //注意：巧用引用使节点连接起来
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
			//删除
			Node* del = root;
			if(root->_left == NULL) //删除左为空结点
				root = root->_right;
			else if(root->_right == NULL)//删除右为空结点
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
