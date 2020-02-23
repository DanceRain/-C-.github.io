#pragma once
#include "Vector.h"

template<typename T> class Vector;

template<typename T>
class Stack :public Vector<T>
{
public:
	Stack(std::initializer_list<T> list):Vector<T>(list){}
	Stack() :Vector<T>(){};
	void push(const T& e) { this->push_back(e); }
	const T pop() { return this->remove(this->size() - 1); }
	T& top() { return (*this)[this->size() - 1]; }
	bool empty() { return this->size() == 0; }
};

void convert(Stack<char>& s, int n, int base)
{
	static char digit[]
		= { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	while (n > 0)
	{
		int number = n % base;
		s.push(digit[number]);
		n /= base;
	}
}

