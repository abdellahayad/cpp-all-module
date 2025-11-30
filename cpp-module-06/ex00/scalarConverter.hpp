#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <exception>
#include <cmath>
#include <climits>
#include <sstream>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &copy);
        ScalarConverter& operator=(const ScalarConverter &other);

    public:
        static void convert(const std::string &literal);
};

class ScalarConverterException : public std::exception
{
    public:
        const char *what() const throw();
};


#endif