/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:11 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/02 12:02:14 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/* ------------ same constructors/destr as in ex00 ------------------------*/

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

/* ------------- new constructor -------------------------------*/
/**
 * Constructor that takes a constant integer as a parameter.
 * It converts it to the corresponding fixed-point value. 
*/
Fixed::Fixed(int n)
{
    std::cout << "Int constructor called" << std::endl;
    _raw = n << _fracBits; // scale = 256
}

/**
 * Constructor that takes a constant floating-point number as a parameter.
 * It converts it to the corresponding fixed-point value. 
*/
Fixed::Fixed(float f)
{
    std::cout << "Float constructor called" << std::endl;
    _raw = static_cast<int>(roundf(f * (1 << _fracBits)));
};

/* -------------------- New convertion functions -----------------*/
float Fixed::toFloat(void) const
{
    return static_cast<float>(_raw) / static_cast<float>(1 << _fracBits);
}

int Fixed::toInt(void) const
{
    return _raw >> _fracBits; // divide by 256 (truncate toward zero)
}

/* ------------ Getter - Setter: same functions as in ex00 ------------------------*/

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

// --- operator<< prints the floating representation ---
std::ostream& operator<<(std::ostream& os, const Fixed& x)
{
    return os << x.toFloat();
}