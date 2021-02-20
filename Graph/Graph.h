#pragma once

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;

template<typename Tv, typename Te>
class Graph
{
public:
	//因为派生类要执行其基类的虚函数，因此也要给纯虚函数提供一个定义。
	virtual ~Graph() = 0
	{

	}

	/*顶点操作*/
	virtual int insertVertex(const Tv&) = 0;
	virtual Tv removeVertex(int i) = 0;
	virtual Tv vertexData(int i) = 0;

	/*边操作*/
	virtual void insertEdge(const Te&, int w, int i, int j) = 0;
	virtual Te removeEdge(int i, int j) = 0;
	virtual Te edgeData(int i, int j) = 0;

	/*遍历操作*/
	virtual void DFS(int i) = 0;
	virtual void BFS() = 0;

	

protected:
	int n;	//顶点数
	int e;	//边数
};
