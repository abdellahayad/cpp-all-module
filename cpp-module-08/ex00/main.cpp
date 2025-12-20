#include "easyfind.hpp"

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(10);
    v.push_back(20);

    try
    {
        std::vector<int>::iterator it = easyfind(v, 100);
        std::cout << "Found value: " << *it << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}