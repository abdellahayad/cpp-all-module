#include "easyfind.hpp"

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(10);
    v.push_back(20);
    
    const std::vector<int> v2 = v;
    
    try
    {
        std::vector<int>::iterator it = easyfind(v, 10);
        std::cout << "Found value: " << *it << std::endl; 

        std::vector<int>::const_iterator it2 = easyfind(v2, 100);
        std::cout << "Found value: " << *it2 << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}