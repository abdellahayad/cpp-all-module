#include "Span.hpp"
#include <list>


int main()
{
    try
    {
        Span v(6);
        v.addNumber(1);
        v.addNumber(20);
        v.addNumber(30);
        v.addNumber(40);
        v.addNumber(50);
        v.addNumber(600);

        std::cout << "max: " << v.longestSpan() << std::endl;
        std::cout << "min: " << v.shortestSpan() << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << "==========" << std::endl;
    try
    {
        Span s(10000);
        std::vector<int> ve;
        for (size_t i = 0; i < 10000; i++)
            ve.push_back(i * 3);
        
        s.addRange(ve.begin(), ve.end());
        std::cout << "max: " << s.longestSpan() << std::endl;
        std::cout << "min: " << s.shortestSpan() << std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << "==========" << std::endl;
    try
    {
        int max;
        int min;

        Span v(600);
        std::list<int> l;
        for (int i = -10; i <= 20; i++)
            l.push_back(i);
        v.addRange(l.begin(), l.end());
        max = v.longestSpan();
        min = v.shortestSpan();
        std::cout << "max: " << max << std::endl;
        std::cout << "min: " << min << std::endl;
            
    }
    catch(const std::exception& e)
    {
        std::cout << "Error" << std::endl;
    }
    
    
}