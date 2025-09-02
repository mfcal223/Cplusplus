/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:15 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/02 12:02:16 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iosfwd>		// forward declare std::ostream
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
	Fixed& operator=(const Fixed& rhs);	// Copy assignment
	~Fixed();							// Destructor

	Fixed(int n);						// Int constructor
	Fixed(float f);						// Float constructor
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	float	toFloat( void ) const;		// fixed -> float
	int		toInt( void ) const;		// fixed -> int


};

// Non-member stream insertion operator
std::ostream& operator<<(std::ostream& os, const Fixed& x);

#endif

/*
And add the following function to the Fixed class files:
• Anoverload of the insertion («) operator that inserts a floating-point 
representation of the fixed-point number into the output stream object
passed as a parameter.
*/