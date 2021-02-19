#pragma once
#include "Graph.h"
#include <vector>
#include <iostream>

template<typename Tv> struct Vertex
{
	Tv data;		//���������㣨ʵ������������
	explicit Vertex(const Tv& _data) :
		data(_data)
	{
	}
};

template<typename Te> struct Edge
{
	Te data;		//�������������ߣ�ʵ����·�����ƣ�
	int weight;		//�ߵ�Ȩ�أ���չ��ʵ������·�ĳ��ȵȣ�
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

	/*�����*/
	int insertVertex(const Tv& data) override {
		/*��Ӷ���*/
		V.push_back(Vertex<Tv>(data));
		++n;

		/*Ϊ�ö�����������������Ԥ����*/
		E.push_back(std::vector<Edge<Te>*>(n, nullptr));
		for (int i = 0; i != n - 1; ++i)
		{
			E[i].push_back(nullptr);
		}

		return n;
	}

	virtual Tv removeVertex(int i) override {
		judgeVertexsBoundary(i);
		/*ɾ������*/
		Tv delData = V[i].data;
		V.erase(V.cbegin() + i);
		--n;

		/*ɾ�������ж�Ӧ�ı�*/
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

	/*�߲���*/
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
