#include <iostream>
#include <exception>
#include <string>

template <typename T>
class Stack
{
	T* data;
	size_t count;
	size_t capacity;
	T* last;

public:

	Stack()
	{
		count = 0;
		capacity = 10;
		data = new T[capacity];

		last = data;
	}

	~Stack()
	{
		delete[] data;
	}

	void push(T&& rhs)
	{
		if (count == capacity)
		{
			T* newdata = new T[capacity * 2];

			for (size_t i = 0; i < count; i++)
			{
				newdata[i] = std::move(data[i]);
			}

			capacity *= 2;

			delete[] data; //âûçîâåò äåñòðóêòîð äëÿ êàäîãî ýëåìåíòà ìàññèâà
			data = newdata;
		}
		data[count] = rhs;

		last = data + count;

		count++;
	}

	T& top()
	{
		return *last;
	}

	T& top() const
	{
		return *last;
	}

	void pop()
	{
		if (count == 0)
		{
			throw std::out_of_range("Stack is empty.");
		}
		count--;
		last = data + count;
	}

	void print()
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << i << ") " << data[i] << std::endl;
		}
	}

	size_t size() const
	{
		return count;
	}
};

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
