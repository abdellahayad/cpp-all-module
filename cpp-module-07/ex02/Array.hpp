#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>


template <typename t>
class Array
{
private:
    t* array;
    unsigned int _size;
public:
    Array() : array(NULL), _size(0) {}

    Array(unsigned int n): array(NULL),  _size(n)
    {
        if (n > 0)
            array = new t[n]();
    }

    Array(const Array& copy)  : array(NULL)
    {
        _size = copy._size;
        array = new t[_size];
        for (unsigned int i = 0; i < _size; i++)
            array[i] = copy.array[i];
    }

    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            delete[] array;
            _size = other._size;
            if (_size > 0)
                array = new t[_size];
            else
                array = NULL;
            for (unsigned int i = 0; i < _size; i++)
                array[i] = other.array[i];
        }
        return *this;
    }

    ~Array() {delete[] array;}

    t& operator[](unsigned int index)
    {
        if (index >= _size)
            throw std::out_of_range("array index out of bounds");
        return (array[index]);
    }

    unsigned int size() const
    {
        return _size;
    }
};






#endif