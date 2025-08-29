#include <iostream>
#include "Fixed.hpp"

int main(void)
{
	std::cout << "-------------- Create (a)  -----------" << std::endl;
    Fixed a;
	std::cout << "----- Create (b) --> b( 10 ) ---------" << std::endl;
	Fixed const b( 10 );
	std::cout << "----- Create (c) -> c( 42.42f ) ------" << std::endl;
    Fixed const c( 42.42f );
	std::cout << "----- Create (d) -> copy of (b) ------" << std::endl;
    Fixed const d( b );

	std::cout << "--- Change value of (a) -> a = Fixed( 1234.4321f ) -----" << std::endl;
    a = Fixed( 1234.4321f );

	std::cout << " ======================================================" << std::endl;

	std::cout << "---- Streaming values - Right operand = object Fixed ----" << std::endl;
	std::cout << "-----------  Triggers << overloading -------------------" << std::endl;
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << "---- Overload stream = all output is float ----" << std::endl;

	std::cout << " ======================================================" << std::endl;

	std::cout << "---- Streaming values - Right operand = [object].toInt() ----" << std::endl;
	std::cout << "--------- !! DOES NOT !! Triggers << overloading -----------" << std::endl;
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	std::cout << "---- toInt() was call for every object == all int output ----" << std::endl;

    return 0;
}


/*
int main(void)
{
    Fixed a;
    Fixed const b( 10 );
    Fixed const c( 42.42f );
    Fixed const d( b );
    
    a = Fixed( 1234.4321f );
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;
    return 0;
}
*/