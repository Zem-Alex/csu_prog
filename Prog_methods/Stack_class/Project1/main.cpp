#include <iostream>
#include <exception>
#include <string>
#include <chrono>
#include <vector>
#include <iomanip>
#include "StackOnList.cpp"
#include <random>

template <typename T>
class Stack
{
	T* data;         // ��������� �� ������ ������
	size_t count;    // ���������� ��������� � �����
	size_t capacity; // ������� ����� (������ �������)
	T* last;         // ��������� �� ��������� ������� (������� �����)

public:

	Stack()
	{
		count = 0;
		capacity = 10;
		data = new T[capacity];

		last = data; // ���������� ��������� �� ������� ����� ��������� �� ������ �������.
	}

	~Stack()
	{
		delete[] data;
	}

	void push(T&& rhs)
	{
		if (count == capacity)  // ���� ���� ��������, ����������� ��� ������.
		{
			T* newdata = new T[capacity * 2];

			for (size_t i = 0; i < count; i++)
			{
				newdata[i] = std::move(data[i]);
			}

			capacity *= 2;

			delete[] data; //������� ���������� ��� ������ �������� �������
			data = newdata;
		}
		data[count] = rhs; // ��������� ������� �� ������� �����.

		last = data + count; // ��������� ��������� �� ������� �����.

		count++;
	}

	T& top()
	{
		return *last; // ���������� �������, �� ������� ��������� last(������� �����).
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
			throw std::out_of_range("Stack is empty."); //�������� �� ������� �����.
		}
		count--;
	}

	void print()
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << i << ") " << data[i] << std::endl; // ����� ��������� ����� ��� �������
		}
	}

	size_t size() const
	{
		return count; // ���������� ������� ���������� ��������� � �����.
	}
};

// ������� ��� ����������������� ������
template <typename T>
void DeterministicTests(size_t N, size_t M, size_t K) {
	Stack<T> stack;
	std::vector<std::chrono::nanoseconds> pushTimes;
	std::vector<std::chrono::nanoseconds> popTimes;

	for (size_t i = 0; i < K; ++i) {
		auto startPush = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < N; ++j) {
			stack.push(T());
		}
		auto endPush = std::chrono::high_resolution_clock::now();
		pushTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(endPush - startPush));

		auto startPop = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < M; ++j) {
			stack.pop();
		}
		auto endPop = std::chrono::high_resolution_clock::now();
		popTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(endPop - startPop));
	}

	// ����� �����������
	std::cout << "Deterministic Test Results:" << std::endl;
	std::cout << "N = " << N << ", M = " << M << ", K = " << K << std::endl;
	std::cout << "Push Times (ns)\tPop Times (ns)" << std::endl;
	for (size_t i = 0; i < K; ++i) {
		std::cout << pushTimes[i].count() << "\t\t" << popTimes[i].count() << std::endl;
	}
}

// ������� ��� ������������������� ������
template <typename T>
void NonDeterministicTests(size_t N, size_t M, double P) {
	Stack<T> stack;
	std::vector<std::chrono::nanoseconds> pushTimes;
	std::vector<std::chrono::nanoseconds> popTimes;

	for (size_t i = 0; i < 1000; ++i) { // �������� 1000 �������������
		auto start = std::chrono::high_resolution_clock::now();

			double randValue = (double)rand() / RAND_MAX; // ���������� ��������� �������� [0, 1]
			if (randValue < P) {
				for (size_t k = 0; k < N; ++k) {
					stack.push(T());
				}
			}
			else {
				for (size_t k = 0; k < M; ++k) {
					if (stack.size() > 0) {
						stack.pop();
					}
				}
			}
		

		auto end = std::chrono::high_resolution_clock::now();
		pushTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));
	}

	// ����� �����������
	std::cout << "Non-Deterministic Test Results:" << std::endl;
	std::cout << "N = " << N << ", M = " << M << ", P = " << P << std::endl;
	std::cout << "Push Times (ns)" << std::endl;
	for (size_t i = 0; i < 1000; ++i) {
		std::cout << pushTimes[i].count() << std::endl;
	}
}


//int testStackOnList();

int main()
{
	srand(time(NULL));
	size_t N = 10000;  
	size_t M = 10000;
	size_t K = 1000; 
	double P = 0.5; 

	DeterministicTests<int>(N, M, K);
	//NonDeterministicTests<int>(N, M, P);
	//testStackOnList();
}