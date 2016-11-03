/*************************************************************************
	> File Name: HashTable.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Wed 02 Nov 2016 07:07:13 PM CST
 ************************************************************************/

#pragma once
#include<iostream>
#include<vector>
using namespace std;

enum Status
{
	EMPTY,
	EXIST,
	DELETE,
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

template<class K, class V>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
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
protected:
	size_t _HashFunc(const K& key)
	{
		return key % _table.size();
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
