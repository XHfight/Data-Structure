/*************************************************************************
	> File Name: HashTable_List.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sun 06 Nov 2016 02:35:58 PM CST
 ************************************************************************/
#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

//处理哈希冲突  开链法（拉链法）--哈希桶

template <class K, class V>
struct HashListNode
{
	K _key;
	V _value;
	HashListNode<K, V>* _next;

	HashListNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		 ,_next(NULL)
	{}
};

template <class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __HashFunc<string>
{
	static size_t BKDRHash(const char *str)
	{
		unsigned int seed= 131;// 31 131 1313 13131 131313
		unsigned int hash= 0;
		while(*str)
		{
			hash=hash*seed+ (*str++);
		}
		return(hash& 0x7FFFFFFF);
	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}	
};

template <class K, class V, class HashFunc = __HashFunc<K> >
class HashTable_List
{
	typedef HashListNode<K,V> Node;
public:
	HashTable_List()
	:_size(0)
	{}
	~HashTable_List()
	{
		size_t size = _table.size();
		for(size_t i=0; i<size; ++i)
		{
			Node* cur = _table[i];
			while(cur)
			{
				Node* del = cur;
				cur = cur->_next;
				delete del;
				del = NULL;
			}
		}
		_table.clear(); //将vector的size设置为0，并没有释放空间。
		_size = 0;
	}

	bool Insert(const K& key, const V& value)
	{
		_CheckSize();
		if(Find(key) != NULL) //结点已存在
			return false;

		size_t index = _HashFunc(key, _table.size());
		Node* node = new Node(key, value);
		node->_next = _table[index];
		_table[index] = node;
		
		++_size;
		return true;
	}

	Node* Find(const K& key)
	{
		if(_table.size() == 0)
			return NULL;
		size_t index = _HashFunc(key, _table.size());
		Node* cur = _table[index];
		while(cur)
		{
			if(cur->_key == key)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		size_t size = _table.size();
		if(size == 0)
			return false;
		size_t index = _HashFunc(key, size);

		Node* cur = _table[index];
		Node* del = NULL;
		//删头
		if(cur && cur->_key == key)
		{
			del = cur;
			_table[index] = cur->_next;
			delete del;
			del = NULL;
			--_size;
			return true;
		}
		else
		{
			Node* prev = cur;
			cur = cur->_next;
			while(cur)
			{
				if(cur->_key == key)
				{
					del = cur;
					prev->_next = cur->_next;
					delete del; 
					del = NULL;
					--_size;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}

	void Print()
	{
		size_t size = _table.size();
		for(size_t i=0; i<size; ++i)
		{
			printf("[%d]:", i);
			Node* cur = _table[i];
			while(cur)
			{
				cout << cur->_key << "->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}
protected:
	size_t _GetPrimeSize(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] = 
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for(size_t i=0; i<28; ++i)
		{
			if(_PrimeList[i] > size)
				return _PrimeList[i];
		}
		
		//已增到最大
		return _PrimeList[27];
	}

	size_t _HashFunc(const K& key, size_t size)
	{
		HashFunc hf;
		return hf(key)%size;
	}
	
	void _CheckSize()
	{
		if(_table.size()==0 || _size==_table.size())
		{
			size_t size = _table.size();
			size_t newSize = _GetPrimeSize(size);
			
			vector<Node*> newTable;
			newTable.resize(newSize);
			for(size_t i=0; i<size; ++i)
			{
				Node* cur = _table[i];
				while(cur)
				{
					size_t index = _HashFunc(cur->_key, newSize);
					Node* tmp = cur;
					tmp->_next = newTable[index];
					newTable[index] = tmp;
					cur = cur->_next;
				}
			}
			_table.swap(newTable);
		}
	}
protected:
	vector<Node*> _table;
	size_t _size;
};
