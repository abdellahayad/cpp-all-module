#include "scalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        
        if (argc != 2)
        {
            std::cout << "Usage: ./convert <literal>" << std::endl;
            return 1;
        }
    
        ScalarConverter::convert(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}