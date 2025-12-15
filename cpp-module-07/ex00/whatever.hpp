#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <string>
#include <iostream>

template <typename t>
void swap(t &a, t &b)
{
    t tmp = a;
    a = b;
    b = tmp;
}
template <typename t>
t min(t const &a, t const  &b)
{
    if (a < b)
        return a;
    return b;
}

template <typename t>
t max(t const &a, t const b)
{
    if (a > b)
        return a;
    return b;
}


#endif