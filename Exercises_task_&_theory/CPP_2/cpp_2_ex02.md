# CPP Module 2 - Ex 01 - Overloading all of it.

## TASK 

1. Extend your Fixed class (fixed-point with 8 fractional bits) so it behaves like a number; it must support 
	- comparisons (` >, <, >=, <=, ==, and !=`), 
	- arithmetic (`+,-, *, and /`), and 
	- increment/decrement (`pre/post ++/--`) which will change the value by the smallest epsilon (i.e., one LSB of your fixed format).  
2. Provide 4 static member functions that work as min/max helpers
    - that take two references to fixed-point numbers or  constant fixed-point
 numbers,  
    -  returns a reference to the smallest/greates one.

3. Other constrains: 
- Follow OCF and the other general rules for this C++ projects.
- only `roundf`from <cmath> is allowed.

<details> <summary> Click for Main.cpp </summary> 

```cpp
#include <iostream> 
int	main( void ) 
{
	Fixed a; 
	.Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) ); 
	
	std::cout << a << std::endl; 
	std::cout << ++a << std::endl; 
	std::cout << a << std::endl; 
	std::cout << a++ << std::endl; 

	std::cout << a << std::endl; 
	std::cout << b << std::endl; 

	std::cout << Fixed::max( a, b ) << std::endl; 
	
	return 0; 
}
```
</details>

<details> <summary> Click for Expected output </summary> 

```shell
$> ./a.out 
0
0.00390625 
0.00390625 
0.00390625 
0.0078125 
10.1016 
10.1016 
$>
```
</details>

---

## Comparison operators ⚖️

### What is going on with the parameters?
At first glance you may think they take "1 parameter"

```cpp
bool operator>(Fixed const& rhs) const;
```
But it´s an illusion. The left-hand side is the implicit object [*this]; the right-hand side is the single parameter rhs.

So when you write `a > b`, what gets called is: 

```cpp
a.operator>(b);   // lhs is *this == a, rhs is b
```
### Implicit conversion of non-objects
`a > 2` works thanks to the converting constructor Fixed(int): the 2 is converted to a temporary Fixed, then `a.operator>(temp)` runs.
Same thing for float, as long as we maintain the extra constructor for float.

### #include <iomanip>

This is a standard C++ header from the I/O manipulators library.
It provides tools to format input/output streams (std::cout, std::cin).

Examples of manipulators it gives you:

1. std::boolalpha → print true/false instead of 1/0.

```
std::cout << true;          // prints "1" by default
std::cout << std::boolalpha << true;  // prints "true"
```

2. std::setprecision(n) → control how many significant digits are printed for floating-point numbers.
Sets the floating-point precision to 8 significant digits when printing floats/doubles.
By default, cout may print only 6 digits.
```
float x = 10.1015625;
std::cout << x << "\n";                 // 10.1016 (rounded, 6 digits)
std::cout << std::setprecision(8) << x; // 10.101563 (more digits shown)
```

3. std::setw(n) → set field width.

4. std::setfill(c) → choose the fill character.

5. std::hex, std::dec, std::oct → switch number base.

---

## Arithmetics  🧮

Addition ➕ and substraction ➖ are quite straighforward. They don´t need to be talked about.
Multiplication and division is another thing as the program IS constructing the objects as fixed-point numbers.

> Keep in mind that: 
A real number X is stored as `_raw = round(num * S)`.
According to subject, _fracBits = 8, so the `scale (S) is 256`.

### Multiplication ✖️
In real numbers:  (A * B)   
In _raw : 
- a_raw = round(A * S)
- b_raw = round(B * S)

```cpp
a_raw * b_raw = (A*S) * (B*S) = (A*B) * S^2
```
As it is necessary to make that `^2` disappear. Therefore, divide by S once.  
```cpp
r_raw = (a_raw * b_raw) / S;
```

In code, dividing by S is a right shift by _fracBits:
```cpp
r._raw = (a_raw * b_raw) >> _fracBits;
```

⚠️ ***Important:***
- `>>` n divides by 2^n,  
- `<<` n multiplies by 2^n.
- casting to long (or long long) is advice to reduce overflow risk. 

### Division 

You want (A / B) in real numbers. In raw:

a_raw / b_raw ≈ (A*S)/(B*S) = A/B


But that loses the S scale. To keep the result at scale S, multiply the numerator by S first:

r_raw = (a_raw * S) / b_raw;


In code, multiplying by S is a left shift by _fracBits:

r._raw = (a_raw << _fracBits) / b_raw;


(And yes, per the subject, divide-by-zero may crash; it’s acceptable in this exercise.)