#include "Fixed.hpp"

Fixed::Fixed() : fixdVal(0) {}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}
Fixed::Fixed(const float f)
{
    fixdVal = roundf(f * (1 <<  fracBits));
}


Fixed::Fixed(const int n) 
{
    fixdVal = n << fracBits;
}

Fixed::Fixed(const Fixed& other)
{
    *this = other;
}
Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
        fixdVal = other.fixdVal;
    return *this;
}

int Fixed::getRawBits(void) const
{
    return this->fixdVal;
}

void Fixed::setRawBits(int const raw)
{
    this->fixdVal = raw;
}
bool Fixed::operator>(const Fixed& other) const
{
    return (this->fixdVal > other.fixdVal);
}

std::ostream& operator<<(std::ostream& os, const Fixed& f)
{
    os << f.toFloat();
    return os;
}

int Fixed::toInt() const
{
    return (fixdVal >> fracBits);
}

float Fixed::toFloat() const
{
    return (fixdVal / (float)(1 << fracBits));
}

// The 6 comparison operators: >, <, >=, <=, ==, and !=.
bool Fixed::operator<(const Fixed& other) const
{
    return (this->fixdVal < other.fixdVal);
}

bool Fixed::operator>=(const Fixed& other)const
{
    return (this->fixdVal >= other.fixdVal);
}

bool Fixed::operator<=(const Fixed& other)const
{
    return (this->fixdVal <= other.fixdVal);
}

bool Fixed::operator==(const Fixed& other)const
{
    return (this->fixdVal == other.fixdVal);
}

bool Fixed::operator!=(const Fixed& other)const
{
    return (this->fixdVal != other.fixdVal);
}

// The 4 arithmetic operators: +, -, *, and /.
float Fixed::operator+(const Fixed& other) const
{
    return this->toFloat() + other.toFloat();
}

float Fixed::operator-(const Fixed& other) const
{
    return this->toFloat() - other.toFloat();
}

float    Fixed::operator*(Fixed other) const
{
    return (this->toFloat() * other.toFloat());
}

float    Fixed::operator/(Fixed other) const
{
    return (this->toFloat() / other.toFloat());
}

// The 4 increment/decrement
Fixed &Fixed::operator++()
{
    this->fixdVal += 1;
    return (*this);
}

Fixed &Fixed::operator--()
{
    this->fixdVal -= 1;
    return (*this);
}

Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    ++(*this);
    return tmp;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    --(*this);
    return tmp;
}

//min, max
Fixed &Fixed::min(Fixed &a, Fixed &b){return(a < b ? a : b);}
const Fixed &Fixed::min(const Fixed &a, const Fixed &b){return(a < b ? a : b);}
Fixed &Fixed::max(Fixed &a, Fixed &b){return(a > b ? a : b);}
const Fixed &Fixed::max(const Fixed &a, const Fixed &b){return(a > b ? a : b);}
