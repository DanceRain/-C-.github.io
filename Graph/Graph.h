#pragma once

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;

template<typename Tv, typename Te>
class Graph
{
public:
	//��Ϊ������Ҫִ���������麯�������ҲҪ�����麯���ṩһ�����塣
	virtual ~Graph() = 0
	{

	}

	/*�������*/
	virtual int insertVertex(const Tv&) = 0;
	virtual Tv removeVertex(int i) = 0;
	virtual Tv vertexData(int i) = 0;

	/*�߲���*/
	virtual void insertEdge(const Te&, int w, int i, int j) = 0;
	virtual Te removeEdge(int i, int j) = 0;
	virtual Te edgeData(int i, int j) = 0;

	/*��������*/
	virtual void DFS(int i) = 0;
	virtual void BFS() = 0;

	

protected:
	int n;	//������
	int e;	//����
};
