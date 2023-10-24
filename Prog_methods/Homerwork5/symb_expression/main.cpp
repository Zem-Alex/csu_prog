#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class Term
{
public:
	enum class TermType 
	{ 
		Constant, 
		Variable, 
		Operator, 
		Function, 
		OpenBracket, 
		CloseBracket,
	};

	Term() = default;
	Term(string s, TermType tt) : value(s), type(tt) {}

	string value;
	TermType type;

	static vector<Term> stringToTerms(const string& s);
};

vector<Term> Term::stringToTerms(const string& s)
{
	vector<Term> result;

	string current = "";

	static string delimeters = " +-*/%!^(){}[]<>=,";

	auto pos = s.begin();

	while (pos != s.end())
	{
		//auto it = s.find_first_of(delimeters, pos - s.begin()) + s.begin();
		auto it = std::find_first_of(pos, s.end(), delimeters.begin(), delimeters.end());

		if (it == pos)
		{
			if (*pos != ' ')
			{
				result.push_back(Term{ string(1, *pos), TermType::Operator });
			}
			++pos;
		}
		else
		{
			result.push_back(Term{ string(pos, it), TermType::Operator });
			pos = it;
		}
	}
	return result;
}

void classifyTerms(vector<Term>& terms)
{
	for (Term& t : terms)
	{
		const string& value = t.value;

		// Проверяем, если терм состоит только из цифр или точки
		if (value.find_first_not_of("0123456789.") == string::npos)
		{
			t.type = Term::TermType::Constant;
		}
		
		else if (value.find_first_not_of("({[") == string::npos)
		{
			t.type = Term::TermType::OpenBracket;
		}
		else if (value.find_first_not_of(")}]") == string::npos)
		{
			t.type = Term::TermType::CloseBracket;
		}
		// Проверяем, если терм - оператор
		else if (value.find_first_not_of("+-*/=<>!^") == string::npos)
		{
			t.type = Term::TermType::Operator;
		}

		// Проверяем, если терм состоит только из букв
		else if (value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") == string::npos)
		{
			for (int i = 0; i < terms.size(); i++)
			{
				if (&t == &terms[i])
				{
					if (terms[i + 1].value.find_first_of("(") != string::npos)
					{
						t.type = Term::TermType::Function;
						break;
					}
					else
					{
						t.type = Term::TermType::Variable;
						break;
					}
				}
				
			}
		}


		
	}
}


int main()
{
	vector<Term> v = Term::stringToTerms("1.23 * abc - 3.15 * 1func(-x / (!y - z * x^(abc)^2) / [abc] + 6)! ^ arr[2*i]");

	classifyTerms(v);

	for (Term& t : v)
	{
		cout << "Value: " << t.value << "\t Type: ";
		switch (t.type)
		{
		case Term::TermType::Constant:
			cout << "Constant";
			break;
		case Term::TermType::Variable:
			cout << "Variable";
			break;
		case Term::TermType::Operator:
			cout << "Operator";
			break;
		case Term::TermType::Function:
			cout << "Function";
			break;
		case Term::TermType::OpenBracket:
			cout << "OpenBracket";
			break;
		case Term::TermType::CloseBracket:
			cout << "CloseBracket";
			break;
		}
		cout << endl;
	}
	return 0;
}