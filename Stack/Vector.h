#pragma once
#include <initializer_list>
#include <time.h>
#define DEFAULT_CAPACITY 3
typedef int Rank;

template<typename T> class Vector
{
public:
	typedef T* iterator;

	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0):_elem(nullptr), _size(0), _capacity(c)
	{
		_elem = new T[c];
		for (; _size != s; ++_size)
		{
			_elem[_size] = v;
		}
	}
	Vector(std::initializer_list<T> list):_elem(new T[list.size()]), _size(0), _capacity(list.size())
	{
		for (; _size != _capacity; ++_size)
		{
			_elem[_size] = *(list.begin() + _size);
		}
	}
	Vector(const Vector& V) { copyFrom(V._elem, 0, V.size()); }
	Vector(const T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(iterator lo, iterator he);
	Vector(const T* A, Rank n) { copyFrom(A, 0, n); }

	const Vector& operator=(const Vector& V);
	T& operator[](Rank r)const;
	
	~Vector() { delete []_elem;}

	Rank size() const { return _size; }
	iterator begin() { return _elem; }
	iterator end() { return _elem + _size; }
	iterator cbegin() const { return _elem; }
	iterator cend()const { return _elem + _size; }
	void push_back(const T& e);
	Rank insert(Rank r, const T& e);
	T remove(Rank r) { T e = _elem[r]; remove(r, r + 1); return e; }
	int remove(Rank lo, Rank hi);
	Rank find(const T& e) const { return find(e, 0, _size); }
	Rank find(const T& e, Rank lo, Rank hi)const;
	void unsort() { unsort(0, _size); };
	void unsort(Rank lo, Rank hi);
	int deduplicate();
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	Rank search(const T& e, Rank lo, Rank hi);
	Rank search(const T& e) { return search(e, 0, _size); }
protected:
	void copyFrom(const T* A, Rank lo, Rank hi);
	/*Àı»›¿©»›*/
	void expand();
	void shrink();
	/*√∞≈›≈≈–Ú*/
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	/*πÈ≤¢≈≈–Ú*/
	void merge(Rank lo, Rank mi, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	int binarySearch(const T& e, Rank lo, Rank hi);

private:
	T* _elem;
	Rank _size;
	int _capacity;
};

template<typename T> 
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
	_capacity = hi - lo;
	_elem = new T[_capacity];
	
	for (_size = 0; _size != _capacity; ++_size)
	{
		_elem[_size] = A[lo + _size];
	}
}

template<typename T>
Vector<T>::Vector(iterator lo, iterator he)
{
	_capacity = he - lo;
	_elem = new T[_capacity];
	for (_size = 0; _size != _capacity; ++_size)
	{
		_elem[_size] = *(lo + _size);
	}
}

template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector& V)
{
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
T& Vector<T>::operator[](Rank r)const
{
	if (r >= _size)
	{
		throw std::out_of_range("the access is in");
	}
	return _elem[r];
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
	{
		return;
	}

	T* _oldElem = _elem;
	_elem = new T[_capacity * 2];
	if (_elem)
	{
		for (int i = 0; i != _size; ++i)
		{
			_elem[i] = _oldElem[i];
		}
	}
	else
	{
		std::runtime_error("the memory is full");
	}
	delete[]_oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
	if (_size > (_capacity >> 2))
	{
		return;
	}
	T* _oldElem = _elem;
	_elem = new T[_capacity >> 2];
	if (_elem)
	{
		for (int i = 0; i != _size; ++i)
		{
			_elem[i] = _oldElem[i];
		}
	}
	else
	{
		std::runtime_error("the memory is full");
	}
	delete []_oldElem;
}

template<typename T>
void Vector<T>::push_back(const T& e)
{
	expand();
	_elem[_size++] = e;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();
	for (int i = _size; i != r; --i)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	++_size;
	return r;
}

/*Œﬁ–Ú»›∆˜≤È’“*/
template<typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi)const
{
	for (int i = hi; i != lo; --i)
	{
		if (_elem[i - 1] == e)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
	{
		return 0;
	}
	while (hi != _size)
	{
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	srand(time(NULL));
	while (lo != hi)
	{
		std::swap(_elem[hi - 1], _elem[lo + (rand() % (hi - lo))]);
		--hi;
	}
}

template<typename T>
int Vector<T>::deduplicate()
{
	int oldsize = _size;
	for (int i = 1; i != _size; )
	{
		if (find(_elem[i], 0, i) != -1)
		{
			remove(i);
		}
		else
		{
			++i;
		}
	}
	return oldsize - _size;
}

/*√∞≈›*/
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi));
}
template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool judge = true;
	while (++lo < hi)
	{
		if (_elem[lo] < _elem[lo - 1])
		{
			judge = false;
			std::swap(_elem[lo], _elem[lo - 1]);
		}
	}
	return judge;
}


/*πÈ≤¢*/
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (lo == hi - 1)
	{
		return;
	}
	Rank mid = (lo + hi) >> 1;
	mergeSort(lo, mid);
	mergeSort(mid, hi);
	merge(lo, mid, hi);
}
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	Rank leftSize = mi - lo;
	Rank rightSize = hi - mi;
	T* A = _elem + lo;

	T* leftElem = new T[leftSize];
	for (int i = 0; i != leftSize; ++i)
	{
		leftElem[i] = A[i];
	}
	T* rightElem = _elem + mi;

	for (int i = 0, j = 0, k = 0; (i < leftSize) || (j < rightSize);)
	{
		if ((i < leftSize) && ((leftElem[i] <= rightElem[j]) || !(j < rightSize)))
		{
			A[k++] = leftElem[i++];
		}
		if ((j < rightSize) && ((rightElem[j] <= leftElem[i]) || !(i < leftSize)))
		{
			A[k++] = rightElem[j++];
		}
	}
	delete[]leftElem;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 2)
	{
	case 0:mergeSort(lo, hi); break;
	case 1:bubbleSort(lo, hi); break;
	}
}

template<typename T>
int Vector<T>::binarySearch(const T& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mid = (lo + hi) >> 1;
		e < _elem[mid] ? hi = mid : lo = mid + 1;
	}
	return --lo;
}

template<typename T>
int Vector<T>::search(const T& e, Rank lo, Rank hi)
{
	switch (rand()%1)
	{
	case 0:return binarySearch(e, lo, hi); break;
	}
}


