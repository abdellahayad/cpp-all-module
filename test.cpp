#include <iostream>
#include <limits>
#include <cmath>


int main()
{
    std::cout << "float: ";
    double d = 0.0 / 0.0;
    if (std::isnan(d))
        std::cout << "nanf" << std::endl;
    else if (std::isinf(d) && d > 0)
        std::cout << "+inff" << std::endl;
    else if (std::isinf(d) && d < 0)
        std::cout << "-inff" << std::endl;
    else if (d == static_cast<int>(d))
        std::cout << static_cast<int>(d) << ".0f" << std::endl;
    else
        std::cout << static_cast<float>(d) << "f" << std::endl;
}




#include "scalarConverter.hpp"

// ------------------- DETECT TYPES -------------------

static bool is_char(const std::string& s)
{
    return (s.size() == 1 && !isdigit(s[0]));
}

static bool is_int(const std::string& s)
{
    std::istringstream iss(s);
    int n;
    iss >> n;
    return (iss.eof() && !iss.fail());
}

static bool is_float(const std::string& s)
{
    if (s == "+inff" || s == "-inff" || s == "nanf")
        return true;

    if (s[s.size() - 1] != 'f')
        return false;

    std::string core = s.substr(0, s.size() - 1);
    std::istringstream iss(core);
    float f;
    iss >> f;
    return (iss.eof() && !iss.fail());
}

static bool is_double(const std::string& s)
{
    if (s == "+inf" || s == "-inf" || s == "nan")
        return true;

    std::istringstream iss(s);
    double d;
    iss >> d;
    return (iss.eof() && !iss.fail());
}


// ------------------- PRINT FUNCTIONS -------------------

static void print_char(double d)
{
    std::cout << "char: ";
    if (std::isnan(d) || d < 0 || d > 255)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(d)))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
}

static void print_int(double d)
{
    std::cout << "int: ";
    if (std::isnan(d) || d < INT_MIN || d > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(d) << std::endl;
}

static bool is_integer(double d)
{
    return (!std::isnan(d) && d == static_cast<int>(d));
}

static void print_float(double d)
{
    std::cout << "float: ";
    if (std::isnan(d))
        std::cout << "nanf" << std::endl;
    else if (std::isinf(d) && d < 0)
        std::cout << "-inff" << std::endl;
    else if (std::isinf(d) && d > 0)
        std::cout << "+inff" << std::endl;
    else if (is_integer(d))
        std::cout << static_cast<int>(d) << ".0f" << std::endl;
    else
        std::cout << static_cast<float>(d) << "f" << std::endl;
}

static void print_double(double d)
{
    std::cout << "double: ";
    if (std::isnan(d))
        std::cout << "nan" << std::endl;
    else if (std::isinf(d) && d < 0)
        std::cout << "-inf" << std::endl;
    else if (std::isinf(d) && d > 0)
        std::cout << "+inf" << std::endl;
    else if (is_integer(d))
        std::cout << static_cast<int>(d) << ".0" << std::endl;
    else
        std::cout << d << std::endl;
}


// ------------------- CONVERTER -------------------

void ScalarConverter::convert(const std::string& literal)
{
    double value;

    if (is_char(literal))
        value = literal[0];
    
    else if (is_int(literal))
    {
        std::stringstream ss(literal);
        ss >> value;
    }

    else if (is_float(literal))
    {
        if (literal == "+inff")
            value = std::numeric_limits<double>::infinity();
        else if (literal == "-inff")
            value = -std::numeric_limits<double>::infinity();
        else if (literal == "nanf")
            value = std::numeric_limits<double>::quiet_NaN();
        else 
        {
            std::string core = literal.substr(0, literal.size() - 1);
            std::stringstream ss(core);
            ss >> value;
        }
    }

    else if (is_double(literal))
    {
        if (literal == "+inf")
            value = std::numeric_limits<double>::infinity();
        else if (literal == "-inf")
            value = -std::numeric_limits<double>::infinity();
        else if (literal == "nan")
            value = std::numeric_limits<double>::quiet_NaN();
        else
        {
            std::stringstream ss(literal);
            ss >> value;
        }
    }

    else
        throw scalarConverterException();

    print_char(value);
    print_int(value);
    print_float(value);
    print_double(value);
}


// ------------------- EXCEPTION -------------------

const char* scalarConverterException::what() const throw()
{
    return "Invalid literal";
}
