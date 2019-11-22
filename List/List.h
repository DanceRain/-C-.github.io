#pragma once
#include "ListNode.h"
#include <time.h>

template<typename T> struct ListNode;

template<typename T> class List
{
	
public:
	using Rank = size_t;
	List() { init(); }
	List(const List&);

	ListNode<T>* insertAsFrist(const T& e);
	ListNode<T>* insertAsLast(const T& e);
	ListNode<T>* insertAsBefore(ListNode<T>* p, const T& e);
	ListNode<T>* insertAsAfter(ListNode<T>* p, const T& e);

	Rank remove(Rank lo, Rank he);
	Rank remove(ListNode<T>* lo, ListNode<T>* he);
	T remove(ListNode<T>* p);

	ListNode<T>* find(const T& e, int n, ListNode<T>* p) const;
	ListNode<T>* find(const T& e) const { find(e, _size, _trailer); }
	ListNode<T>* search(const T& e) const { search(e, _size, begin()); }
	ListNode<T>* search(const T& e, int n, ListNode<T>* p) const;

	void print() const;
	void print(const ListNode<T>* lo, const ListNode<T>* hi)const;

	ListNode<T>* begin(){ return _header->succ; }
	ListNode<T>* end(){ return _trailer; }
	const ListNode<T>* cbegin() const{ return _header->succ; }
	const ListNode<T>* cend() const{ return _trailer; }
	int size() { return _size; }

	void sort(ListNode<T>* p, int n);
	void sort() { sort(begin(), _size); }
	void reverse();
	int deduplicate();
	int uniquify();
	ListNode<T>* selectMax(ListNode<T>* p, int n);
	ListNode<T>* selectMax();

	ListNode<T>* operator[](Rank r) const;
	~List();
protected:
	void reverse_1();
	void reverse_2();
	void init();
	void mergeSort(ListNode<T>*& p, int n);
	void merge(ListNode<T>*& lo, int loN, ListNode<T>*& he, int heN);
	void selectionSort(ListNode<T>* p, int n);
	void insertionSort(ListNode<T>* p, int n);
private:
	ListNode<T>* _header = nullptr;
	ListNode<T>* _trailer = nullptr;
	size_t _size = 0;
};

template<typename T>
void List<T>::init()
{
	_header = new ListNode<T>;
	_trailer = new ListNode<T>;
	_header->succ = _trailer;
	_header->prev = nullptr;
	_trailer->succ = nullptr;
	_trailer->prev = _header;
	_size = 0;
}

template<typename T>
ListNode<T>* List<T>::insertAsFrist(const T& e)
{
	ListNode<T>* newElem = new ListNode<T>(e, _header, _header->succ);
	_header->succ->prev = newElem;
	_header->succ = newElem;
	_size++;
	return newElem;
}

template<typename T>
ListNode<T>* List<T>::insertAsLast(const T& e)
{
	ListNode<T>* newElem = new ListNode(e, _trailer->prev, _trailer);
	_trailer->prev->succ = newElem;
	_trailer->prev = newElem;
	_size++;
	return newElem;
}

template<typename T>
ListNode<T>* List<T>::insertAsBefore(ListNode<T>* p, const T& e)
{
	ListNode<T>* newElem = new ListNode<T>(e, p->prev, p);
	p->prev->succ = newElem;
	p->prev = newElem;
	_size++;
	return newElem;
}

template<typename T>
ListNode<T>* List<T>::insertAsAfter(ListNode<T>* p, const T& e)
{
	ListNode<T>* newElem = new ListNode<T>(e, p, p->succ);
	p->succ->prev = newElem;
	p->succ = newElem;
	_size++;
	return newElem;
}

template<typename T>
List<T>::List(const List& L)
{
	ListNode<T>* tmp = L._header->succ;
	while (tmp != L._trailer)
	{
		insertAsLast(tmp->data);
		tmp = tmp->succ;
	}
}

template<typename T> 
List<T>::~List()
{
	ListNode<T>* now = _header->succ;
	while (now != _trailer)
	{
		ListNode<T>* tmp = now;
		now = now->succ;
		delete tmp;
	}
}

template<typename T>
ListNode<T>* List<T>::operator[](Rank r) const
{
	ListNode<T>* tmp = _header->succ;
	for (int i = 0; i != r; ++i)
	{
		tmp = tmp->succ;
	}
	return tmp;
}

template<typename T>
typename List<T>::Rank List<T>::remove(Rank lo, Rank he)
{
	if (lo >= 0 && he <= _size)
	{
		for (Rank i = lo; i != he; ++i)
		{
			ListNode* tmp = (*this)[i];
			remove(tmp);
		}
	}
	return he - lo;
}

