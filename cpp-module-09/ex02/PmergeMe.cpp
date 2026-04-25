#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &copy) : vec(copy.vec), lst(copy.lst) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
        vec = other.vec;
    lst = other.lst;
    return *this;
}

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

    for (int i = 1; i < ac; i++)
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

std::vector<int> PmergeMe::generateJacobsthal(int n)
{
    std::vector<int> jac;
    if (n == 0)
        return jac;
    jac.push_back(1);
    if (n == 1)
        return jac;
    jac.push_back(3);
    while (jac.back() < n)
    {
        int next = jac.back() + 2 * jac[jac.size() - 2];
        jac.push_back(next);
    }
    return jac;
}

void PmergeMe::run()
{
    std::cout << "Before: ";
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    clock_t startV = clock();
    std::vector<int> resV = sortVector(vec);
    clock_t endV = clock();

    clock_t startL = clock();
    std::list<int> resL = sortList(lst);
    clock_t endL = clock();

    std::cout << "After: ";
    for (int i = 0; i < resV.size(); i++)
        std::cout << resV[i] << " ";
    std::cout << std::endl;
}

std::vector<int> PmergeMe::sortVector(std::vector<int> &v)
{
    if (v.size() <= 1)
        return v;
    
    std::vector<std::pair<int, int> > pair;
    int leftOvr = -1;
    bool hasLeft = (v.size() % 2 != 0);
    size_t limit = v.size();
    if (hasLeft)
        limit--;
    for (int i = 0; i < limit; i += 2)
    {
        if (v[i] > v[ + 1])
            pair.push_back(std::make_pair(v[i] , v[i + 1]));
        else
            pair.push_back(std::make_pair(v[i + 1] , v[i]));
    }
    if (hasLeft)
        leftOvr  = v.back();
    std::vector<int> winners;
    for (int i = 0; i < pair.size(); i++)
        winners.push_back(pair[i].first);
    std::vector<int> mainChain = sortVector(winners);
    return mainChain;
}

std::list<int> PmergeMe::sortList(std::list<int> &l)
{
    return l;
}