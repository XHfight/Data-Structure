#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include <cassert>
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


	/*
	由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 6 5）
	*/
	void CreateBinaryTree(const T* prevOrderArr, const T* inOrderArr, size_t size1, size_t size2)
	{
		assert(prevOrderArr && inOrderArr);
		assert(size1 == size2);
		int prevArrIndex = 0;
		_root = _CreatTree(prevOrderArr, inOrderArr, prevArrIndex, 0, size1-1);
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

	void PostOrder_NonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prevVisited = NULL;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			
			Node* t = s.top();

			if (t->_right == NULL || t->_right == prevVisited)
			{
				cout << t->_data << " ";
				prevVisited = t;
				s.pop();
			}
			else
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

	/*
	求二叉树中最远的两个结点的距离
	*/

	//方法一：时间复杂度O(N^2)
	//思路：先求出以每个结点为根的最远距离，在求出的所有距离中选最大的就是整棵二叉树中最远的两个结点的距离
	size_t GetFarthestDistance1()
	{
		return _GetFarthestDistance1(_root);
	}

	//方法二：时间复杂度(N)
	//思路：
	//1，后序遍历每一节点，找出该节点到最右边的距离以及最左边的距离；
	//2，找到之和最大的即可。
	size_t GetFarthestDistance2()
	{
		int rightDep = 0, leftDep = 0;
		return _GetFarthestDistance2(_root, leftDep, rightDep);
	}

	/*
	判断一棵二叉树是否是完全二叉树
	*/
	//方法一：时间复杂度O(N)
	//思路：利用层序遍历（只入队非空节点）
	//(1)当一个结点只有右结点，不是完全二叉树。
	//(2)当检测出一个结点为叶子结点或只有左结点，则以后的结点都为叶子结点，否则，这棵树不是完全二叉树。
	bool IsCompleteBinaryTree1()
	{
		if (_root == NULL)
			return true;

		bool isVisited = false; //标记是否访问过叶子结点或只有左结点的结点 
		queue<Node*> q;
		q.push(_root);
		Node* cur = NULL;
		while (!q.empty())
		{
			cur = q.front();
			q.pop();

			if (cur->_left == NULL && cur->_right == NULL)
			{
				isVisited = true;
			}
			else
			{
				if (isVisited == true)
					return false;
				if (cur->_left != NULL && cur->_right == NULL)
				{
					isVisited = true;
					q.push(cur->_left);
				}
				else if (cur->_left != NULL && cur->_right != NULL)
				{
					q.push(cur->_left);
					q.push(cur->_right);
				}
				else  //左为空，右不为空
				{
					return false;
				}
			}	
		}
		return true;
	}

	//方法二：时间复杂度：O（N）
	//思路：利用层序遍历（空结点也入队），如果遇到空结点，跳出，则队列里剩余的结点都应该是空结点，否则，不是完全二叉树。
	bool IsCompleteBinaryTree2()
	{
		if (_root == NULL)
			return true;

		queue<Node*> q;
		q.push(_root);
		Node* cur = NULL;
		while ( (cur = q.front()) != NULL )
		{
			q.pop();
			q.push(cur->_left);
			q.push(cur->_right);
		}

		q.pop();

		while (!q.empty())
		{
			cur = q.front();
			q.pop();
			if (cur)
				return false;
		}
		return true;
	}

	/*
	求二叉树中两个结点的最近公共祖先
	*/

	//情景一：当这棵树为搜索二叉树
	//情景二：这棵树是一般的树，它是三叉链
	//情景三：这棵树就是一般的二叉链的树
	Node* RecentlyRoot(Node* node1, Node* node2)
	{
		//实现？？？
		return NULL;
	}
private:
	//中序区间[left, right]
	Node* _CreatTree(const T* prevOrderArr, const T* inOrderArr, int& prevIndex, int left, int right)
	{
		Node* root = NULL;
		if (right >= left)
		{
			root = new Node(prevOrderArr[prevIndex]);

			int index = -1;  //当前结点在中序遍历数组中的下标
			for (int i = left; i <= right; ++i)
			{
				if (inOrderArr[i] == prevOrderArr[prevIndex])
					index = i;
			}

			//如果index == -1,则证明传入前序和中序的数组不匹配
			assert(index != -1);
			
			++prevIndex;
			root->_left = _CreatTree(prevOrderArr, inOrderArr, prevIndex, left, index - 1);
			root->_right = _CreatTree(prevOrderArr, inOrderArr, prevIndex, index + 1, right);
		}
		return root;
	}

	size_t _GetFarthestDistance2(Node* root, int& leftDep, int& rightDep)
	{
		if (root == NULL)
		{
			leftDep = 0;
			rightDep = 0;
			return 0;
		}

		int llDep = 0, lrDep = 0; //左子树的左深度和左子树的右深度
		int leftDis = _GetFarthestDistance2(root->_left, llDep, lrDep);

		int rlDep = 0, rrDep = 0;//右子树的左深度和右子树的右深度
		int rightDis = _GetFarthestDistance2(root->_right, rlDep, rrDep);
		
		//选出左右的较大者为当前的左/右子树的深度
		leftDep = llDep > lrDep ? llDep : lrDep;
		rightDep = rlDep > rrDep ? rlDep : rrDep;

		int farthestDis = rightDep + leftDep;
		//左子树返回的，右子树返回的， 和当前的 三者选最大为当前最大距离
		if (leftDis > rightDis)
		{
			if (leftDis > farthestDis)
				farthestDis = leftDis;
		}
		else
		{
			if (rightDis > farthestDis)
				farthestDis = rightDis;
		}

		++leftDep;
		++rightDep;

		return farthestDis;
	}

	size_t  _GetFarthestDistance1(Node* root)
	{
		if (root == NULL)
			return 0;

		//计算以当前结点为根的树中两个结点的最大距离
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		int dis = left + right;
		
		//选择最大距离放入dis里面
		int leftDis = _GetFarthestDistance1(root->_left);
		int rightDis = _GetFarthestDistance1(root->_right);
		int max = (leftDis > rightDis) ? leftDis : rightDis;
		if (max > dis)
			dis = max;

		return dis;
	}

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