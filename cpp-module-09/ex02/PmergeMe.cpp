#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& copy) : vec(copy.vec) {}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {if (this != &other) vec = other.vec; return *this;}


static bool isNumber(const char *str)
{
    if (str[0] == '\0') 
        return false;
    int i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

void PmergeMe::parsInput(int ac, char **av)
{
    if (ac < 2)
        throw std::runtime_error("Error!");
    
    for (int i = 1; i < ac ; i++)
    {
        if (!isNumber(av[i]))
            throw std::runtime_error("Error!");
        long num = strtol(av[i], NULL, 10);
        if (num < 0 || num > INT_MAX)
            throw std::runtime_error("Error!");
        if (std::find(vec.begin(), vec.end(), static_cast<int>(num)) != vec.end())
            throw std::runtime_error("Error: duplicate!");
        vec.push_back(static_cast<int>(num));
        lst.push_back(static_cast<int>(num));
    }  
}
void PmergeMe::printBefore() const
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    
}