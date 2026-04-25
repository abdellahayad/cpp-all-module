#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <climits> 
#include <algorithm>

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
    void run();

    std::vector<int> sortVector(std::vector<int>& v);
    std::list<int> sortList(std::list<int>& l);
    std::vector<int> generateJacobsthal(int n);
};



#endif