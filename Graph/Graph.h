#pragma once
#include <queue>

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;

template<typename Tv, typename Te>
class Graph
{
public:
	//��Ϊ������Ҫִ���������麯�������ҲҪ�����麯���ṩһ�����塣
	virtual ~Graph() = 0
	{

	}
	/*��λ����*/
	void reset()
	{
		for (int i = 0; i < n; ++i)
		{
			vertexStatus(i) = UNDISCOVERED;
		}
	}

	/*�������*/
	virtual int insertVertex(const Tv&) = 0;
	virtual Tv removeVertex(int i) = 0;
	virtual Tv vertexData(int i) = 0;
	virtual VStatus& vertexStatus(int i) = 0;

	/*�߲���*/
	virtual void insertEdge(const Te&, int w, int i, int j) = 0;
	virtual Te removeEdge(int i, int j) = 0;
	virtual Te edgeData(int i, int j) = 0;
	virtual bool isEdgeExist(int i, int j) = 0;

	/*��������*/
	void dfs(int i)
	{
		int j = i;
		do
		{
			if (vertexStatus(j) == UNDISCOVERED)
			{
				DFS(j);
			}
			++j;
			j = j % n;
		} while (j != i);
	}

	void bfs(int i)
	{
		int j = i;
		do
		{
			if (vertexStatus(j) == UNDISCOVERED)
			{
				BFS(j);
			}
			++j;
			j = j % n;
		} while (j != i);
	}

protected:
	int n;	//������
	int e;	//����

	bool isOutOfBoundary(int i) {
		if (i < 0 || i >= n)
		{
			std::cout << "overstep the boundary" << std::endl;
			return true;
		}
		return false;
	}

private:
	void DFS(int i)
	{
		vertexStatus(i) = DISCOVERED;
		for (int j = 0; j < n; ++j)
		{
			//�����Ի�����س��֣������ i != j��
			//���ñߴ��ڣ���ָ��������ȱ���
			if (isEdgeExist(i, j) && vertexStatus(j) == UNDISCOVERED)
			{
				DFS(j);
			}
		}
		std::cout << vertexData(i) << std::endl;
		vertexStatus(i) = VISITED;
	}

	void BFS(int i)
	{
		std::queue<int> queueVertex;
		queueVertex.push(i);
		while (!queueVertex.empty())
		{
			int vertexNum = queueVertex.front();
			queueVertex.pop();
			vertexStatus(vertexNum) = DISCOVERED;

			for (int j = 0; j < n; ++j)
			{
				if (isEdgeExist(vertexNum, j) && vertexStatus(j) == UNDISCOVERED)
				{
					vertexStatus(j) = DISCOVERED;
					queueVertex.push(j);
				}
			}

			std::cout << vertexData(vertexNum) << std::endl;
			vertexStatus(vertexNum) = VISITED;
		}
	}
};
