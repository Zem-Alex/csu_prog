#include <iostream>
#include <ctime>
#include <stack>
#include <vector>

using namespace std;

template <typename stack_t>
void mysort(stack_t& s)
{
	stack_t store;
	stack_t result;

	while (!s.empty())
	{
		result.push(s.top());
		s.pop();

		while (!s.empty())
		{
			if (s.top() < result.top())
			{
				swap(s.top(), result.top());
			}
			store.push(s.top());
			s.pop();
		}

		while (!store.empty())
		{
			s.push(store.top());
			store.pop();
		}
	}
	while (!result.empty())
	{
		s.push(result.top());
		result.pop();
	}
}

template <class stack_t>
void movehead(stack_t& _left, stack_t& _right)
{
	_right.push(std::move(_left.top()));
	_left.pop();
}

template <class stack_t>
void movestack(stack_t& _left, stack_t& _right)
{
	while (!_left.empty())
	{
		movehead(_left, _right);
	}
}

stack<int> generateRandomStack(int size)
{
	stack<int> s;
	srand(time(0)); // »нициализаци€ генератора случайных чисел
	for (int i = 0; i < size; i++)
	{
		s.push(rand());
	}
	return s;
}

stack<int> generateSortedStack(int size)
{
	stack<int> s;
	for (int i = 1; i <= size; i++)
	{
		s.push(i);
	}
	return s;
}

template <typename SortFunc, typename stack_t>
double measureSortingTime(SortFunc sortFunc, stack_t& s)
{
	clock_t start = clock();
	sortFunc(s);
	clock_t end = clock();
	return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

template <class stack_t, class compare>
void myquicksort(stack_t& _stack, compare _pred = std::less<decltype((_stack.top()))>())
{
	if (_stack.size() <= 1)
		return;

	stack_t storeLess;
	stack_t storeGreater;
	stack_t storeEqual;

	movehead(_stack, storeEqual);

	while (!_stack.empty())
	{
		if (_pred(_stack.top(), storeEqual.top()))
		{
			movehead(_stack, storeLess);
		}
		else if (_pred(storeEqual.top(), _stack.top()))
		{
			movehead(_stack, storeGreater);
		}
		else
		{
			movehead(_stack, storeEqual);
		}
	}

	myquicksort(storeLess, _pred);
	myquicksort(storeGreater, _pred);

	movestack(storeGreater, storeEqual); // left -> right
	movestack(storeEqual, _stack);
	movestack(storeLess, storeEqual);
	movestack(storeEqual, _stack);
}

template <class stack_t>
void myquicksortWrapper(stack_t& _stack)
{
	myquicksort(_stack, std::less<int>()); // «десь вы указываете необходимый компаратор
}

int main()
{	
	int stackSize = 100000;
	
	stack<int> randomStack = generateRandomStack(stackSize);
	// «амер времени выполнени€ дл€ сортировки вставками на случайно заполненном стеке
	//double insertionSortTimeRandom = measureSortingTime(mysort<stack<int>>, randomStack);
	//cout << "Insertion Sort Time for Random Stack: " << insertionSortTimeRandom << " seconds" << endl;



	stack<int> randomStack2 = generateRandomStack(stackSize);
	// «амер времени выполнени€ дл€ быстрой сортировки на случайно заполненном стеке
	double quickSortTimeRandom = measureSortingTime(myquicksortWrapper<stack<int>>, randomStack2);
	cout << "Quick Sort Time for Random Stack: " << quickSortTimeRandom << " seconds" << endl;


	stack<int> sortedStack = generateSortedStack(stackSize);
	// «амер времени выполнени€ дл€ сортировки вставками на упор€доченном стеке
	//double insertionSortTimeSorted = measureSortingTime(mysort<stack<int>>, sortedStack);
	//cout << "Insertion Sort Time for Sorted Stack: " << insertionSortTimeSorted << " seconds" << endl;


	stack<int> sortedStack2 = generateSortedStack(stackSize);
	// «амер времени выполнени€ дл€ быстрой сортировки на упор€доченном стеке
	double quickSortTimeSorted = measureSortingTime(myquicksortWrapper<stack<int>>, sortedStack2);
	//cout << "Quick Sort Time for Sorted Stack: " << quickSortTimeSorted << " seconds" << endl;

	return 0;
}
