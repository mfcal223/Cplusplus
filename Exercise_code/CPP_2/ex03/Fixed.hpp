/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:59:24 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 14:11:01 by mcalciat         ###   ########.fr       */
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

};

std::ostream& operator<<(std::ostream& os, const Fixed& x);

#endif