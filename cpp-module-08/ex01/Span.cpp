#include "Span.hpp"

Span::Span(unsigned int n) : maxSize(n) {}
Span::Span(const Span& copy)
{
    *this = copy;
}
Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        numbers = other.numbers;
        maxSize = other.maxSize;
    }
    return *this;
}
Span::~Span() {}

void Span::addNumber(int n)
{
    if (numbers.size() >= maxSize)
        throw std::out_of_range("out of range");
    numbers.push_back(n);
}

int Span::longestSpan() const
{
    int min;
    int max;

    if (numbers.size() < 2)
        throw std::out_of_range("out of range");
    min = *std::min_element(numbers.begin(), numbers.end());
    max = *std::max_element(numbers.begin(), numbers.end());
    return max - min;
}

int Span::shortestSpan() const
{
    int diff;
    int minSpan;

    if (numbers.size() < 2)
        throw std::out_of_range("out of range");
    std::vector<int> tmp = numbers;
    std::sort(tmp.begin(), tmp.end());

    minSpan = tmp[1] - tmp[0];
    for (size_t i = 1; i < tmp.size() - 1; i++)
    {
        diff = tmp[i + 1] - tmp[i];
        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
}


