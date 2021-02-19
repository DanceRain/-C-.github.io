#pragma once
#include "Graph.h"
#include <vector>
#include <iostream>

template<typename Tv> struct Vertex
{
	Tv data;		//用于描述点（实例：城市名称
	explicit Vertex(const Tv& _data) :
		data(_data)
	{
	}
};

template<typename Te> struct Edge
{
	Te data;		//可以用于描述边（实例：路的名称）
	int weight;		//边的权重（扩展到实例就是路的长度等）
	Edge(const Te& _data, int _weight) :
		data(_data),
		weight(_weight)
	{
	}
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
public:
	using Graph<Tv, Te>::e;
	using Graph<Tv, Te>::n;
	GraphMatrix() {
		n = e = 0;
	}
	~GraphMatrix() {
		for (int i = 0; i != n; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				delete Edge[i][j];
			}
		}
	}

	/*点操作*/
	int insertVertex(const Tv& data) override {
		/*添加顶点*/
		V.push_back(Vertex<Tv>(data));
		++n;

		/*为该顶点添加与其它顶点的预留边*/
		E.push_back(std::vector<Edge<Te>*>(n, nullptr));
		for (int i = 0; i != n - 1; ++i)
		{
			E[i].push_back(nullptr);
		}

		return n;
	}

	virtual Tv removeVertex(int i) override {
		judgeVertexsBoundary(i);
		/*删除顶点*/
		Tv delData = V[i].data;
		V.erase(V.cbegin() + i);
		--n;

		/*删除矩阵中对应的边*/
		E.erase(E.cbegin() + i);
		for (int vertexFlag = 0; vertexFlag != n; ++vertexFlag)
		{
			E[vertexFlag].erase(E[vertexFlag].cbegin() + i);
		}

		return delData;
	}

	virtual Tv vertexData(int i) override {
		judgeVertexsBoundary(i);
		return V[i].data;
	}

	/*边操作*/
	virtual int insertEdge(const Te& edgeData, int w, int i, int j) override {
		E[i][j] = new Edge<Te>(edgeData, w);
	}

	virtual Te removeEdge(int i, int j) override {
		Te data = E[i][j].data;
		delete E[i][j];
		E[i][j] = nullptr;
		return data;
	}


private:
	void judgeVertexsBoundary(int i) {
		if (i < 0 || i >= V.size())
		{
			std::cout << "overstep the boundary" << std::endl;
		}
	}

	std::vector<Vertex<Tv>> V;
	std::vector<std::vector<Edge<Te>*>> E;
};
