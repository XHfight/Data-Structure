/*************************************************************************
	> File Name: HashTable.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Wed 02 Nov 2016 07:07:13 PM CST
 ************************************************************************/

#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

enum Status
{
	EMPTY,
	EXIST,
	DELETE,
};
template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//模板的特化：类型符合，优先调用特化的版本
template <>
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

template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	Status _sta;
	
	HashNode(const K& key = K(), const V& value = V())
		:_key(key)
		 ,_value(value)
		 ,_sta(EMPTY)
	{}
};

template<class K, class V, class HashFunc=__HashFunc<K> >
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{
		_table.resize(_GetPrimeSize(0));
	}

	bool Insert(const K& key, const V& value)
	{
		_CheckSize();
		
		size_t index = _HashFunc(key);
		int i = 0;
		while(_table[index]._sta == EXIST)
		{
			if(_table[index]._key == key)
				return false;
			++i;
			index = (index + (i*i)) % _table.size();
		}
		
		_table[index]._key = key;
		_table[index]._value = value;
		_table[index]._sta = EXIST;
		++_size;
		return true;
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		int i = 0;
		size_t begin = index;//记录起点的
		
		/*
		 *while循环不会死循环：
		 *1.当找的位置为空，跳出；
		 *2.当走回起点，跳出；
		 *如果条件1一直不能满足，那2必然可以满足。index增长函数：index = index + i^2; 只要满足(index + i^2）% size = index就满足条件2，
		 *上式即：C*size + index = index + i^2;(c为常数) --> C*size = i^2;当条件1不能满足时，极端情况下，i=size，C*size = size^2必然成立。
		 *所以条件2满足，while不会死循环。
		 * */
		while(_table[index]._sta != EMPTY)
		{
			if(_table[index]._sta==EXIST && _table[index]._key==key)
				return &_table[index];
			else
			{
				++i;
				index = (index+ (i*i))%_table.size();
				
				if(index == begin) //走回起点；
					break;
			}
		}

		return NULL;

	}

	bool Remove(const K& key)
	{
		Node* del = Find(key);
		if(del)
		{
			del->_sta = DELETE;
		}
		--_size;
		return false;
	}

	void Print()
	{
		int size = _table.size();
		for(int i = 0; i<size; ++i)
		{
			if(_table[i]._sta == EXIST)
				cout << i <<":key->" << _table[i]._key << " value->" << _table[i]._value << "	";
			else
				cout << i << ":NULL ";
			if(i%5 == 0)
				cout << endl;
		}
		cout << endl;
	}
protected:
	size_t _HashFunc(const K& key)
	{
		HashFunc hf;
		return hf(key) % _table.size();
	}
	
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

	void _CheckSize()
	{
		if((_size*10)/(_table.size()*10) >= 7) // 负载因子>=0.7开辟空间
		{
			size_t newSize = _GetPrimeSize(_table.size());

			HashTable newhs;
			newhs._table.resize(newSize);
			for(size_t i=0; i<_table.size(); ++i)
			{
				newhs.Insert(_table[i]._key, _table[i]._value);
			}
			swap(_table, newhs._table);
		}
	}

protected:
	vector<Node> _table;
	size_t _size;
};
