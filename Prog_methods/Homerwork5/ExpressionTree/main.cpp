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


//using treeStack = std::stack<CalcNode*>;
//
//operations op = {
//    {"+", [](treeStack& stack)->double
//        {
//            return pop(stack) + pop(stack);
//        }
//    }
//}

class CalcNode
{
public:
    Term term;
    CalcNode* left;
    CalcNode* next;
    CalcNode() = default;

    static CalcNode* createCalcNode(const vector<Term>& postfix)
    {
        stack<CalcNode*> parseTrees;
        for (auto& t : postfix)
        {
            switch (t.type)
            {
            case Term::TermType::Variable:
            case Term::TermType::Constant:
                parseTrees.push(new CalcNode{ t, nullptr, nullptr });
                break;
            case Term::TermType::Operator:
            case Term::TermType::Function:
                size_t num = numOfArgs[t.value];
                CalcNode* tmp = nullptr;
                for (size_t i = 0; i < num; i++)
                {
                    parseTrees.top()->next = tmp;
                    tmp = parseTrees.top();
                    parseTrees.pop()
                }
                parseTrees.push(new CalcNode{ t, tmp, nullptr });
                break;
            default:
                break;
            }
            
        }
        return parseTrees.top();
    }

    double calculation(CalcNode* tree, std::unordered_map<string, double>& vars)
    {
        switch (tree->term.type)
        {
        case Term::TermType::Constant:
            return std::stod(tree->term.value);
        case Term::TermType::Variable:
            return  vars[tree->term.value];
        case Term::TermType::Operator:
        case Term::TermType::Function:
            return op[tree->term.value] (tree->left);
        default:
            break;
        }
    }
};

int main()
{
    auto f = expToTerms("1+1");

    
}





















