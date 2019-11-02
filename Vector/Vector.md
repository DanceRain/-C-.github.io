```c++
#include <iostream>
#include <ctime>

using std::endl;
using std::cout;
using std::cin;
#define DEFAULT_CAPACITY 10
#pragma once

template <typename T> class Vector
{
public:
	Vector(std::initializer_list<T> list);
	Vector() :elem(new T[DEFAULT_CAPACITY]()), idx(0), capacity(10) {}
	~Vector() { delete[]elem; }

​```
void push_back(T number);
void expand();
void unsort(unsigned, unsigned);
void print();
void shrink();
unsigned remove(unsigned, unsigned);
int remove(unsigned);
int find(const T&, unsigned, unsigned);
unsigned deduplicate();
T* begin() { return elem; }
T* end() { return elem + idx; }

size_t getCapacity();
size_t getSize();
T& operator[](unsigned);
​```

private:
	T* elem;
	size_t idx;
	size_t capacity;
};

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list):elem(new T[list.size()])
{
	int i = 0;
	for (auto& rElem : list)
	{
		elem[i] = rElem;
		++i;
	}
	idx = i;
}

template<typename T>
T& Vector<T>::operator[](unsigned i)
{
	return elem[i];
}

template<typename T>
void Vector<T>::unsort(unsigned left, unsigned right)
{
	for (unsigned i = right - left; i > 0; --i)
	{
		std::swap(*(elem + i - 1), *(elem + rand() % i));
	}
}

template<typename T>
void Vector<T>::print()
{
	for (int i = 0; i < idx; ++i)
	{
		cout << elem[i];
	}
	cout << endl;
}

template<typename T>
void Vector<T>::expand()
{
	if (idx < capacity)
	{
		return;
	}
	T* old = elem;
	elem = new T[capacity * 2]();
	for (size_t i = 0; i != capacity; ++i)
	{
		elem[i] = old[i];
	}
	capacity *= 2;
	delete[] old;
}

template<typename T>
size_t Vector<T>::getCapacity()
{
	return capacity;
}

template<typename T>
size_t Vector<T>::getSize()
{
	return idx;
}

template<typename T>
void Vector<T>::push_back(T number)
{
	expand();
	elem[idx] = number;
	++idx;
}

template<typename T>
void Vector<T>::shrink()
{
	if (capacity < DEFAULT_CAPACITY)
	{
		return;
	}
	/*缩容*/
	if (idx > (capacity >> 2))
	{
		return;
	}
	T* pOld = elem;
	elem = new T[capacity / 2];
	for (int i = 0; i != idx; ++i)
	{
		elem[i] = pOld[i];
	}
	delete[]pOld;
}

template<typename T>
unsigned Vector<T>::remove(unsigned left, unsigned right)
{
	/*特殊情况*/
	if (left == right)
	{
		return 0;
	}
	while (right < idx)
	{
		elem[left++] = elem[right++];
	}
	idx = idx - (right - left);
	shrink();
	return right - left;
}

template<typename T>
int Vector<T>::remove(unsigned r)
{
	T backup = elem[r];
	remove(r, r + 1);
	return backup;
}

template<typename T>
int Vector<T>::find(const T& number, unsigned left, unsigned right)
{
	int IntRight = right;
	/*利用短路判断，避免IntRight为-1，从而越界*/
	while ((left < IntRight--) && (number != elem[IntRight]));
	return IntRight;
}

template<typename T>
/*the return value is the number of deletes*/
unsigned Vector<T>::deduplicate()
{
	unsigned old_size = getSize();

​```
//int new_idx = 0;
//while (new_idx < getSize())
//{
//	int find_idx = find(elem[new_idx], new_idx + 1, getSize());
//	remove(find_idx);
//	++new_idx;
//}

int new_idx = 1;
while (new_idx < getSize())
{
	/*该算法从第一个开始，从该数向前查找，如果在前面有与该数一样的数则删除该数，否则++idx*/
	(find(elem[new_idx], 0, new_idx) >= 0) ? remove(new_idx) : ++new_idx;
}
return old_size - getSize();
​```

}
```



