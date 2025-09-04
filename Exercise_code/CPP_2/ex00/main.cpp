/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:33 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/04 11:11:23 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int	main( void ) 
{
	std::cout << CYAN << "-----Create (a)  ------" << ERASE << std::endl;
	Fixed a;
	std::cout << a.getRawBits() << " = a " << std::endl;

	std::cout << CYAN << "---New object {b} created as a copy of {a} [b(a)] ---" 
					<< ERASE << std::endl;
	Fixed b( a );
	std::cout << b.getRawBits() <<  " = b" << std::endl;

	std::cout << MAGENTA << "----- Change value of (b) ------" << ERASE << std::endl;
	b.setRawBits(42);
	std::cout << b.getRawBits() <<  " = b" << std::endl;

	std::cout << CYAN << "-----Create (c) ------" << ERASE << std::endl;
	Fixed c;
	std::cout << c.getRawBits() << " = c " << std::endl;
    std::cout << CYAN << "----Assign {c} to be like {b} (c = b) -----" << ERASE << std::endl;
	c = b;
	std::cout << b.getRawBits() <<  " = b" << std::endl;
	std::cout << c.getRawBits() <<  " = c" << std::endl;

	std::cout << MAGENTA << "----- Change value of (c) (c = a) ------" << ERASE << std::endl;
	c = a;
	std::cout << a.getRawBits() << " = a " << std::endl;
	std::cout << c.getRawBits() <<  " = c" << std::endl;

	std::cout << RED << "-----Final values of a / b / c  ------" << ERASE << std::endl;
	std::cout << a.getRawBits() << " = a " << std::endl;
	std::cout << b.getRawBits() << " = b" << std::endl;
	std::cout << c.getRawBits() << " = c" << std::endl;

	std::cout << YELLOW << "--End of Function - a/b/c go out of scope--" << ERASE << std::endl;

	return 0;
}

/*
//main as seen on subject 
int	main( void ) 
{
	Fixed a;
	Fixed b( a );
	Fixed c;
	c = b;
	
	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;
	return 0;
}
*/