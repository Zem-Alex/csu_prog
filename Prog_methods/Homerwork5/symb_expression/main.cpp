#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <algorithm>
#include <map>
#include <unordered_map>

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
		Unknown,
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

	static string delimeters = " +-*/%!^(){}[]<>=,?:";

	auto pos = s.begin();

	while (pos != s.end())
	{
		auto it = std::find_first_of(pos, s.end(), delimeters.begin(), delimeters.end());

		if (*pos == ' ')
		{
			pos++;
			continue;
		}

		if (it == pos)
			it++;

		result.push_back(Term{ string(pos, it), TermType::Unknown });
		pos = it;
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		Term& t = result[i];
		if (isdigit(t.value[0]))
		{
			t.type = Term::TermType::Constant;
		}
		else if (isalpha(t.value[0]))
		{
			if (i + 1 < result.size() && result[i + 1].value == "(")
			{
				t.type = Term::TermType::Function;
			}
			else
				t.type = Term::TermType::Variable;
		}
		else if (t.value == "(")
		{
			t.type = Term::TermType::OpenBracket;
		}
		else if (t.value == ")")
		{
			t.type = Term::TermType::CloseBracket;
		}
		else
		{
			t.type = Term::TermType::Operator;
			if (i == 0 || i > 0 && result[i - 1].type == Term::TermType::OpenBracket)
			{
				// лево ассоциативный оператор
				t.value = "U" + t.value;
			}


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
		else if (value.find_first_not_of("+-*/=<>") == string::npos)
		{
			t.type = Term::TermType::Operator;
		}
		else if (value.find_first_not_of("^") == string::npos)
		{
			t.type = Term::TermType::Function;
		}
		else if (value.find_first_not_of("!") == string::npos)
		{
			for (int i = 1; i < terms.size(); i++)
			{
				if (&t == &terms[i])
				{
					if (terms[i - 1].value.find_first_of(")") != string::npos || terms[i - 1].type == Term::TermType::Constant || terms[i - 1].type == Term::TermType::Variable)
					{
						t.type = Term::TermType::Function;
						break;
					}
					else
					{
						t.type = Term::TermType::Operator;
						break;
					}
				}

			}
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

vector<Term> buildPostfixEntry(vector<Term>& terms)
{
	vector<Term> out;
	stack<Term> s;

	map<string, int> operatorPrecedence;
	operatorPrecedence["+"] = 1;
	operatorPrecedence["-"] = 1;
	operatorPrecedence["*"] = 2;
	operatorPrecedence["/"] = 2;
	operatorPrecedence["^"] = 3;
	operatorPrecedence["!"] = 3;
	operatorPrecedence["U-"] = 4;

	for (Term& t : terms)
	{
		if (t.type == Term::TermType::Variable || t.type == Term::TermType::Constant)
		{
			out.push_back(t);
		}
		else if (t.type == Term::TermType::OpenBracket)
		{
			s.push(t);
		}
		else if (t.type == Term::TermType::CloseBracket)
		{
			while (s.top().type != Term::TermType::OpenBracket)
			{
				out.push_back(s.top());
				s.pop();
			}
			if (!s.empty() && s.top().type == Term::TermType::OpenBracket)
			{
				s.pop(); // Удаляем открывающую скобку(включительно)
			}
		}
		else if (t.type == Term::TermType::Function)
		{
			s.push(t);
		}
		else if (t.type == Term::TermType::Operator)
		{
			while (!s.empty() && s.top().type == Term::TermType::Operator && operatorPrecedence[s.top().value] >= operatorPrecedence[t.value])
			{
				out.push_back(s.top());
				s.pop();
			}
			s.push(t);
		}
	}

	while (!s.empty())
	{
		out.push_back(s.top());
		s.pop();
	}


	return out;
}

vector<Term> buildPostfixEntry_2_Version(vector<Term>& terms)
{
	vector<Term> result;
	vector<Term> stack;

	static std::unordered_map<std::string, size_t> priority =
	{
		{"+", 60},
		{"-", 60},
		{"%", 50},
		{"*", 50},
		{"/", 50},
		{"^", 30},
		{"!", 30},
		{"U-", 30},
		{"=", 160},
		{"?", 166},
		{":", 165},
		{",", 170}
	};

	for (Term& t : terms)
	{
		// ...

		switch (t.type)
		{
		case Term::TermType::Variable:
		case Term::TermType::Constant:
			result.push_back(t);
			break;
		case Term::TermType::OpenBracket:
		case Term::TermType::Function:
			stack.push_back(t);
			break;
		case Term::TermType::CloseBracket:
			while (!stack.empty() && (stack.back().type != Term::TermType::OpenBracket))
			{
				result.push_back(stack.back()); // этот вайл не правильный ( сфоткал)
				stack.pop_back();
			}
			if (!stack.empty() && stack.back().type == Term::TermType::OpenBracket)
			{
				stack.pop_back(); // Удаляем открывающую скобку
			}
			break;
		case Term::TermType::Operator:
			while (stack.size() != 0 && stack.back().type != Term::TermType::OpenBracket && priority[stack.back().value] <= priority[t.value])
			{
				result.push_back(stack.back());
				stack.pop_back();
			}
			stack.push_back(t);
			break;
		default:
			break;
		}
	}
	return result;
}

double mySqrt(double x) {
	if (x < 0) {
		throw runtime_error("Нельзя извлекать корень из отрицательного числа");
	}
	return sqrt(x);
}

double evaluatePostfixExpression(const vector<Term>& postfixExpression, const std::unordered_map<std::string, double>& variableMap)
{
	stack<double> S;

	for (const Term& term : postfixExpression)
	{
		if (term.type == Term::TermType::Constant)
			S.push(stod(term.value));
		else if (term.type == Term::TermType::Variable)
		{
			if (variableMap.find(term.value) != variableMap.end())
				S.push(variableMap.at(term.value));
		}
		else if (term.type == Term::TermType::Operator)
		{
			double operand2 = S.top();
			S.pop();

			double operand1 = S.top();
			S.pop();

			double result;

			if (term.value == "+")	result = operand1 + operand2;
			else if (term.value == "-")	result = operand1 - operand2;
			else if (term.value == "*")	result = operand1 * operand2;
			else if (term.value == "/")	result = operand1 / operand2;
			else if (term.value == "^")	result = pow(operand1, operand2);

			S.push(result);
		}
		else if (term.type == Term::TermType::Function)
		{
			if (term.value == "sin")
			{
				double operand = S.top();
				S.pop();
				double result = sin(operand);
				S.push(result);
			}
			else if (term.value == "cos")
			{
				double operand = S.top();
				S.pop();
				double result = cos(operand);
				S.push(result);
			}
			else if (term.value == "sqrt")
			{
				double operand = S.top();
				S.pop();
				double result = mySqrt(operand);
				S.push(result);
			}
		}
	}

	return S.top();
}
/*шnt main()
{
	//vector<Term> v = Term::stringToTerms("1.23 * abc - 3.15 * func_1(-x / (!y - z * x^(abc)^2) / [abc] + 6)! ^ arr[2*i]");
	vector<Term> v = Term::stringToTerms("1.23 * abc - 3.15");

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

	cout << endl << "Postfix:" << endl;


	vector<Term> postfixEntry;

	postfixEntry = buildPostfixEntry_2_Version(v);
	//postfixEntry = buildPostfixEntry(v);

	for (Term& t : postfixEntry)
	{
		cout << t.value << "";
	}

	cout << endl;

	return 0;
}*/



int main()
{
	std::unordered_map<std::string, double> variableMap;
	variableMap["x"] = 5.0;
	variableMap["y"] = 10.0;
	variableMap["abc"] = 3.14 / 2;

	string infixExpression = "sqrt(30 + x * y + sin(abc))^2";
	vector<Term> infixTerms = Term::stringToTerms(infixExpression);
	vector<Term> postfixExpression = buildPostfixEntry(infixTerms);

	double result = evaluatePostfixExpression(postfixExpression, variableMap);

	cout << "Result: " << result << endl;

	return 0;
}