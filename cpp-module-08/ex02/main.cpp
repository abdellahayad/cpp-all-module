#include <iostream>
#include <stack>
#include <vector>
#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    std::cout << "===========" << std::endl;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::cout << "===========" << std::endl;
    std::stack<int> s(mstack);
    while(!s.empty())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }
    std::cout << "===========" << std::endl;
    MutantStack<int> empty;
    if (empty.begin() == empty.end())
        std::cout << "stack is empty" << std::endl;
    
    std::cout << "===========" << std::endl;
    MutantStack<std::string> strs;
    for (int i = 0; i < 100; i++)
        strs.push("ayad");
    int i = 1;
    for (MutantStack<std::string>::iterator it = strs.begin(); it != strs.end(); it++)
        std::cout << *it << " " << i++ << std::endl;

    std::cout << "===========" << std::endl;
    MutantStack<int> rstack;
    rstack.push(10);
    rstack.push(20);
    rstack.push(30);
    rstack.push(40);
    MutantStack<int>::reverse_iterator rit = rstack.rbegin();
    MutantStack<int>::reverse_iterator rite = rstack.rend();
    while (rit != rite)
    {
        std::cout << *rit << std::endl;
        rit++;
    }

    return 0;
}