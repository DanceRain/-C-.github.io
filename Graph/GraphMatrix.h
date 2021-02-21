#pragma once
#include "Graph.h"
#include <vector>
#include <iostream>

template<typename Tv> struct Vertex
{
	Tv data;		//���������㣨ʵ������������)
	VStatus status;
	explicit Vertex(const Tv& _data) :
		data(_data),
		status(UNDISCOVERED)
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
	//���typename����n����eΪGraph�ж�������͡�����using e = int;
	typename Graph<Tv, Te>::e;
	typename Graph<Tv, Te>::n;

	GraphMatrix()
	{
		n = e = 0;
	}

	~GraphMatrix() {
		for (int i = 0; i != n; ++i)
		{
			for (int j = 0; j != n; ++j)
			{
				delete E[i][j];
			}
		}
	}

	/*�����*/
	virtual int insertVertex(const Tv& data) override {
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
		return V[i].data;
	}
	
	virtual VStatus& vertexStatus(int i) override {
		return V[i].status;
	}

	/*�߲���*/
	virtual void insertEdge(const Te& edgeData, int w, int i, int j) override {
		E[i][j] = new Edge<Te>(edgeData, w);
		++e;
	}

	virtual Te removeEdge(int i, int j) override {
		Te data = E[i][j]->data;
		delete E[i][j];
		E[i][j] = nullptr;
		--e;
		return data;
	}

	virtual Te edgeData(int i, int j) override {
		Te data = E[i][j]->data;
		return data;
	}

	virtual bool isEdgeExist(int i, int j) override {
		if (Graph<Tv, Te>::isOutOfBoundary(i) || Graph<Tv, Te>::isOutOfBoundary(j) || E[i][j] == nullptr)
		{
			return false;
		}
		return true;
	}

private:
	std::vector<Vertex<Tv>> V;
	std::vector<std::vector<Edge<Te>*>> E;
};
