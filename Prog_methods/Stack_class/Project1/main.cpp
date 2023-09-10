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

			delete[] data; //вызовет деструктор для кадого элемента массива
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
		//data[count];

		if (count == 0)
		{
			throw std::out_of_range("Stack is empty.");
		}
		count--;
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


int test1()
{
	Stack<int> s;

	for (size_t i = 0; i < 20; i++)
	{
		s.push(5);
	}

	s.push(7);
	s.push(9);

	std::cout << s.size() << std::endl;
	std::cout << s.top() << std::endl;

	return 0;
}

int test2()
{
	Stack<std::string> s;

	try
	{
		s.pop();

	}
	catch (const std::out_of_range& what)
	{
		std::cout << what.what() << std::endl;
	}

	for (size_t i = 0; i < 20; i++)
	{
		s.push("Hello world #" + std::to_string(i));
	}

	s.pop();
	s.pop();
	s.pop();

	s.top() = "Hello world and another world";
	std::cout << s.size() << std::endl;
	std::cout << "\n";
	s.print();
	std::cout << s.top() << std::endl;

	return 0;
}

int testStackOnList();

int main()
{
	testStackOnList();
}