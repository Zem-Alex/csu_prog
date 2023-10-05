#include <iostream>
#include <stack>

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

template <typename stack_t>
void quickSort(stack_t& s) {
	if (s.empty()) {
		return; // Если стек пуст, нет смысла сортировать
	}

	stack_t lessStack, equalStack, greaterStack, store;
	auto pivot = s.top();
	s.pop();

	// Разбиваем стек на три подстека
	while (!s.empty()) {
		auto current = s.top();
		s.pop();
		if (current < pivot) {
			lessStack.push(current);
		}
		else if (current == pivot) {
			equalStack.push(current);
		}
		else {
			greaterStack.push(current);
		}
	}

	// Рекурсивно сортируем первый и третий подстеки
	quickSort(lessStack);
	quickSort(greaterStack);

	// Объединяем три подстека в исходный стек
	while (!greaterStack.empty()) {
		equalStack.push(greaterStack.top());
		greaterStack.pop();
	}
	while (!equalStack.empty()) {
		s.push(equalStack.top());
		equalStack.pop();
	}
	while (!lessStack.empty()) {
		greaterStack.push(lessStack.top());
		lessStack.pop();
	}
	while (!greaterStack.empty()) {
		s.push(greaterStack.top());
		greaterStack.pop();
	}


	s.push(pivot); // Помещаем опорный элемент обратно в стек
}


int main()
{
	initializer_list<int> list = { 3,1,6,9,0,13,7,4,8,0 };
	stack<int> s(list);

	//mysort(s);
	quickSort(s);
	// Выводим отсортированный стек
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}

	return 0;
}