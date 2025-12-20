#ifndef EASYFIND_HPP
#define EASYFIND_HPP


#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>


class notFound : public std::exception
{
    public:
        virtual const char *what() const throw()
        {
            return ("value not found in container");
        }
};

template <typename T>
typename T::iterator easyfind(T& type, int value)
{
    typename T::iterator it;
    it = std::find(type.begin(), type.end(), value);
    if (it == type.end())
        throw notFound();
    return it;
}




#endif