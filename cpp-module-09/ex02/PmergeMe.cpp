#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &copy) : vec(copy.vec), lst(copy.lst) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {

        vec = other.vec;
        lst = other.lst;
    }
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
    jac.push_back(1);
    jac.push_back(3);
    while (jac.back() < n)
    {
        int next = jac.back() + 2 * jac[jac.size() - 2];
        jac.push_back(next);
    }
    return jac;
}

std::vector<int> PmergeMe::sortVector(std::vector<int> &v)
{
    if (v.size() <= 1)
        return v;

    std::vector<std::pair<int, int>> pair;
    int leftOvr = -1;
    bool hasLeft = (v.size() % 2 != 0);
    size_t limit = v.size();
    if (hasLeft)
        limit--;
    for (int i = 0; i < limit; i += 2)
    {
        if (v[i] > v[i + 1])
            pair.push_back(std::make_pair(v[i], v[i + 1]));
        else
            pair.push_back(std::make_pair(v[i + 1], v[i]));
    }
    if (hasLeft)
        leftOvr = v.back();
    std::vector<int> winners;
    for (int i = 0; i < pair.size(); i++)
        winners.push_back(pair[i].first);
    std::vector<int> mainChain = sortVector(winners);

    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); i++)
    {
        for (size_t j = 0; j < pair.size(); j++)
        {
            if (mainChain[i] == pair[j].first)
            {
                pend.push_back(pair[j].second);
                break;
            }
        }
    }

    std::vector<int> result = mainChain;
    std::vector<int> jac = generateJacobsthal(pend.size());
    result.insert(result.begin(), pend[0]);
    std::vector<bool> inserted(pend.size(), false);
    inserted[0] = true;

    for (size_t i = 0; i < jac.size(); i++)
    {
        int target = std::min(jac[i], (int)pend.size());
        for (int j = target - 1; j >= 0; j--)
        {
            if (!inserted[j])
            {
                result.insert(std::lower_bound(result.begin(), result.end(), pend[j]), pend[j]);
                inserted[j] = true;
            }
        }
    }

    if (hasLeft)
        result.insert(std::lower_bound(result.begin(), result.end(), leftOvr), leftOvr);
    return result;
}

std::list<int> PmergeMe::sortList(std::list<int> &l)
{
    if (l.size() <= 1)
        return l;

    std::list<std::pair<int, int>> pair;
    int leftOvr = -1;
    bool hasLeft = (l.size() % 2 != 0);

    size_t limit = l.size();
    if (hasLeft)
        limit--;
    std::list<int>::iterator it = l.begin();
    for (size_t i = 0; i < limit; i += 2)
    {
        int first = *it++;
        int second = *it++;

        if (first > second)
            pair.push_back(std::make_pair(first, second));
        else
            pair.push_back(std::make_pair(second, first));
    }
    if (hasLeft)
        leftOvr = l.back();

    std::list<int> winners;
    for (std::list<std::pair<int, int>>::iterator itr = pair.begin(); itr != pair.end(); ++itr)
        winners.push_back(itr->first);

    std::list<int> mainChain = sortList(winners);

    std::list<int> pend;
    for (std::list<int>::iterator mit = mainChain.begin(); mit != mainChain.end(); ++mit)
    {
        for (std::list<std::pair<int, int>>::iterator pit = pair.begin(); pit != pair.end(); ++pit)
        {
            if (*mit == pit->first)
            {
                pend.push_back(pit->second);
                break;
            }
        }
    }
    std::list<int> result = mainChain;
    std::vector<int> pendVec(pend.begin(), pend.end());
    std::vector<int> jac = generateJacobsthal(pendVec.size());

    result.push_front(pendVec[0]);
    std::vector<bool> inserted(pendVec.size(), false);
    inserted[0] = true;

    for (size_t i = 0; i < jac.size(); i++)
    {
        int target = std::min(jac[i], (int)pendVec.size());
        for (int j = target - 1; j >= 0; j--)
        {
            if (!inserted[j])
            {
                result.insert(std::lower_bound(result.begin(), result.end(), pendVec[j]), pendVec[j]);
                inserted[j] = true;
            }
        }
    }

    if (hasLeft)
        result.insert(std::lower_bound(result.begin(), result.end(), leftOvr), leftOvr);
    return result;
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

    // std::cout << "After: ";
    // for (size_t i = 0; i < resV.size(); i++)
    //     std::cout << resV[i] << " ";

    std::cout << "After: ";
    for (std::list<int>::iterator l = resL.begin(); l != resL.end(); ++l)
        std::cout << *l << " ";
    std::cout << std::endl;

    double timeV = static_cast<double>(endV - startV) / CLOCKS_PER_SEC * 1000000;
    double timeL = static_cast<double>(endL - startL) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeV << " us" << std::endl;
    std::cout << "Time to process a range of " << lst.size() << " elements with std::list   : " << timeL << " us" << std::endl;
}
