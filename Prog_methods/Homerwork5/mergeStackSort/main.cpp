#include <iostream>
#include <stack>


using namespace std;

// Sorts input stack and returns sorted stack.
template<typename stack_t>
stack<int> sortStack(stack<int>& src)
{
	if (src.size() <= 1)
		return

	stack_t result;
	size_t count = 0;

	do
	{
		while (!src.empty())
		{
			extractIncrementalSubsequence(src, left);
			extractIncrementalSubsequence(src, right);

			mergeStack(left, right, result);
		}
		count = 0;
		while (!result.empty())
		{
			extractIncrementalSubsequence(result, left);
			extractIncrementalSubsequence(result, right);

			mergeStack(left, right, src);
			count++;
		}
	}
	while (count > 1) {
		
	}

	return tmpStack;
}


// main function
int main()
{
	stack<int> s1, s2;
	s1.push(34);
	s1.push(3);
	s1.push(31);
	s1.push(14);
	s1.push(23);
	s1.push(11);

	
	// This is the temporary stack
	s2 = sortStack(s1);
	cout << "Sorted and merged stack :\n";

	
}

