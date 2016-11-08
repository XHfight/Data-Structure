/*************************************************************************
	> File Name: BloomFilter.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Tue 08 Nov 2016 10:02:38 AM CST
 ************************************************************************/

#pragma once
#include "BitMap.h"
#include<string>
#include<iostream>
using namespace std;

struct __HashFunc1
{

	size_t BKDRHash(const char *str)  
	{  
		 register size_t hash = 0;  
		 while (size_t ch = (size_t)*str++)  
		 {         
			 hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
		 }
		return hash;
	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

struct __HashFunc2
{
	size_t SDBMHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash = 65599 * hash + ch;         
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
	    }  
		return hash;  
	}
	
	size_t operator()(const string& str)
	{
		return SDBMHash(str.c_str());
	}
};

struct __HashFunc3
{
	size_t RSHash(const char *str)  
	{  
		register size_t hash = 0;  
	    size_t magic = 63689;   
		while (size_t ch = (size_t)*str++)  
		{  
			hash = hash * magic + ch;  
			magic *= 378551;  
		}  
		return hash;  
	} 

	size_t operator()(const string& str)
	{
		return RSHash(str.c_str());
	}
};
struct __HashFunc4
{
	size_t APHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t ch;  
		for (long i = 0; ch = (size_t)*str++; i++)  
		{  
			if ((i & 1) == 0)  
			{  
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
			}  
			else  
			{  
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
			}  
		}  
		return hash;  
	}

	size_t operator()(const string& str)
	{
		return APHash(str.c_str());
	} 
};

struct __HashFunc5
{
	size_t JSHash(const char *str)  
	{  
		if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;  
	    register size_t hash = 1315423911;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash ^= ((hash << 5) + ch + (hash >> 2));  
		}  
		return hash;  
	}  

	size_t operator()(const string& str)
	{
		return JSHash(str.c_str());
	}
};

template< class K = string,
	class HashFunc1 = __HashFunc1,
	class HashFunc2 = __HashFunc2,
	class HashFunc3 = __HashFunc3,
	class HashFunc4 = __HashFunc4,
	class HashFunc5 = __HashFunc5 >

class BloomFilter
{
public:
	BloomFilter(size_t num)
		:_bitmap(num*5) //设定每个key值映射5个位置
		 ,_size(num*5)
	{}

	void Set(const K& key)
	{
		_bitmap.Set(HashFunc1()(key)%_size);
		_bitmap.Set(HashFunc2()(key)%_size);
		_bitmap.Set(HashFunc3()(key)%_size);
		_bitmap.Set(HashFunc4()(key)%_size);
		_bitmap.Set(HashFunc5()(key)%_size);
	}

	void Reset(const K& key)
	{
		//引用计数实现
	}

	bool Test(const K& key)
	{
		if(_bitmap.Test(HashFunc1()(key)%_size) == false)
			return false;
		if(_bitmap.Test(HashFunc2()(key)%_size) == false)
			return false;
		if(_bitmap.Test(HashFunc3()(key)%_size) == false)
			return false;
		if(_bitmap.Test(HashFunc4()(key)%_size) == false)
			return false;
		if(_bitmap.Test(HashFunc5()(key)%_size) == false)
			return false;
		return true;
	}
protected:
	BitMap _bitmap;
	size_t _size;
};
