#include "RPN.hpp"


RPN::RPN() {}

RPN::RPN(const RPN& copy) : stack(copy.stack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        stack = other.stack;
    return *this;
}

RPN::~RPN() {}

bool RPN::isNum(const std::string& num) const
{
    if (num.empty())
        return false;
    
    for (size_t i = 0; i < num.size(); i++)
    {
        if (!std::isdigit(num[i]))
            return false;
    }
    return true;
}

bool RPN::isopr(const std::string& opr) const
{
    if (opr.size() != 1)
        return false;
    char c = opr[0];

    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double RPN::applyOperation(double a, double b, char opr)
{
    switch(opr)
    {
        case '+':
            return (a + b);

        case '-':
            return (a - b);

        case '*':
            return (a * b);

        case '/':
        if (b == 0)
            throw std::runtime_error("Error: division by zero");
        return (a / b);

        default:
            throw std::runtime_error("Error: unknown operation"); 
    }
}

int RPN::calculate(const std::string& str)
{
    std::stringstream iss(str);

    std::string token;
    while (iss >> token)
    {
        if (isNum(token))
        {
            double num = strtod(token.c_str(), NULL);
            stack.push_back(num);
        }

        else if (isopr(token))
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error: not enough number");

            double b = stack.back();
            stack.pop_back();

            double a = stack.back();
            stack.pop_back();

            double result = applyOperation(a, b, token[0]);

            stack.push_back(result);
        }

        else
            throw std::runtime_error("Error: invalid token");
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");

    return (static_cast<int>(stack.back()));
}