//vector<Term> Term::stringToTerms(const string& s)
//{
//    vector<Term> result;
//
//    string current = "";
//
//    static string delimeters = " +-*/%!^(){}[]<>=,?:";
//
//    auto pos = s.begin();
//
//    while (pos != s.end())
//    {
//        auto it = std::find_first_of(pos, s.end(), delimeters.begin(), delimeters.end());
//
//        if (*pos == ' ')
//        {
//            pos++;
//            continue;
//        }
//
//        if (it == pos)
//            it++;
//
//        result.push_back(Term{ string(pos, it), TermType::Unknown });
//        pos = it;
//    }
//
//    for (size_t i = 0; i < result.size(); i++)
//    {
//        Term& t = result[i];
//        if (isdigit(t.value[0]))
//        {
//            t.type = Term::TermType::Constant;
//        }
//        else if (isalpha(t.value[0]))
//        {
//            if (i + 1 < result.size() && result[i + 1].value == "(")
//            {
//                t.type = Term::TermType::Function;
//            }
//            else
//                t.type = Term::TermType::Variable;
//        }
//        else if (t.value == "(")
//        {
//            t.type = Term::TermType::OpenBracket;
//        }
//        else if (t.value == ")")
//        {
//            t.type = Term::TermType::CloseBracket;
//        }
//        else
//        {
//            t.type = Term::TermType::Operator;
//            if (i == 0 || i > 0 && result[i - 1].type == Term::TermType::OpenBracket)
//            {
//                // лево ассоциативный оператор
//                t.value = "U" + t.value;
//            }
//
//
//        }
//
//    }
//
//    return result;
//}
//
//vector<Term> buildPostfixEntry(vector<Term>& terms)
//{
//    vector<Term> out;
//    stack<Term> s;
//
//    map<string, int> operatorPrecedence;
//    operatorPrecedence["+"] = 1;
//    operatorPrecedence["-"] = 1;
//    operatorPrecedence["*"] = 2;
//    operatorPrecedence["/"] = 2;
//    operatorPrecedence["^"] = 3;
//    operatorPrecedence["!"] = 3;
//    operatorPrecedence["U-"] = 4;
//
//    for (Term& t : terms)
//    {
//        if (t.type == Term::TermType::Variable || t.type == Term::TermType::Constant)
//        {
//            out.push_back(t);
//        }
//        else if (t.type == Term::TermType::OpenBracket)
//        {
//            s.push(t);
//        }
//        else if (t.type == Term::TermType::CloseBracket)
//        {
//            while (s.top().type != Term::TermType::OpenBracket)
//            {
//                out.push_back(s.top());
//                s.pop();
//            }
//            if (!s.empty() && s.top().type == Term::TermType::OpenBracket)
//            {
//                s.pop(); // Удаляем открывающую скобку(включительно)
//            }
//        }
//        else if (t.type == Term::TermType::Function)
//        {
//            s.push(t);
//        }
//        else if (t.type == Term::TermType::Operator)
//        {
//            while (!s.empty() && s.top().type == Term::TermType::Operator && operatorPrecedence[s.top().value] >= operatorPrecedence[t.value])
//            {
//                out.push_back(s.top());
//                s.pop();
//            }
//            s.push(t);
//        }
//    }
//
//    while (!s.empty())
//    {
//        out.push_back(s.top());
//        s.pop();
//    }
//
//
//    return out;
//}
//
//class ExpressionTreeNode
//{
//public:
//   /* enum class TermType
//    {
//        Constant,
//        Variable,
//        Operator,
//        Function,
//        OpenBracket,
//        CloseBracket,
//        Unknown,
//    };*/
//
//    ExpressionTreeNode(const Term& term) : termType(term.type), termName(term.value), firstArgument(nullptr), nextArgument(nullptr) {}
//
//    ExpressionTreeNode(Term::TermType type, const std::string& name) : termType(type), termName(name), firstArgument(nullptr), nextArgument(nullptr) {}
//
//    Term::TermType termType;
//    string termName;
//    ExpressionTreeNode* firstArgument;
//    ExpressionTreeNode* nextArgument;
//
//    static ExpressionTreeNode* BuildExpressionTreeFromPostfix(const std::vector<Term>& postfixExpression)
//    {
//        std::stack<ExpressionTreeNode*> stack;
//
//        for (const Term& term : postfixExpression)
//        {
//            if (term.type == Term::TermType::Variable || term.type == Term::TermType::Constant)
//            {
//                stack.push(new ExpressionTreeNode(term));
//            }
//            else if (term.type == Term::TermType::Operator || term.type == Term::TermType::Function)
//            {
//                int argumentCount = getOperatorArgumentCount(term.value);
//                ExpressionTreeNode* newNode = new ExpressionTreeNode(term);
//
//                for (int i = 0; i < argumentCount; i++)
//                {
//                    if (!stack.empty())
//                    {
//                        ExpressionTreeNode* argument = stack.top();
//                        stack.pop();
//                        newNode = CombineSubtrees(newNode, argument, newNode);
//                    }
//                }
//
//                stack.push(newNode);
//            }
//        }
//
//        if (stack.empty())
//        {
//            std::cerr << "Invalid postfix expression." << std::endl;
//            return nullptr;
//        }
//
//        ExpressionTreeNode* root = stack.top();
//        stack.pop();
//
//        if (!stack.empty())
//        {
//            std::cerr << "Invalid postfix expression." << std::endl;
//            return nullptr;
//        }
//
//        return root;
//    }
//
//    static bool isOperator(const std::string& term)
//    {
//        // Мы будем считать операторами только +, -, *, и /.
//        return (term == "+" || term == "-" || term == "*" || term == "/");
//    }
//
//    static int getOperatorArgumentCount(const std::string& term)
//    {
//        // Мы будем считать все операторы бинарными, то есть с двумя аргументами.
//        if (isOperator(term))
//        {
//            return 2;
//        }
//
//        // Если терм не является оператором, вернем 0.
//        return 0;
//    }
//
//    static ExpressionTreeNode* CombineSubtrees(ExpressionTreeNode* root, ExpressionTreeNode* firstSubtree, ExpressionTreeNode* nextSubtree)
//    {
//        if (root)
//        {
//            root->firstArgument = firstSubtree;
//            root->nextArgument = nextSubtree;
//        }
//        return root;
//    }
//};
//
//int main()
//{
//
//    string infixExpression = "(2 * 3) + 4 * y";
//    vector<Term> infixTerms = Term::stringToTerms(infixExpression);
//    vector<Term> postfixExpression = buildPostfixEntry(infixTerms);
//
//    ExpressionTreeNode* root = ExpressionTreeNode::BuildExpressionTreeFromPostfix(postfixExpression);
//
//
//    return 0;
//}

