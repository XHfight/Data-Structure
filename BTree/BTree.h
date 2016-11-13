#pragma once
#include<iostream>
using namespace std;

template<class K, size_t M>
struct BTreeNode
{
	/*K _keys[M-1];
	BTreeNode* _subs[M];*/
	//Ϊ�����������ʱ���ķ��ѣ����ռ�Կ���һ��
	K _keys[M];
	BTreeNode* _subs[M+1];

	BTreeNode* _parent;
	size_t _size;

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(size_t i = 0; i < M; ++i)
		{
			_keys[i] = K();
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}
};

template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	//���ڶ���Ľṹ��
	//template<class K, class V>
	//struct pair
	//{
	//	K first;
	//	V second;
	//};

	//���ﷵ��pairΪ�˸��õ���Insert�и���
	pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			size_t i = 0;
			while(i < cur->_size)
			{
				if(cur->_keys[i] < key)
				{
					++i;
				}
				else if(cur->_keys[i] > key)
				{
					break;
				}
				else  //cur->_keys[i] == key
					return pair<Node*, int>(parent,i);
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return pair<Node*, int>(parent, -1);  //��int ����-1����־û�ҵ�
	}


	bool Insert(const K& key)
	{
		//���ڵ�Ϊ��
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			++_root->_size;
			return true;
		}

		pair<Node*, int> find = Find(key);

		//key�Ѵ���
		if(find.second != -1)
			return false;

		Node* insert = find.first;
		Node* sub = NULL;
		K newKey = key;

		//����������1.������������  2.���ѵ����ڵ�
		while(1)
		{
			//��insert�в���key��sub
			//����Ƿ���Ϸ������������������ѣ������������򣬼������Ϸ��ѡ�
			_InsertKey(insert, newKey, sub);
			
			//����
			if(insert->_size == M)
			{
				size_t mid = insert->_size/2;

				if(insert == _root) //�����
				{
					//���Ѹ��ڵ�
					_root = new Node;
					_root->_keys[0] = insert->_keys[mid];
					insert->_keys[mid] = K();
					//�����½ڵ�
					Node* newNode = new Node;
					size_t j = 0;
					size_t i = mid+1;
					for(; i < insert->_size; ++i,++j)
					{
						newNode->_keys[j] = insert->_keys[i];
						insert->_keys[i] = K();
						newNode->_subs[j] = insert->_subs[i];
						insert->_subs[i] = NULL;
						++newNode->_size;
					}
					newNode->_subs[j] = insert->_subs[i];
					insert->_subs[i] = NULL;
					
					newNode->_parent = _root;

					_root->_subs[0] = insert;
					_root->_subs[1] = newNode;
					++_root->_size;

					insert->_parent = _root;
					insert->_size -= (newNode->_size)+1; 

					break;
				}
				else
				{
					Node* parent = insert->_parent;

					//�����½ڵ�
					Node* newNode = new Node;
					size_t j = 0;
					size_t i = mid+1;
					for(; i < insert->_size; ++i,++j)
					{
						newNode->_keys[j] = insert->_keys[i];
						insert->_keys[i] = K();
						newNode->_subs[j] = insert->_subs[i];
						insert->_subs[i] = NULL;
						++newNode->_size;
					}
					newNode->_subs[j] = insert->_subs[i]; 
					insert->_subs[i] = NULL;

					newNode->_parent = parent;
					
					insert->_size -= (newNode->_size)+1;
					
					newKey = insert->_keys[mid];
					insert->_keys[mid] = K();
					sub = newNode; //�²����Ľ��newNodeΪnewKey����sub
					insert = parent; //ע��˳�򣬸�insertҪ�������

				}
			}
			else
				break;
		}
		return true;
	}
protected:
	void _InsertKey(Node* node, K key, Node* sub)
	{
		size_t i = node->_size-1;
		while(i >= 0)
		{
			if(key < node->_keys[i])
			{
				node->_keys[i+1] = node->_keys[i];
				node->_subs[i+2] = node->_subs[i+1];
				--i;
			}
			else // >
				break;
		}
		node->_keys[i+1] = key;
		node->_subs[i+2] = sub;
		++node->_size;
	}
protected:
	Node* _root;
};