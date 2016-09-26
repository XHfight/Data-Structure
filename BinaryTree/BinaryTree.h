#pragma once
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& data = T())
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
	{}
	BinaryTree(const T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _BinaryTree(arr, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}
	~BinaryTree()
	{
		_Release(_root);
	}
	//现代写法
	BinaryTree& operator=(const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			BinaryTree c(t);
			swap(_root, c._root);
		}
		return *this;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()
	{
		queue<Node*> q;
		Node* cur = _root;
		if (cur != NULL)
			q.push(cur);

		while (!q.empty())
		{
			Node* f = q.front();
			cout << f->_data << " ";
			q.pop();

			if (f->_left)
				q.push(f->_left);
			if (f->_right)
				q.push(f->_right);
		}
		cout << endl;

	}

	void InOrder_NonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* t = s.top();
			cout << t->_data << " ";
			s.pop();
			cur = t->_right;
		}
		cout << endl;
	}

	void PrevOrder_NonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}

			Node* t = s.top();
			s.pop();
			cur = t->_right;
		}
		cout << endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t LeafSize()
	{
		return _LeafSize(_root);
	}

	size_t GetKLevel(int k) //计算第k层的结点的个数
	{
		return _GetKLevel(_root, k);
	}
private:
	Node* _BinaryTree(const T* arr, size_t size, size_t& index, const T& invalid)
	{
		if (index < size && arr[index] != invalid)
		{
			Node* node = new Node(arr[index]);
			node->_left = _BinaryTree(arr, size, ++index, invalid);
			node->_right = _BinaryTree(arr, size, ++index, invalid);
			return node;
		}
		return NULL;
	}

	void _Release(Node*& root)
	{
		if (root != NULL)
		{
			_Release(root->_left);
			_Release(root->_right);

			delete root;
			root = NULL;
		}
	}

	Node* _Copy(Node* root)
	{
		if (root != NULL)
		{
			Node* node = new Node(root->_data);
			node->_left = _Copy(root->_left);
			node->_right = _Copy(root->_right);
			return node;
		}
		return NULL;
	}

	void _PrevOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}

	void _InOrder(Node* root)
	{
		if (root != NULL)
		{
			_InOrder(root->_left);
			cout << root->_data << " ";
			_InOrder(root->_right);
		}
	}

	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_data << " ";
		}
	}


	size_t _Size(Node* root)
	{
		size_t count = 0;
		if (root != NULL)
		{
			count = 1 + _Size(root->_left) + _Size(root->_right);
		}
		return count;
	}

	size_t _Depth(Node* root)
	{
		size_t dep = 0;
		if (root != NULL)
		{
			size_t ld = _Depth(root->_left);
			size_t rd = _Depth(root->_right);
			dep = (ld > rd) ? ld + 1 : rd + 1;
		}
		return dep;
	}

	size_t _LeafSize(Node* root)
	{
		size_t ls = 0;
		if (root != NULL)
		{
			if (root->_left == NULL && root->_right == NULL)
				ls = 1;
			else
				ls = _LeafSize(root->_left) + _LeafSize(root->_right);

		}
		return ls;
	}

	size_t _GetKLevel(Node* root, int k)
	{
		if (root == NULL || k < 0)
		{
			return 0;
		}
		else if (k == 0) //根节点为第0层
		{
			return 1;
		}
		else
		{
			return _GetKLevel(root->_left, k - 1) + _GetKLevel(root->_right, k - 1);
		}
	}
protected:
	Node* _root;
};