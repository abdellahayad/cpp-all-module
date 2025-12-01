#include <iostream>
#include "serial.hpp"

int main()
{
    Data data;
    data.number = 1337;
    data.name = "Abdellah";

    std::cout << "origin pointer: " << &data << std::endl;

    uintptr_t raw = Serializer::serialize(&data);

    std::cout << "serial value: " << raw << std::endl;

    Data* restored = Serializer::deserialize(raw);

    std::cout << "restored pointer: " << restored << std::endl;

    if (restored == &data)
        std::cout << "<======OK======>\n";
    else
        std::cout << "<======KO======>\n";

    std::cout << "restored data: " << restored->number 
              << " | " << restored->name << std::endl;

    return 0;
}
