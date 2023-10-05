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
	T* data;         // Указатель на массив данных
	size_t count;    // Количество элементов в стеке
	size_t capacity; // Емкость стека (размер массива)
	T* last;         // Указатель на последний элемент (вершину стека)

public:

	Stack()
	{
		count = 0;
		capacity = 10;
		data = new T[capacity];

		last = data; // Изначально указатель на вершину стека указывает на начало массива.
	}

	~Stack()
	{
		delete[] data;
	}

	void push(T&& rhs)
	{
		if (count == capacity)  // Если стек заполнен, увеличиваем его размер.
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
		data[count] = rhs; // Добавляем элемент на вершину стека.

		last = data + count; // Обновляем указатель на вершину стека.

		count++;
	}

	T& top()
	{
		return *last; // Возвращает элемент, на который указывает last(вершину стека).
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
			throw std::out_of_range("Stack is empty."); //Проверка на пустоту стека.
		}
		count--;
	}

	void print()
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << i << ") " << data[i] << std::endl; // Вывод элементов стека для отладки
		}
	}

	size_t size() const
	{
		return count; // Возвращает текущее количество элементов в стеке.
	}
};

// Функция для детерминированных тестов
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

	// Вывод результатов
	std::cout << "Deterministic Test Results:" << std::endl;
	std::cout << "N = " << N << ", M = " << M << ", K = " << K << std::endl;
	std::cout << "Push Times (ns)\tPop Times (ns)" << std::endl;
	for (size_t i = 0; i < K; ++i) {
		std::cout << pushTimes[i].count() << "\t\t" << popTimes[i].count() << std::endl;
	}
}

// Функция для недетерминированных тестов
template <typename T>
void NonDeterministicTests(size_t N, size_t M, double P) {
	Stack<T> stack;
	std::vector<std::chrono::nanoseconds> pushTimes;
	std::vector<std::chrono::nanoseconds> popTimes;

	for (size_t i = 0; i < 1000; ++i) { // Проведем 1000 экспериментов
		auto start = std::chrono::high_resolution_clock::now();

			double randValue = (double)rand() / RAND_MAX; // Генерируем случайное значение [0, 1]
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

	// Вывод результатов
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