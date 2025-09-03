/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:59:21 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 14:11:43 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Fixed.hpp"

/* ------------ same constructors/destr as in ex00 ------------------------------*/

const int Fixed::_fracBits = 8;

// Default constructor
Fixed::Fixed() : _raw(0)
{
   // std::cout << "Default constructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other) : _raw(other._raw)
{
    //std::cout << "Copy constructor called" << std::endl;
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other)
{
   // std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->_raw = other._raw;
    return *this;
}

// Destructor
Fixed::~Fixed()
{
   // std::cout << "Destructor called" << std::endl;
}

/* ------ EXTRA CONSTRUCTORS FOR INT AND FLOAT  - from ex01------------------------*/
/**
 * Constructor that takes a constant integer as a parameter.
 * It converts it to the corresponding fixed-point value. 
*/
Fixed::Fixed(int n)
{
    //std::cout << "Int constructor called" << std::endl;
    _raw = n << _fracBits; // scale = 256
}

/**
 * Constructor that takes a constant floating-point number as a parameter.
 * It converts it to the corresponding fixed-point value. 
*/
Fixed::Fixed(float f)
{
    //std::cout << "Float constructor called" << std::endl;
    _raw = static_cast<int>(roundf(f * (1 << _fracBits)));
};

/* -------------------- Convertion functions - same ex01 -------------------------*/
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

/* --- OVERLOADING OPERATOR << for fixed binded objects as in ex01 -------------- */
std::ostream& operator<<(std::ostream& os, const Fixed& x)
{
    return os << x.toFloat();
}

/* --------------------------- COMPARISONS ---------------------------------------*/
bool Fixed::operator>(Fixed const& rhs) const { return _raw > rhs._raw; }
bool Fixed::operator<(Fixed const& rhs) const { return _raw < rhs._raw; }
bool Fixed::operator>=(Fixed const& rhs) const { return _raw >= rhs._raw; }
bool Fixed::operator<=(Fixed const& rhs) const { return _raw <= rhs._raw; }
bool Fixed::operator==(Fixed const& rhs) const { return _raw == rhs._raw; }
bool Fixed::operator!=(Fixed const& rhs) const { return _raw != rhs._raw; }


/* --------------------------- ARITHMETICS ---------------------------------------*/

// Keep all math in fixed domain to preserve precision where possible.
Fixed Fixed::operator+(Fixed const& rhs) const 
{
    Fixed r; 
    r._raw = _raw + rhs._raw; 
    return r;
}
Fixed Fixed::operator-(Fixed const& rhs) const 
{
    Fixed r;
    r._raw = _raw - rhs._raw; 
    return r;
}
Fixed Fixed::operator*(Fixed const& rhs) const 
{
    long a = _raw;
    long b = rhs._raw;
    Fixed res;
    res._raw = static_cast<int>((a * b) >> _fracBits);
    return res;
}
Fixed Fixed::operator/(Fixed const& rhs) const
{
	if (rhs._raw == 0) 
	{
		std::cerr << "Error: Division by zero!" << std::endl;
		return Fixed(0);
    }
    long a = _raw;
    long b = rhs._raw;
    Fixed res;
    res._raw = static_cast<int>((a << _fracBits) / b);
    return res;
}