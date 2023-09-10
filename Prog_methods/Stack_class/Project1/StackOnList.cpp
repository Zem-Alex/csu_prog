#include <iostream>
#include <exception>

template <typename T>
class StackOnList
{
	struct myList
	{
		T data;
		myList* next;
	};

	myList* head;
	size_t count;

public:
	StackOnList() : count(0), head(nullptr) {}
	~StackOnList()
	{
		while (count)
		{
			pop();
		}
	};

	void push(T&& rhs)
	{
		head = new myList{ rhs, head };
		count++;
	}

	void pop()
	{
		if (count == 0)
		{
			throw std::out_of_range("Stack is empty.");
		}

		myList* tmphead = head;
		head = head->next;
		delete tmphead;
		count--;
	}

	T& top()
	{
		return head->data;
	}

	size_t size() const
	{
		return count;
	}
};


int testStackOnList()
{
	StackOnList<int> s;
	try
	{
		s.pop();
	}
	catch (const std::out_of_range& what)
	{
		std::cout << what.what() << std::endl;
	}

	s.push(5);
	s.push(6);
	s.push(7);

	std::cout << s.top() << std::endl;

	s.push(9);

	//s.top() = 123456;
	std::cout << s.top() << std::endl;

	return 0;
}