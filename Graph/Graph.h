/*************************************************************************
	> File Name: Graph.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sat 26 Nov 2016 07:53:42 PM CST
 ************************************************************************/

#pragma once
#include <queue>
#include <stdio.h>
#include <vector>
#include <stdexcept>
#include<iostream>
#include <string>
using namespace std;

//图的邻接矩阵存储
template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex, size_t size, bool isDirected = false, const W& illegal = W())
	:_vertex(new V[size])
	 ,_size(size)
	 ,_matrix(new W*[size])
	 ,_isDirected(isDirected)
	{
		for(int i = 0; i < _size; ++i)
		{
			_matrix[i] = new W[_size];
			_vertex[i] = vertex[i];
		}

		for(int i = 0; i < _size; ++i)
		{
			for(int j = 0 ; j < _size; ++j)
			{
				_matrix[i][j] = illegal;
			}
		}
	}

	~GraphMatrix()
	{
		delete[] _vertex;
		for(int i = 0; i < _size; ++i)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}

	void InsertArc(const V& src, const V& dst, const W& w) //添加边，权重为w
	{
		size_t srcIndex = GetIndex(src);
		size_t dstIndex = GetIndex(dst);

		_matrix[srcIndex][dstIndex] = w;
		if(_isDirected == false)
		{
			_matrix[dstIndex][srcIndex] = w;
		}
	}

	void Print()
	{
		for(size_t i = 0; i < _size; ++i)
		{
			cout << _vertex[i] << ":";
			for(size_t j = 0; j < _size; ++j)
			{
				cout << _matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
protected:
	size_t GetIndex(const V& v)
	{
		for(size_t i = 0; i < _size; ++i)
		{
			if(_vertex[i] == v)
				return i;
		}
		throw::invalid_argument("参数错误");
	}
protected:
	V* _vertex; //存储结点的数组
	W** _matrix; //存储边权重的数组
	size_t _size; //结点个数
	bool _isDirected; //是否为有向图
};

//图的邻接表存储
template<class W>
struct GraphListNode
{
	size_t _src; //为了以后实现最小生成树更简单而设计
	size_t _dst;
	W _weight;
	GraphListNode<W>* _next;

	GraphListNode(size_t src = 0, size_t dst = 0, const W& w = W())
	:_src(src)
	,_dst(dst)
	,_weight(w)
	,_next(NULL)
	{}
};

template<class V, class W>
class GraphList
{
	typedef GraphListNode<W> Node;
public:
	GraphList(V* vertex, size_t size, bool isDirected = false)
	 :_isDirected(isDirected)
	{
		for(int i = 0; i < size; ++i)
		{
			_vertex.push_back(vertex[i]);
		}
		_list.resize(size);
	}

	~GraphList()
	{
		for(int i = 0 ; i < _vertex.size(); ++i)
		{
			Node* cur = _list[i];
			while(cur)
			{
				Node* del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
	void InsertArc(const V& src, const V& dst, const W& w) //添加边， 权重为w
	{
		size_t srcIndex = GetIndex(src);
		size_t dstIndex = GetIndex(dst);
		
		_Insert(srcIndex, dstIndex, w);
		if(_isDirected == false)
			_Insert(dstIndex, srcIndex, w);
	}

	void Print()
	{
		for(int i = 0 ; i < _vertex.size(); ++i)
		{
			cout << _vertex[i] << ":";
			Node* cur = _list[i];
			while(cur)
			{
				cout << _vertex[cur->_dst] << "[" << cur->_weight << "]->";
				cur = cur->_next;
			}
			cout << "NULL" <<endl;
		}
		cout << endl;
	}
	
	//深度优先遍历
	void DFSTraverse(const V& v)
	{
		size_t index = GetIndex(v);
		vector<bool> visited(_vertex.size(), false); //记录该顶点是否访问过
		_DFS(index , visited);
		cout << "NULL" <<endl;
	}

	//广度优先遍历
	void BFSTraverse(const V& v)
	{
		size_t srcIndex = GetIndex(v);
		vector<bool> visited(_vertex.size(), false);
		queue<size_t> visitIndex;  //保存要访问的结点
	    visitIndex.push(srcIndex);
		visited[srcIndex] = true; //注意：只要入队就要将它标记为已访问

		while(!visitIndex.empty())
		{
			size_t i = visitIndex.front();
			cout << _vertex[i] << "->";
			visitIndex.pop();
			

			Node* cur = _list[i];
			while(cur)
			{
				if(visited[cur->_dst] == false)
				{
					visitIndex.push(cur->_dst);
					visited[cur->_dst] = true;
				}
				cur = cur->_next;
			}
		}
		cout << "NULL" << endl;
	}
protected:
	void _DFS(size_t index, vector<bool>& visited)
	{
		cout << _vertex[index] << "->";
		visited[index] = true;
		Node* cur = _list[index];
		while(cur)
		{
			if(visited[cur->_dst] == false)
				_DFS(cur->_dst, visited);
			cur = cur->_next;
		}
	}

	void _Insert(size_t src, size_t dst, const W& w)
	{
		Node* node = new Node(src, dst, w);
		node->_next = _list[src];
		_list[src] = node;
	}

	size_t GetIndex(const V& v)
	{
		for(int i = 0 ; i < _vertex.size(); ++i)
		{
			if(_vertex[i] == v)
				return i;
		}
		throw::invalid_argument("参数错误");
	}
protected:
	vector<V> _vertex;  //存储结点的数组
	vector<Node*> _list;//存储结点关系的邻接表
						//这里不需要size，直接用vector求size
	bool _isDirected;	//是否为有向图
	
};
