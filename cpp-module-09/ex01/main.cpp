#include "RPN.hpp"



int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: ./RPN <rpn_expresion>" << std::endl;
        return 1;
    }

    try
    {
        RPN rpn;

        int res = rpn.calculate(av[1]);
        
        std::cout << res << std::endl;

        return 0;
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
}