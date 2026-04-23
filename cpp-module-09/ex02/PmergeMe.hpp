#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>

class PmergeMe
{
private:
    std::vector<int> vec;
    std::list<int> lst;
public:
    PmergeMe();
    PmergeMe(const PmergeMe& copy);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();


    void parsInput(int ac, char **av);
    void printBefore() const;
};



#endif