#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <iostream>
#include <string>
#include <stdint.h>

struct Data
{
    int number;
    std::string name;
};

class Serializer
{
private:
    Serializer();
    Serializer(const Serializer &copy);
    Serializer &operator=(const Serializer &other);
    ~Serializer();

public:
    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);
};

#endif