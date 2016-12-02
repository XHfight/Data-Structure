/*************************************************************************
	> File Name: Graph.h
	> Author: XH
	> Mail: X_H_fight@163.com 
	> Created Time: Sat 26 Nov 2016 07:53:42 PM CST
 ************************************************************************/

#pragma once
#include "Heap.h"
#include "UnionFind.h"
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
	GraphList(bool isDirected = false)
	:_isDirected(isDirected)
	{}

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

	//求最小生成树
	//贪心算法：局部最优，不一定全局最优。Kruskal和Prim算法
	
	//Kruskal算法针对无向连通图求他的最小生成树
	//思路：选出一条具有最小权值，且两端点不在同一集合中（保证不构成回路），则加入生成树。
	bool Kruskal(GraphList<V, W>& minTree)
	{
		assert(_isDirected == false);
		//初始化minTree
		//初始化顶点数组
		for(int i = 0; i < _vertex.size(); ++i)
		{
			minTree._vertex.push_back(_vertex[i]);
		}
		//初始化边数组
		_list.resize(_vertex.size());
		
		//利用小堆选最小边
		struct EdgeCompare
		{
			bool operator()(const Node* l, const Node* r) const
			{
				return l->_weight < r->_weight;
			}
		};

		Heap<Node*, EdgeCompare> minHeap;
		for(int i = 0; i < _list.size(); ++i)
		{
			Node* cur = _list[i];
			while(cur)
			{
				minHeap.Push(cur);
				cur = cur->_next;
			}
		}
		
		//选出最小权值边插入最小生成树集合，判断两端点不在同一集合中，利用并查集
		
		int edgeNum  = 0; //
		while(edgeNum < _vertex.size()-1)
		{
			if(minHeap.Empty())
			{
				return false;
			}

			Node* min = minHeap.Top();
			minHeap.Pop();
			
			//检查两端点是否在同一集合：并查集中，两端点的根是否相同
			UnionFind uf(_vertex.size());
			size_t root1 = uf.FindRoot(min->_src);
			size_t root2 = uf.FindRoot(min->_dst);
			if(root1 != root2)
			{
				_Insert(min->_src, min->_dst, min->_weight);
				uf.Union(min->_src, min->_dst);
				++edgeNum;
			}
		}
		return true;
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
