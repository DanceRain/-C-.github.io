#pragma once

template<typename Tv, typename Te>
class Graph
{
public:
	/*�������*/
	virtual int insertVertex(const Tv&) = 0;
	virtual Tv removeVertex(int i) = 0;
	virtual Tv vertexData(int i) = 0;

	/*�߲���*/
	virtual int insertEdge(const Te&, int w, int i, int j) = 0;
	virtual int removeEdge(int i, int j) = 0;
protected:
	int n;	//������
	int e;	//����
};
