#include "iter.hpp"


template <typename t>
void print(const t& x)
{
    std::cout << x << std::endl;
}

void addOne(int &x)
{
    x++;
}

int main()
{
    int a[] = {1, 2 , 3};
    const int b[] = {10, 20, 30};

    iter(a, 3, print<int>);
    std::cout << "=====" << std::endl;
    iter(a, 3, addOne);
    iter(a, 3, print<int>);
    std::cout << "=====" << std::endl;
    iter(b, 3, print<int>);


    return 0;
}