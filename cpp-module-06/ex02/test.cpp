#include "base.hpp"
#include <ctime>

int rnm()
{
    std::cout << std::rand() % 100 << std::endl;
    return 0;
}

int main()
{
    std::srand(std::time(NULL));
    rnm();
}