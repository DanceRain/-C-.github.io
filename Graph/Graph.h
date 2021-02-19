#pragma once

template<typename Tv, typename Te>
class Graph
{
public:
	/*顶点操作*/
	virtual int insertVertex(const Tv&) = 0;
	virtual Tv removeVertex(int i) = 0;
	virtual Tv vertexData(int i) = 0;

	/*边操作*/
	virtual int insertEdge(const Te&, int w, int i, int j) = 0;
	virtual int removeEdge(int i, int j) = 0;
protected:
	int n;	//顶点数
	int e;	//边数
};
