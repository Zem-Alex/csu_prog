#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
int majorityVotes(const vector<T>& elements)
{
	int majorEl, count = 0;
	stack<T> s;

	for (auto i : elements)
	{
		if (s.empty())
		{
			s.push(i);
		}
		else if (s.top() == i)
		{
			s.push(i);
		}
		else
		{
			s.pop();
		}
	}

	if (s.empty())
	{
		cout << "Mojorising element none" << endl;
		return -1;
	}
	else
	{
		majorEl = s.top();
		for (auto i : elements)
		{
			if (i == majorEl)
			{
				count++;
			}
		}
		if (count <= elements.size() / 2)
		{
			cout << "Mojorising element none" << endl;
			return -1;
		}
		else
		{
			cout << "Mojorising element: " << majorEl << endl;
			return majorEl;
		}
	}
}

int main()
{
	std::vector<int> elements = { 1, 0, 1, 2, 2, 1, 1, 3, 2, 1, 2, 1 };
	int result = majorityVotes(elements);

	return 0;
}
