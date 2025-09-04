# CPP Module 2 - Ex 02 - Overloading all of it.

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

### Division 

In real numbers: (A / B) 
In raw:
```cpp
A/B = a_raw / b_raw ≈ (A*S) / (B*S)
```

But that *loses the S scale*. To keep the result at scale S, multiply the numerator by S first:
```cpp
r_raw = (a_raw * S) / b_raw;
```

In code, multiplying by S is a left shift by _fracBits:
```cpp
r_raw = (a_raw << _fracBits) / b_raw;
```

--- 

⚠️ ***Important:***
- `>>` n divides by 2^n,  
- `<<` n multiplies by 2^n.
- casting to long (or long long) is advice to reduce overflow risk. 
- per the subject, divide-by-zero may crash; it’s acceptable in this exercise.

---

## Increment & Decrement

### What “epsilon (ϵ)” means

Subject says: `"your ++/-- must change the value by the smallest representable ϵ “such that 1 + ϵ > 1.”`

> How do we know what is that smallest representable ϵ ? 

The least significant bit (LSB) of _raw represents exactly `1`.   
Since the real value = _raw / 256, that LSB corresponds to `1/256`.  
So, **epsilon = value of the LSB in real units**.  

The smallest change you can make to _raw is +1 or -1.
That corresponds to a change in real value of `1 / S = 1 / 256 ≈ 0.00390625`.  

* `++_raw`; → adds 1 to raw → adds epsilon (1/256) to real value.
* `--_raw`; → subtracts epsilon.

### Pre or Post operator?

Pre or postfix operator have an impact on the value of the variable at the time it is used.  

Pre-increment operator (++a / --a): the prefix operator says first increment the value then use it. This means the value is increased by 1 for the operation then the value is used by the variable.

Post- increment operator (a++ / a--): says that first use the value and then increment it. This means the value is first used up for the operation then the value is updated by 1.  

#### Why post-increment uses a temp?
C++ semantics require:
- Pre-increment (++x) → increment and return the new value (by reference).
- Post-increment (x++) → return the old value, but still increment the object.

```cpp
Fixed Fixed::operator++(int) {
    Fixed tmp(*this);  // copy old value
    ++_raw;            // increment current object
    return tmp;        // return old value
}
```

So:
```cpp
Fixed x(1);   // ≈ 1.0
std::cout << x++ << std::endl;  // prints 1.0 (old)
std::cout << x   << std::endl;  // prints 1.00390625 (incremented)
```

#### Why postfix prototypes have (int) as parameter?
Post-fix prototypes have a dummy INT as parameter as a syntactic tag the compiler uses to differentiate between ++x and x++
It is a tric C++ uses to distinguish the 2 overloads.

```cpp
x++;   // compiler looks for operator++(int)
++x;   // compiler looks for operator++()
```
### Why prefix and postfix have different return type?

- Pre-increment / decrement return by reference (`return *this;`):  
This is because **++x means “increment x, then use x”.**
Returning a reference allows chaining without extra copies:  
```cpp
(++x).toFloat();   // works directly on x
++(++x);           // increments twice
```
No need to return a copy, because we want to keep working on the modified x.  

- Post-increment/decrement returns by value (`return tmp;`):  
`x++` means **“use the old value of x, but still increment x afterward”.**
So you must return a copy (value) of the object before it changed.  
That’s why it returns by value: you can’t safely return a reference to the old value, because that state doesn’t exist anymore after the increment.  

```cpp
Fixed a(1);

// Pre-increment
std::cout << ++a << std::endl; // prints 1.00390625
std::cout << a    << std::endl; // also 1.00390625

// Post-increment
std::cout << a++ << std::endl; // prints 1.00390625 (old)
std::cout << a   << std::endl; // prints 1.0078125 (new)
```

---

## Max / Min Helpers

As I am now allowed to use ternary conditional operators, I will use that to include the max/min helpers required by subject.

### Ternary Conditional Operator

The `? :` operator is constructed like this:  

```yaml
(condition) ? value_if_true : value_if_false;

If condition is [true] → expression evaluates to value_if_true.
If condition is [false] → expression evaluates to value_if_false.
```

Example in plain numbers
```cpp
int a = 5;
int b = 10;

int min = (a < b) ? a : b;  // condition is true → picks a (5)
int max = (a > b) ? a : b;  // condition is false → picks b (10)
```

This is like coding :
```cpp
int min;
if (a < b)
    min = a;
else
    min = b;

int max;
if (a > b)
	max = a;
else
	max = b;
```

### Why two overloads (non-const and const)?

1. Fixed& min(Fixed& a, Fixed& b) → used when arguments are non-const (you can modify the returned object).
2. Fixed const& min(Fixed const& a, Fixed const& b) → used when arguments are const (cannot modify).

This is required so that both situations compile correctly.  
```cpp
Fixed x, y;
Fixed& m = Fixed::min(x, y);  // non-const overload
```

and
```cpp
Fixed const cx, cy;
Fixed const& m = Fixed::min(cx, cy);  // const overload
```

If the program would hold only the non-const version, when trying to compare a const& variable, you would get a error similar to this:

```shell
error: invalid initialization of reference of type ‘Fixed&’ from expression of type ‘const Fixed’
note: candidate function not viable: 1st argument ('const Fixed') would lose const qualifier
```

---


