#pragma once
#include "BinNode.h"
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define IsExist(x) ((x) != nullptr)
#define IsLC(x) ((x)->parent->lChild == (x))
#define IsRC(x) ((x)->parent->rChild == (x))
#define JudgeNode(x) (!((x)->parent) ? _root : (IsLC(x) ? ((x)->parent->lChild):((x)->parent->rChild)))


template<typename T> class BinTree;
template<typename T> void EmptyTree(BinTree<T>* tree);

template<typename T>
class BinTree
{
	friend void EmptyTree<T>(BinTree<T>* tree);
public:
	BinTree():_size(0), _root(nullptr){}
	BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);
	BinNode<T>* insertAsRoot(const T& e);
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>*& S);
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>*& S);
	int remove(BinNode<T>* x);

	BinNode<T>* root() const { return _root; }
	
	template<typename VST>
	void travPre(VST& visit) { if(_root)_root->travPre(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }
	template<typename VST>
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }

protected:
	int _size;
	BinNode<T>* _root;
	void updateHeight(BinNode<T>* node);
};

template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, const T& e)
{
	if (!(x != nullptr))
	{
		return nullptr;
	}
	x->insertAsLC(e);
	++_size;
	updateHeight(x);
	return x->lChild;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, const T& e)
{
	if (!(x != nullptr))
	{
		return nullptr;
	}
	x->insertAsRC(e);
	++_size;
	updateHeight(x);
	return x->rChild;
}

template<typename T>
void BinTree<T>::updateHeight(BinNode<T>* node)
{
	while (IsExist(node))
	{
		if (IsExist(node->lChild) && IsExist(node->rChild))
		{
			node->height = 1 + MAX(node->lChild->height, node->rChild->height);
		}
		else if (IsExist(node->lChild))
		{
			node->height = 1 + node->lChild->height;
		}
		else
		{
			node->height = 1 + node->rChild->height;
		}
		node = node->parent;
	}
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(const T& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &S)
{
	if (S == nullptr)
	{
		return nullptr;
	}
	_size += S->_size;
	S->_root->parent = x;
	x->lChild = S->_root;
	updateHeight(x);
	EmptyTree(S);
	S = nullptr;
	return x;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &S)
{
	if (S == nullptr)
	{
		return nullptr;
	}
	_size += S->_size;
	S->_root->parent = x;
	x->rChild = S->_root;
	updateHeight(x);
	EmptyTree(S);
	S = nullptr;
	return x;
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
	if (!IsExist(x))
	{
		return -1;
	}
	JudgeNode(x) = nullptr;
	updateHeight(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template<typename T>
int removeAt(BinNode<T>* x)
{
	if (nullptr == x)
	{
		return 0;
	}
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x);
	return n;
}

template<typename T>
void release(BinNode<T>* node)   //删除该节点孩子指针指向的资源
{
	if (nullptr == node)
	{
		return;
	}
	delete node;
}

template<typename T>
void EmptyTree(BinTree<T>* tree)	//置空树中所有的指针
{
	//EmptyNode(tree->_root);
	tree->_root = nullptr;
	tree->_size = 0;
}
