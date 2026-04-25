#include "PmergeMe.hpp"

int main(int ac, char ** av)
{
    try
    {
        PmergeMe merge;

        merge.parsInput(ac, av);
        merge.printBefore();
        merge.generateJacobsthal(30);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}