#ifndef ITER_HPP
#define ITER_HPP


#include <string>
#include <iostream>


template <typename t, typename f>
void iter(t* array, const std::size_t length, f &fun)
{
    std::size_t i = 0;

    while (i < length)
    {
        fun(array[i]);
        i++;
    }
}

#endif


