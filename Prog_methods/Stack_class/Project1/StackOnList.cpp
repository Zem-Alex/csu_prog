#include <iostream>
#include <exception>

template <typename T>
class StackOnList
{
    // Внутренняя структура myList для представления элементов связанного списка
    struct myList
    {
        T data;         // Значение элемента
        myList* next;   // Указатель на следующий элемент списка
    };

    myList* head;    // Указатель на вершину стека (первый элемент)
    size_t count;    // Количество элементов в стеке

public:
    // Конструктор по умолчанию инициализирует пустой стек
    StackOnList() : count(0), head(nullptr) {}

    // Деструктор удаляет все элементы стека при его уничтожении
    ~StackOnList()
    {
        while (count)
        {
            pop();
        }
    };

    // Метод push добавляет элемент в вершину стека
    void push(T&& rhs)
    {
        // Создаем новый узел и делаем его новой вершиной стека
        head = new myList{ rhs, head };
        count++;
    }

    // Метод pop удаляет элемент из вершины стека
    void pop()
    {
        if (count == 0)
        {
            throw std::out_of_range("Stack is empty.");
        }

        // Сохраняем указатель на текущую вершину стека
        myList* tmphead = head;

        // Перемещаем указатель вершины на следующий элемент
        head = head->next;

        // Удаляем старую вершину
        delete tmphead;
        count--;
    }

    // Метод top возвращает ссылку на элемент в вершине стека
    T& top()
    {
        if (count == 0)
        {
            throw std::out_of_range("Stack is empty.");
        }

        return head->data;
    }

    // Метод size возвращает количество элементов в стеке
    size_t size() const
    {
        return count;
    }
};


/*int testStackOnList()
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
}*/