#include <iostream>
#include <exception>
#include <string>
#include "stack.cpp"

using namespace std;

int indexWrongBracket(StackOnList <char> &s, string &sequenceBrackets)
{
	int length = sequenceBrackets.length();

	for (int count = 0; count < length; count++)
	{
		//cout << s.top();
		if (sequenceBrackets[count] == '(' || sequenceBrackets[count] == '{' || sequenceBrackets[count] == '[')
		{
			s.push(forward<char>(sequenceBrackets[count]));
		}
		else if (sequenceBrackets[count] == ')')
		{
			if (s.size() == 0 || s.top() != '(')
			{
				return count;
			}
			else
			{
				s.pop();
			}
		}
		else if (sequenceBrackets[count] == '}')
		{
			if (s.size() == 0 || s.top() != '{')
			{
				return count;
			}
			else
			{
				s.pop();
			}
		}
		else if (sequenceBrackets[count] == ']')
		{
			if (s.size() == 0 || s.top() != '[')
			{
				return count;
			}
			else
			{
				s.pop();
			}
		}
	}
	
	if (s.size() > 0)
	{
		return length - 1; // Возвращаем индекс последней открывающей скобки
	}

	return -1; // Если все скобки правильно парные
}

int main()
{
	StackOnList<char> s;

	int size = 3;

	string sequenceBrackets = "()[{(){[]}]";
		
	cout << indexWrongBracket(s, sequenceBrackets);


	return 0;
}