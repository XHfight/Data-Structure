#pragma once
#include<iostream>
using namespace std;

template<class K, size_t M>
struct BTreeNode
{
	/*K _keys[M-1];
	BTreeNode* _subs[M];*/
	//为方便插入数据时树的分裂，将空间对开辟一个
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

	//库内定义的结构体
	//template<class K, class V>
	//struct pair
	//{
	//	K first;
	//	V second;
	//};

	//这里返回pair为了更好的在Insert中复用
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
		return pair<Node*, int>(parent, -1);  //用int 返回-1，标志没找到
	}


	bool Insert(const K& key)
	{
		//根节点为空
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			++_root->_size;
			return true;
		}

		pair<Node*, int> find = Find(key);

		//key已存在
		if(find.second != -1)
			return false;

		Node* insert = find.first;
		Node* sub = NULL;
		K newKey = key;

		//跳出条件：1.插入后无需分裂  2.分裂到根节点
		while(1)
		{
			//向insert中插入key和sub
			//检查是否符合分裂条件，如果无需分裂，则跳出；否则，继续向上分裂。
			_InsertKey(insert, newKey, sub);
			
			//分裂
			if(insert->_size == M)
			{
				size_t mid = insert->_size/2;

				if(insert == _root) //根结点
				{
					//分裂根节点
					_root = new Node;
					_root->_keys[0] = insert->_keys[mid];
					insert->_keys[mid] = K();
					//分裂新节点
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

					//分裂新节点
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
					sub = newNode; //新产生的结点newNode为newKey的右sub
					insert = parent; //注意顺序，改insert要防在最后

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