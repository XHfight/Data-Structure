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
	��ǰ���������������ؽ���������ǰ�����У�1 2 3 4 5 6 - ��������:3 2 4 1 6 5��
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
	//�ִ�д��
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

	size_t GetKLevel(int k) //�����k��Ľ��ĸ���
	{
		return _GetKLevel(_root, k);
	}

	/*
	�����������Զ���������ľ���
	*/

	//����һ��ʱ�临�Ӷ�O(N^2)
	//˼·���������ÿ�����Ϊ������Զ���룬����������о�����ѡ���ľ������ö���������Զ���������ľ���
	size_t GetFarthestDistance1()
	{
		return _GetFarthestDistance1(_root);
	}

	//��������ʱ�临�Ӷ�(N)
	//˼·��
	//1���������ÿһ�ڵ㣬�ҳ��ýڵ㵽���ұߵľ����Լ�����ߵľ��룻
	//2���ҵ�֮�����ļ��ɡ�
	size_t GetFarthestDistance2()
	{
		int rightDep = 0, leftDep = 0;
		return _GetFarthestDistance2(_root, leftDep, rightDep);
	}

	/*
	�ж�һ�ö������Ƿ�����ȫ������
	*/
	//����һ��ʱ�临�Ӷ�O(N)
	//˼·�����ò��������ֻ��ӷǿսڵ㣩
	//(1)��һ�����ֻ���ҽ�㣬������ȫ��������
	//(2)������һ�����ΪҶ�ӽ���ֻ�����㣬���Ժ�Ľ�㶼ΪҶ�ӽ�㣬���������������ȫ��������
	bool IsCompleteBinaryTree1()
	{
		if (_root == NULL)
			return true;

		bool isVisited = false; //����Ƿ���ʹ�Ҷ�ӽ���ֻ������Ľ�� 
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
				else  //��Ϊ�գ��Ҳ�Ϊ��
				{
					return false;
				}
			}	
		}
		return true;
	}

	//��������ʱ�临�Ӷȣ�O��N��
	//˼·�����ò���������ս��Ҳ��ӣ�����������ս�㣬�������������ʣ��Ľ�㶼Ӧ���ǿս�㣬���򣬲�����ȫ��������
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
	����������������������������
	*/

	//�龰һ���������Ϊ����������
	//�龰�����������һ�����������������
	//�龰�������������һ��Ķ���������
	Node* RecentlyRoot(Node* node1, Node* node2)
	{
		//ʵ�֣�����
		return NULL;
	}
private:
	//��������[left, right]
	Node* _CreatTree(const T* prevOrderArr, const T* inOrderArr, int& prevIndex, int left, int right)
	{
		Node* root = NULL;
		if (right >= left)
		{
			root = new Node(prevOrderArr[prevIndex]);

			int index = -1;  //��ǰ�����������������е��±�
			for (int i = left; i <= right; ++i)
			{
				if (inOrderArr[i] == prevOrderArr[prevIndex])
					index = i;
			}

			//���index == -1,��֤������ǰ�����������鲻ƥ��
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

		int llDep = 0, lrDep = 0; //������������Ⱥ��������������
		int leftDis = _GetFarthestDistance2(root->_left, llDep, lrDep);

		int rlDep = 0, rrDep = 0;//������������Ⱥ��������������
		int rightDis = _GetFarthestDistance2(root->_right, rlDep, rrDep);
		
		//ѡ�����ҵĽϴ���Ϊ��ǰ����/�����������
		leftDep = llDep > lrDep ? llDep : lrDep;
		rightDep = rlDep > rrDep ? rlDep : rrDep;

		int farthestDis = rightDep + leftDep;
		//���������صģ����������صģ� �͵�ǰ�� ����ѡ���Ϊ��ǰ������
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

		//�����Ե�ǰ���Ϊ����������������������
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		int dis = left + right;
		
		//ѡ�����������dis����
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
		else if (k == 0) //���ڵ�Ϊ��0��
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