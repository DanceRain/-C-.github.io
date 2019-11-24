# 说明文档

主要对下面几个比较重要的地方进行说明。

+ selectMax

+ selectionSort
+ insertionSort
+ mergeSort



## selectMax

```c++
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
```

该算法十分简单，就是使用比较替换，来确定一个序列中最大的元素。



## selectionSort

```c++
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
```

选择排序的思路十分简单，首先确定一个区间的头和尾，当然，头和尾是不属于排序序列的，只是作为辅助节点来方便我们操作。然后，使用selectMax函数来从链表中选择data最大的节点，将其插入到尾节点之前，然后使尾节点指向该节点，因为该节点已经有序。

为什么我们要使用对selectMax传入head->succ而不是使head = p然后传入，原因是，我们随时可能会删除掉head节点，此时该节点就是一个空节点。而使用head->succ可以确保每次都是从待排序区间的第一个节点出发进行selectMax并删除。



## insertionSort

```c++
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
void List<T>::insertionSort(ListNode<T>* p, int n)
{
	for (int i = 0; i != n; ++i)
	{
		insertAsAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->prev);
	}
}
```

insertionSort的主要思路就是利用search函数往前查找到当前节点在序列中的位置，然后插入在其后面，再删除。

search函数往前查找，一旦找到比**传入节点**值大于或者等于的节点便返回该节点，然后将返回节点插入在**传入节点**之后。

我们由小范围到大范围，逐渐将**无序序列中的所有值按照search在有序序列中查找到的顺序**插入到有序序列中以达到整体的有序性。



## mergeSort

```c++
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
```

链表的归并排序相较之向量的归并排序还更加容易理解。在此，我用图片来做解释。

![mergeSort](https://github.com/DanceRain/Data-structure-learning.github.io/blob/master/Picture/List/mergeSort.PNG?raw=true)

![merge](https://github.com/DanceRain/Data-structure-learning.github.io/blob/master/Picture/List/merge.PNG?raw=true)

值得注意的是，我们在lo上写明为引用，原因是，在merge中，我们使用了insertAsBefore和remove重新改变了节点与节点的位置关系，如果我们不使用指针引用，那么在外部lo有可能就指向一个不存在的值，此时就会产生不可预料的结果

