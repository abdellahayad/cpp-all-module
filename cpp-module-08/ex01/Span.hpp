#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>

class Span
{
    private:
        unsigned int maxSize;
        std::vector<int> number;
    public:
        Span(unsigned int n);
        Span(const Span& copy);
        Span(const Span& other);
        ~Span();
        
        int addNumber() const;
        int shortestSpan() const;
};









#endif