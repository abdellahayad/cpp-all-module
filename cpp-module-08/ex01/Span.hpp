#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
// #include <exception>
#include <iostream>
#include <list>

class Span
{
    private:
        unsigned int maxSize;
        std::vector<int> numbers;
    public:
        Span(unsigned int n);
        Span(const Span& copy);
        Span &operator=(const Span& other);
        ~Span();
        void addNumber(int n);
        int longestSpan() const; 
        int shortestSpan() const;

        template <typename it>
        void addRange(it begin, it end)
        {
            if (numbers.size() + std::distance(begin, end) > maxSize)
                throw std::out_of_range("out of range");
            numbers.insert(numbers.end(), begin, end);
        }

};









#endif