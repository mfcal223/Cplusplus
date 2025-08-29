#include <iostream>
#include "Fixed.hpp"

int main(void)
{
    std::cout << std::boolalpha << std::setprecision(8);

	std::cout << "-------------- Create (a) : no value  -----------" << std::endl;
	Fixed a; 
	std::cout << "a = " << a << std::endl; 

	std::cout << "-------------- Create (b) : Fixed( 5.05f ) * Fixed( 2 ) -------" << std::endl;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) ); 
	std::cout << "b = " << b << std::endl; 

	std::cout << "-------------- Comparisons tests (FIXED VS FIXED) -------" << std::endl;
	std::cout << "a < b  : " << (a < b)  << std::endl;
    std::cout << "a > b  : " << (a > b)  << std::endl;
	std::cout << "a <= b : " << (a <= b) << std::endl;
	std::cout << "a >= b : " << (a >= b) << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;

	std::cout << "-------------- Create (c) = (b)  -----------" << std::endl;
	Fixed c (b);
	std::cout << "c = " << c << std::endl; 
	std::cout << "b == c : " << (b == c) << std::endl;
	std::cout << "c > a  : " << (c > a)  << std::endl;
	std::cout << "-------------- Change value of (c)  -----------" << std::endl;
	c = 12.4f;
	std::cout << "c = " << c << std::endl;
	std::cout << "a != c : " << (a != c) << std::endl;
	std::cout << "b == c : " << (b == c) << std::endl;

	std::cout << "--------- Comparisons tests (implicit conversions) -------" << std::endl;
    std::cout << "a < 1      : " << (a < 1) << std::endl;          	// int -> Fixed
    std::cout << "b > 10     : " << (b > 10) << std::endl;         	// int -> Fixed
    std::cout << "c >= 5.1f : " << (c >= 10.1f) << std::endl;     	// float -> Fixed

	std::cout << " ======================================================" << std::endl;
	std::cout << "-------------- Arithmetic tests -------" << std::endl;

	Fixed d = Fixed(10) + Fixed(0.5f);
	Fixed e = Fixed(3.5f) - Fixed(1.25f);
	Fixed f = Fixed(3.5f) - Fixed(4);
	Fixed g = Fixed(2) * Fixed(4.25f);
	Fixed h = Fixed(5) / Fixed(2);           // avoid 0 to not crash - if 0 is added crashing is allowed
	std::cout << "10 + 0.5   = " << d << "\n";
	std::cout << "3.5 - 1.25 = " << e << "\n";
	std::cout << "3.5 - 4    = " << f << "\n";
	std::cout << "2 * 4.25   = " << g << "\n";
	std::cout << "5 / 2      = " << h << "\n";

	std::cout << " ======================================================" << std::endl;
	std::cout << "-------------- Increment & Decrement tests -------" << std::endl;
	std::cout << "----------------- (epsilon = 1/256) --------------" << std::endl;
	Fixed i (1);
	std::cout << "i = " << i << std::endl;
    std::cout << "++i      = " << ++i  << std::endl;
	std::cout << "i = " << i << std::endl;
    std::cout << "i++      = " << g++  << std::endl;
	std::cout << "i = " << i << std::endl;
    std::cout << "--i      = " << --g  << std::endl;
    std::cout << "i--      = " << g--  << std::endl;
	std::cout << "i = " << i << std::endl;

	/*
    // ---- Epsilon demo: (++1 - 1) should be 1/256 ----
    Fixed one(1);
    Fixed one_inc = one;
    ++one_inc;
    std::cout << "epsilon  = (++1 - 1) = " << (one_inc - one) << "\n";

    // ---- min / max (non-const & const overloads) ----
    Fixed x(1.5f), y(1.25f);
    Fixed const cx(3.0f), cy(3.75f);
    std::cout << "min(x,y) = " << Fixed::min(x, y)   << "\n"; // non-const
    std::cout << "max(x,y) = " << Fixed::max(x, y)   << "\n";
    std::cout << "min(cx,cy)= " << Fixed::min(cx, cy) << "\n"; // const
    std::cout << "max(cx,cy)= " << Fixed::max(cx, cy) << "\n";
	*/
	return 0; 

}


/*
#include <iostream> 
#include "Fixed.hpp"

int	main( void ) 
{
	Fixed a; 
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) ); 
	
	std::cout << a << std::endl; 
	std::cout << ++a << std::endl; 
	std::cout << a << std::endl; 
	std::cout << a++ << std::endl; 

	std::cout << a << std::endl; 
	std::cout << b << std::endl; 

	std::cout << Fixed::max( a, b ) << std::endl; 
	
	return 0; 
}
*/