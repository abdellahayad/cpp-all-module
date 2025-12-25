#ifndef EASYFIND_HPP
#define EASYFIND_HPP


#include <iostream>
#include <vector>
#include <algorithm>


template <typename T>
typename T::iterator easyfind(T& type, int value)
{
    typename T::iterator it;
    it = std::find(type.begin(), type.end(), value);
    if (it == type.end())
        throw std::runtime_error("value not found in container");
    return it;
}

template <typename T>
typename  T::const_iterator easyfind(const T& type, int value)
{
    typename T::const_iterator it;
    it = std::find(type.begin(), type.end(), value);
    if (it == type.end())
        throw std::runtime_error("value not found in container");
    return it;
}


#endif