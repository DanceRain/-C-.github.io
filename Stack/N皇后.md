# N皇后

N皇后问题主要考察的是对试探回溯法的理解程度。试探回溯可以应用在很多领域上，例如在一个迷宫中寻找出路，在一个地图软件上寻找所有可以抵达目标地址的路径。而N皇后问题，是对试探回溯这种方法的练习。



## 需求分析

棋盘：N行N列

皇后：皇后的势力范围在以其为中心的垂线和平行线以及在对角线和反对角线上。

### 需求

在N行N列的棋盘上，排列N个皇后，使其不能相互进入其势力范围。



## 数据结构

### 皇后

我们定义一个类来表示皇后在棋盘上的位置。因此它包括x、y轴，还应该有一个重载的比较运算符。比较运算符用来比较两个皇后是否在其对方的势力范围内。因此其定义如下：

```c++
struct Queen
{
    int x;
    int y;
    Queen(int _x, int _y):x(_x), y(_y){}
    bool operator==(const Queen& q);
    bool operator!=(const Queen& q)
    {
        return !(*this == q);
    }
}

bool Queen::operator==(const Queen& q)
{
    return (q.x == x) || (q.y == y) || ((q.x + q.y) == (x + y)) || ((q.x - q.y) == (x + y));
}
```

### 放置皇后

所谓试探回溯算法，就是从某一个点开始，对其不同的可能进行试探，如果其中某一试探满足条件，则继续如此。也就是说，任何试探回溯算法都会以最后可能试探的结束而结束。例如从第一步有\<A，B，C\>三种可能， 而第二步有\<D，E，F\>三种可能，从A开始往下试探，分别\<A, D\>, \<A, B\>, \<A, C\>,接着回溯到A。这样循环，一直到回溯为C，则完成所有可能的试探。 依据此思路我们既可以设计我们的递归版本放置

```c++


void placeQueen(int N, int row)
{
	void printqArr(const vector<Queen> & qArr);
	static vector<Queen> Arr;
	for (int col = 0; col != N; ++col)
	{
		Queen q(row, col);
		if (find(Arr.begin(), Arr.end(), q) == Arr.end())
		{
			Arr.push_back(q);
			if (row == N - 1)
			{
				printqArr(Arr);
				Arr.erase(Arr.end() - 1);
			}
			else
			{
				placeQueen(N, row + 1);
			}
		}
		if (col == N - 1 && row != 0)
		{
			Arr.erase(Arr.end() - 1);
		}
	}
}

void printqArr(vector<Queen>& qArr)
{
    for(Queen& _elem : qArr)
    {
        cout << _elem.x << " " << _elem.y << endl;
    }
    cout << endl;
}

```

首先程序从<0,0>开始试探，如果在**皇后集**中没有与该皇后“相等”的数，就将皇后放入到**皇后集**中去，然后再判断**皇后集**当中的 **row** 是否为 **N - 1**，如果是则证明目前的皇后集满足条件可以输出（输出完成后删除该皇后，因为它上面已经没有层了，所以无法删除他），如果不是则进行下一层试探。

另外添加了一个判断来是否为最后一个试探点，如果是则删除掉皇后集中最后一个元素，该元素记录的是回溯点，删除掉是因为该回溯点的试探已经全部完成，重新定义回溯点再从此回溯点开始试探。



## 迭代版本

上面的程序采用递归版本实现，为此我们需要借用 **栈** 来完成该操作。下面是代码

```c++
struct Queen
{
	int x;
	int y;
	Queen(int _x, int _y):x(_x), y(_y){}
	Queen(int x = 0):x(x), y(x){}
	bool operator== (const Queen& q) const
	{
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
	}
	bool operator !=(const Queen& q) const
	{
		return !(*this == q);
	}
};
```



```c++
int placeQueen(int N)
{
	int solutionCount = 0;
	Stack<Queen> solu;
	Queen q(0, 0);
	do
	{
		if (N == solu.size() || N == q.y)
		{
			q = solu.pop();
			++q.y;
		}
		else
		{
			while ((q.y != N) && (0 <= solu.find(q)))
			{
				q.y++;
			}
			if (q.y < N)
			{
				solu.push(q);
				if (solu.size() == N)
				{
					for (auto& elem : solu)
					{
						cout << elem.x << " " << elem.y << endl;
					}
					cout << endl;
					solutionCount++;
				}
				q.x++;
				q.y = 0;
			}
		}
	} while ((q.x != 0) || (q.y != N));
	return solutionCount;
}
```

该程序的思路与上面类似，只不过将递归的部分该由迭代来完成。

（1）从回溯点开始往后试探，如果栈数==N或者q.y == n，该 **皇后栈** 要么满足要求（栈数 == n）要么已试探完所有的试探点（q.y == N），则退栈到回溯点（该列上一列的某个点），然后使q.y++，以该点为回溯点继续下一试探。

（2）如果不满足 1，则证明该栈不满足条件且未试探完所有试探点，继续进行试探。

（3）利用while(q.y != N && solu.find(q) >= 0) 来完成试探操作。

（4）如果q.y <= N 则证明在q.x列中有满足条件的皇后（也就是该皇后不与栈中其它皇后冲突，则进行入栈）。再比较栈元素数量是否与N相同，如果相同则该 **皇后栈** 满足要求，做对应的操作（我这里是打印输出并使记录个数加一），如果不相同则说明该试探还未使每一行都站满皇后，则将q.x++，q.y = 0继续下一列的试探。

（5）如果q.y == N则说明该列中没有满足条件的皇后（也就是该皇后与栈中皇后发生冲突），则又从开始1操作。

