#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> struct ListNode
{
	T data;
	ListNode* prev = nullptr;
	ListNode* succ = nullptr;

	ListNode() = default;
	ListNode(T e, ListNode* p = nullptr, ListNode* s = nullptr) :data(e), prev(p), succ(s) {}

	ListNode* insertAsPrev(const T& elem);
	ListNode* insertAsSucc(const T& elem);
};

template <typename T> ListNode<T>* ListNode<T>::insertAsPrev(const T& elem)
{
	ListNode<T>* x = new ListNode(elem, prev, this);
	prev->succ = x;
	prev = x;
	return x;
}

template <typename T> ListNode<T>* ListNode<T>::insertAsSucc(const T& elem)
{
	ListNode<T>* x = new ListNode(elem, this, succ);
	succ->prev = x;
	succ = x;
	return x;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ListNode<T>& elem)
{
	os << elem.data;
	return os;
}
