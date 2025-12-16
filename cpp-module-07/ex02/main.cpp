#include "Array.hpp"

int main()
{
    try
    {
        Array<int> a(6);
        std::cout << "==========" << std::endl;
        for (unsigned int i = 0; i < a.size(); i++)
            std::cout << "a[" << i << "] = " << a[i] << std::endl;

        for (unsigned int i = 0; i < a.size(); i++)
            a[i] = i * 10;

        std::cout << "==========" << std::endl;
        for (unsigned int i = 0; i < a.size(); i++)
            std::cout << "a[" << i << "] = " << a[i] << std::endl;
        Array<int> b = a;
        b[0] = 42;
        std::cout << "a[0] = " << a[0] << std::endl;
        std::cout << "b[0] = " << b[0] << std::endl;

        std::cout << "==========" << std::endl;
        std::cout << a[10] << std::endl;
        std::cout << "==========" << std::endl;
    }

    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}