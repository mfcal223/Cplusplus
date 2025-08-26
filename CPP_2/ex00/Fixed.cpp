#include "Fixed.hpp"
#include <iostream>

const int Fixed::_fracBits = 8;

// Default constructor
Fixed::Fixed() : _raw(0)
{
    std::cout << "Default constructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other) : _raw(other._raw)
{
    std::cout << "Copy constructor called" << std::endl;
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& rhs)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_raw = rhs._raw;
    return *this;
}

// Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// Get raw value (with trace, as seen in subject)
int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_raw;
}

// Set raw value (no trace required by subject)
void Fixed::setRawBits(int const raw)
{
    this->_raw = raw;
}
