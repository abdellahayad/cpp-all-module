#include "Span.hpp"
#include <list>


int main()
{
    try
    {
        int max;
        int min;

        Span v(6);
        v.addNumber(1);
        v.addNumber(20);
        v.addNumber(30);
        v.addNumber(40);
        v.addNumber(50);
        v.addNumber(600);

        max = v.longestSpan();
        min = v.shortestSpan();
        std::cout << "max: " << max << std::endl;
        std::cout << "min: " << min << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << "==========" << std::endl;
    try
    {
        int max;
        int min;

        Span s(10000);
        std::vector<int> ve;
        for (size_t i = 1; i <= 10000; i++)
            ve.push_back(i * 3);
        
        s.addRange(ve.begin(), ve.end());
        min = s.shortestSpan();
        max = s.longestSpan();
        std::cout << "max: " << max << std::endl;
        std::cout << "min: " << min << std::endl;
        
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

        Span v(10);
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
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    
}