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
void ft_toupper(std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
        str[i] = std::toupper(str[i]);
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

    std::string str[] = {"abdellah", "ayad", "yassine"};
    iter(str, 3, print<std::string>);
    iter(str, 3, ft_toupper);
    iter(str, 3, print<std::string>);

    return 0;
}
