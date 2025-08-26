#include <iostream>
#include "Fixed.hpp"
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

int	main( void ) 
{
	std::cout << "-----Create (a)  ------" << std::endl;
	Fixed a;
	std::cout << a.getRawBits() << " = a " << std::endl;

	std::cout << "-----New object {b} created as a copy of {a} [b(a)] ----" << std::endl;
	Fixed b( a );
	std::cout << b.getRawBits() <<  " = b" << std::endl;

	std::cout << "----- Change value of (b) ------" << std::endl;
	b.setRawBits(42);
	std::cout << b.getRawBits() <<  " = b" << std::endl;

	std::cout << "-----Create (c) ------" << std::endl;
	Fixed c;
    std::cout << "----Assign {c} to be like {b} (c = b) -----" << std::endl;
	c = b;
	std::cout << b.getRawBits() <<  " = b" << std::endl;
	std::cout << c.getRawBits() <<  " = c" << std::endl;

	std::cout << "----- Change value of (c) (c = a) ------" << std::endl;
	c = a;
	std::cout << a.getRawBits() << " = a " << std::endl;
	std::cout << c.getRawBits() <<  " = c" << std::endl;

	std::cout << "-----Final values of a / b / c  ------" << std::endl;
	std::cout << a.getRawBits() << " = a " << std::endl;
	std::cout << b.getRawBits() << " = b" << std::endl;
	std::cout << c.getRawBits() << " = c" << std::endl;

	std::cout << "--End of Function - a/b/c go out of scope--" << std::endl;

	return 0;
}
