#pragma once
#include "Stack.h"
#include "Queue.h"
template<typename T>
struct BinNode
{
	T data;
	BinNode<T>* parent;
	BinNode<T>* lChild;
	BinNode<T>* rChild;
	int height;
	BinNode<T>() : parent(nullptr), lChild(nullptr), rChild(nullptr), height(0) {}
	BinNode<T>(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0)
		: data(e), parent(p), lChild(lc), rChild(rc), height(h) {}

	int size();//返回子树节点数量
	BinNode<T>* insertAsLC(T const&);
	BinNode<T>* insertAsRC(T const&);
	template<typename VST> void travPre(VST&);
	template<typename VST> void travPost(VST&);
	template<typename VST> void travIn(VST&);
	template<typename VST> void travLevel(VST&);
};

template<typename T>
template<typename VST> 
void BinNode<T>::travPre(VST& visit)
{
	switch (rand() % 3)
	{
		case 0:travPre_R(this, visit); break;
		case 1:travPre_I1(this, visit); break;
		case 2:travPre_I2(this, visit); break;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST& visit)
{
	switch (rand() % 3)
	{
		case 0:travIn_R(this, visit); break;
		case 1:travIn_I1(this, visit); break;
		case 2:travIn_I2(this, visit); break;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST& visit)
{
	switch (rand() % 2)
	{
	case 0:travPost_R(this, visit); break;
	case 1:travPost_I1(this, visit); break;
	}
}


template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit)
{
	switch (rand() % 1)
	{
		case 0:travLevel(this, visit); break;
	}
}

//先、中、后遍历递归版本
template<typename T, typename VST>
void travPre_R(BinNode<T>* x, VST& visit)	
{
	if (!x)
	{
		return;
	}
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}

template<typename T, typename VST>
void travIn_R(BinNode<T>* x, VST& visit)
{
	if (!x)
	{
		return;
	}
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

template<typename T, typename VST>
void travPost_R(BinNode<T>* x, VST& visit)
{
	if (!x)
	{
		return;
	}
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}


//先、中、后遍历迭代（iteration）版本
template<typename T, typename VST>			//先序遍历
void travPre_I1(BinNode<T>* x, VST& visit)  //先序version 1
{
	Stack<BinNode<T>*> S;
	S.push(x);
	while (!S.empty())
	{
		x = S.pop();
		while (x != nullptr)
		{
			visit(x->data);
			if (x->rChild != nullptr)
			{
				S.push(x->rChild);
			}
			x = x->lChild;
		}
	}
}

template<typename T, typename VST>
void travPre_I2(BinNode<T>* x, VST& visit)	//先序version 2
{
	Stack<BinNode<T>*> S;
	S.push(x);
	while (!S.empty())
	{
		x = S.pop();
		visit(x->data);
		if (x->rChild != nullptr)
		{
			S.push(x->rChild);
		}
		if (x->lChild != nullptr)
		{
			S.push(x->lChild);
		}
	}
}

template<typename T, typename VST>			//中序遍历一句话：利用栈先到左底，回退栈莫忘右子树的遍历
void travIn_I1(BinNode<T>* x, VST& visit)
{
	Stack<BinNode<T>*> S;
	while (true)
	{
		while (x != nullptr)
		{
			if (x != nullptr)
			{
				S.push(x);
			}
			x = x->lChild;
		}
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rChild;
	}
}			

template<typename T, typename VST>
void travIn_I2(BinNode<T>* x, VST& visit)
{
	Stack<BinNode<T>*> S;
	while (true)
	{
		if (x)
		{
			S.push(x);
			x = x->lChild;
		}
		else if (!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rChild;
		}
		else break;
	}
}

template<typename T, typename VST>
void travPost_I1(BinNode<T>* x, VST& visit)
{
	Stack<BinNode<T>*> S;
	S.push(x);
	while (!S.empty())
	{
		if (S.top() != x->parent)
		{
			gotoHLVFL(S);
		}
		x = S.pop();
		visit(x->data);
	}
}

template<typename T>
void gotoHLVFL(Stack<BinNode<T>*>& S)
{
	while (BinNode<T>* x = S.top())
	{
		if (x->lChild != nullptr)
		{
			if (x->rChild != nullptr)
			{
				S.push(x->rChild);
			}
			S.push(x->lChild);
		}
		else
			S.push(x->rChild);
	}
	S.pop();
}

//按层次遍历
template<typename T, typename VST>
void travLevel(BinNode<T>* x, VST& visit)
{
	Queue<BinNode<T>*> Q;
	Q.enqueue(x);
	while (!Q.empty())
	{
		x = Q.dequeue();
		visit(x);
		if (!(x->lChild))
		{
			Q.enqueue(x->lChild);
		}
		if (!(x->rChild))
		{
			Q.enqueue(x->rChild);
		}
	}
}

template<typename T>
int BinNode<T>::size()
{
	return checkSize(lChild) + checkSize(rChild);
}

template<typename T>
int checkSize(BinNode<T>* node)
{
	if (node != nullptr)
	{
		return 1 + checkSize(node->lChild) + checkSize(node->rChild);
	}
	return 0;
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(T const& e)
{
	return lChild = new BinNode(e, this);
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(T const& e)
{
	return rChild = new BinNode(e, this);
}
