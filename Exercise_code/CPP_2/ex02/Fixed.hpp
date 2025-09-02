/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:01:20 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/02 12:01:21 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iosfwd>		// forward declare std::ostream
#include <iomanip>		// I/O manipulators library
#include <iostream>		// to use cout
#include <cmath>		// needed this for roundf

class Fixed
{
private:
	int					_raw;
	static const int	_fracBits;

public:
	Fixed();							// Default constructor
	Fixed(const Fixed& other);			// Copy constructor
	Fixed& operator=(const Fixed& other);	// Copy assignment
	~Fixed();							// Destructor

	Fixed(int n);						// Int constructor
	Fixed(float f);						// Float constructor
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	float	toFloat( void ) const;		// fixed -> float
	int		toInt( void ) const;		// fixed -> int

	/* ------ NEW OPERATORS -----------*/
	// Comparison operators
	bool operator>(Fixed const& rhs) const;
	bool operator<(Fixed const& rhs) const;
	bool operator>=(Fixed const& rhs) const;
	bool operator<=(Fixed const& rhs) const;
	bool operator==(Fixed const& rhs) const;
	bool operator!=(Fixed const& rhs) const;

    // Arithmetic operators
	Fixed operator+(Fixed const& rhs) const;
	Fixed operator-(Fixed const& rhs) const;
	Fixed operator*(Fixed const& rhs) const;
	Fixed operator/(Fixed const& rhs) const;

    // ++ / -- (pre & post)
	Fixed& operator++();    // pre-increment
	Fixed  operator++(int); // post-increment
	Fixed& operator--();    // pre-decrement
	Fixed  operator--(int); // post-decrement

    // min / max (overloads)
	static Fixed&       min(Fixed& a, Fixed& b);
	static Fixed const& min(Fixed const& a, Fixed const& b);
	static Fixed&       max(Fixed& a, Fixed& b);
	static Fixed const& max(Fixed const& a, Fixed const& b);
};

// Non-member stream insertion operator
std::ostream& operator<<(std::ostream& os, const Fixed& x);

#endif

// rhs = right hand side