template<typename T>
typename List<T>::Rank List<T>::remove(ListNode<T>* lo, ListNode<T>* he)
{
	while (lo != he)
	{
		remove(lo);
		lo = lo->succ;
	}
	return he - lo;
}

template<typename T>
T List<T>::remove(ListNode<T>* p)
{
	T tmpData = p->data;
	p->prev->succ = p->succ;
	p->succ->prev = p->prev;
	delete p;
	--_size;
	return tmpData;
}

template<typename T>
void List<T>::print() const
{
	print(cbegin(), cend());
}

template<typename T>
void List<T>::print(const ListNode<T>* lo, const ListNode<T>* hi) const
{
	while (lo != hi)
	{
		cout << lo->data << " ";
		lo = lo->succ;
	}
	cout << endl;
}

template<typename T>
ListNode<T>* List<T>::find(const T& e, int n, ListNode<T>* p) const
{
	while (n-- > 0)
	{
		if (e == (p = p->prev)->data)
		{
			return p;
		}
	}
	return nullptr;
}

template<typename T>
void List<T>::reverse()
{
	switch (rand() % 2)
	{
	case 0:reverse_1(); break;
	case 1:reverse_2(); break;
	}
	return;
}

template<typename T>
void List<T>::reverse_1()
{
	if (_size < 2) return;
	ListNode<T>* p = _header;
	ListNode<T>* q = _header->succ;
	for (; p != _trailer; p = q, q = p->succ)
	{
		p->succ = p->prev;
		p->prev = q;
	}
	_trailer->succ = _trailer->prev;
	_trailer->prev = nullptr;
	std::swap(_header, _trailer);
}

template<typename T>
void List<T>::reverse_2()
{
	if (_size < 2) { return; }

	for (ListNode<T>* p = _header; p != nullptr; p = p->prev)
	{
		std::swap(p->prev, p->succ);
	}
	std::swap(_header, _trailer);
}

template<typename T>
void List<T>::merge( ListNode<T>*& lo, int loN, ListNode<T>*& he, int heN)
{
	ListNode<T>* pBegin = lo->prev;
	while (0 < heN)
	{
		if (loN != 0 && (lo->data <= he->data))
		{
			if (he == (lo = lo->succ))
			{
				break;
			}
			--loN;
		}
		else
		{
			this->insertAsBefore(lo, remove((he = he->succ)->prev));
			--heN;
		}
	}
	lo = pBegin->succ;
}

template<typename T>
void List<T>::mergeSort(ListNode<T>*& p, int n)
{
	if (n < 2)
	{
		return;
	}
	int mid = n >> 1;
	ListNode<T>* q = p;
	for (int i = 0; i != mid; ++i)
	{
		q = q->succ;
	}
	mergeSort(p, mid);
	mergeSort(q, n - mid);
	merge(p, mid, q, n - mid);
}

template<typename T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* head = p->prev;
	ListNode<T>* trail = p;
	for(int i = 0; i != n; ++i)
	{
		trail = trail->succ;
	}
	while (n > 1)
	{
		ListNode<T>* max = selectMax(head->succ, n);
		insertAsBefore(trail, remove(max));
		--n;
		trail = trail->prev;
	}
}

template<typename T>
void List<T>::insertionSort(ListNode<T>* p, int n)
{
	for (int i = 0; i != n; ++i)
	{
		insertAsAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->prev);
	}
}

template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;
	ListNode<T>* tmp = _header;
	int i = 0;
	while((tmp = tmp->succ) != _trailer)
	{
		ListNode<T>* finder = find(tmp->data, i, tmp);
		if (finder)
		{
			remove(finder);
		}
		else
		{
			++i;
		}
	}
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2)
	{
		return 0;
	}
	int oldSize = _size;
	ListNode<T>* p = begin();
	ListNode<T>* q = begin()->succ;

	for (; q != _trailer; p = q, q = q->succ)
	{
		if (p->data == q->data)
		{
			remove(q);
			q = p;
		}
	}
	return oldSize - _size;
}

template<typename T>
ListNode<T>* List<T>::search(const T& e, int n, ListNode<T>* p) const
{
	while (0 <= (n--))
	{
		if (((p = p->prev)->data) <= e)
		{
			break;
		}
	}
	return p;
}

template<typename T>
void List<T>::sort(ListNode<T>* p, int n)
{
	srand(time(NULL));
	switch (rand() % 1)
	{
	//case 0:insertionSort(p, n); break;
	//case 1:mergeSort(p, n); break;
	case 0:selectionSort(p, n); break;
	}
	return;
}

template<typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	ListNode<T>* max = p;
	for (ListNode<T>* curr = p; n > 1; --n)
	{
		if (((curr = curr->succ)->data) >= max->data)
		{
			max = curr;
		}
	}
	return max;
}
