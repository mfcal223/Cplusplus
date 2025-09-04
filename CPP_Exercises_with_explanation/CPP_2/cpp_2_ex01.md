# CPP Module 2 - Ex 01 - Floating in weird place.

## TASK
1. Upgrade your Fixed class from ex00 so it behaves like a number: you must be able to build it from int and float, convert it back to int/float, and print it naturally with <<.
2. Constraints & structure:  
- Keep the internal storage as in ex00:
    - a private int holding the raw scaled value;
    - a static const int for the number of fractional bits, always 8.
- Keep the Orthodox Canonical Form (default ctor, copy ctor, copy assignment, dtor) and your split header/implementation.
- Keep/allow the raw accessors from ex00 (getRawBits() / setRawBits()).
3. What to add: 
- Constructors:  
    - Fixed(int n): store the fixed-point value corresponding to n. Hint: scale by 1 << _fracBits (i.e., 256).
    - Fixed(float f): store the fixed-point value corresponding to f. Hint: use roundf(f * (1 << _fracBits)).
- Conversions:  
    - float toFloat() const: return the floating-point value (_raw / 256.0f).  
    - int toInt() const: return the integer value (truncate the fractional part, e.g., _raw >> 8 or _raw / 256).  
- Streaming: 
    - Overload the insertion operator as a non-member "std::ostream& operator<<(std::ostream& os, const Fixed& x);"
    - It must insert a floating-point representation of x (typically by calling x.toFloat()).
4. You are provided with main.cpp and a sample of expected output

<details> <summary> Click for Main.cpp </summary> 

```cpp
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
```
</details>
  
    

<details> <summary> Click for Expected output </summary> 

```shell
 $> ./a.out
 Default constructor called
 Int constructor called
 Float constructor called
 Copy constructor called
 Copy assignment operator called
 Float constructor called
 Copy assignment operator called
 Destructor called
 a is 1234.43
 b is 10
 c is 42.4219
 d is 10
 a is 1234 as integer
 b is 10 as integer
 c is 42 as integer
 d is 10 as integer
 Destructor called
 Destructor called
 Destructor called
 Destructor called
```
</details>

--- 

## TO COMPLETE THIS EXERCISE
Considering the exercise goal, most of the code from the previous exercise is going to be use in this one.  

The exercise demands some extra class members and functions. 

- 2 new constructors that will have to convert **int -> fixed-point number** and **float -> fixed-point number**
    - `THIS MEANS = All objects store their value in _raw as a fixed-point integer with 8 fractional bits.`
- A NON-class function to overload the Streaming/printing (<<) 
    - If the right operand’s type is Fixed (binds to const Fixed&), your non-member operator<< is used.  
    - If the right operand is not Fixed (e.g., it’s an int, float, const char*, …), the standard library overload for that type is used.

### Constructor selection
main() calls the constructor whose signature matches the argument:
- Fixed a; → default ctor
- Fixed const b(10); → int ctor
- Fixed const c(42.42f); → float ctor
- Fixed const d(b); → copy ctor
- a = Fixed(1234.4321f); → float ctor for the temporary, then copy assignment into a.


### Int to fixed-point number
To consider an easy way to convert int to fixed-point number, knowing the scale will always be 8 bits, check [this document](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_1_FPN_scale.md)  


### Float to fixed-point number

Similarly to the int conversion, we need to consider the scale **(S)**:  
- _fracBits == 8 (or 1/256)  
- S = [1 << _fracBits]  or [256]

```cpp
// float -> fixed-point number
fixed-point-num = float * (1 << _fracBits)
or 
fixed-point-num = float * 256 //because subject states fracBits will always be 8
```
### 1st consideration - rounding
3As mentioned in [Fixed-Point Numbers](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_0_FixedPointNumbers.md) and in [Float Numbers](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_2_floatnumbers.md), fixed format can only represent multiples of 1/256. Rounding centers the error around zero. In order to do this, we are allowed to use the function `roundf`from the <cmath> library.

Example:   
```r
fixed-point-value (float32) = 42.42f
42.42 * 256 = 10859.52 → roundf(...) = 10860 → _raw = 10860.
```

#### 2nd consideration - data type
Multiplying a float (f) by an int promotes the int to float, so the product is float. So the initial result of this conversion is of data type **float**.  
As the class member **_raw** is an int, ***casting*** is needed.

---

### toFloat()
This functions needs to undo the scale.  
It divides the store integer _raw by the scale (_fracBits = 8), to get back the real value.
Casting is needed to ensuere `floating-point division` instead of integer division.

Example:   
```r
_raw = 10860
toFloat() = 10860 / 256.0f = 42.421875f.
```
> This is the value the operator << needs to print in this exercise-

NOTE
What happens with different literals
10860 / 256 → int / int = 42 (int division, truncates)
10860 / 256.0 → int / double = 42.421875 (double)
10860 / 256.0f → int / float = 42.421875f (float)

Against the need to cast operands consider that all of this are valid alternatives: 

```cpp
// A) Cast numerator only (denominator int will be promoted to float)
return static_cast<float>(_raw) / (1 << _fracBits);

// B) Cast denominator only (numerator int will be promoted to float)
return _raw / static_cast<float>(1 << _fracBits);

// C) Use float literals (no casts needed). Only if you’re OK with the fixed 8 bits:
return _raw / 256.0f;              // “magic number” – works because fracBits == 8

// D) Multiply by the reciprocal (often a tiny bit faster; same result)
return static_cast<float>(_raw) * (1.0f / static_cast<float>(1 << _fracBits));

// E) With a precomputed local (readable and avoids repeating the shift)
const float invScale = 1.0f / static_cast<float>(1 << _fracBits);
return static_cast<float>(_raw) * invScale;

```
---
//Edge case (range) - consideration to constructor float

If f is huge (so f * S overflows int), you’ll get UB or wrap. The subject doesn’t require clamping, so most ex01 solutions leave it as-is.

---

### Overloading the "<<" operator

The exercise´s subject demands using a non-member (free) function declaration that overloads the "<<" operator.

It is a ***non-member / out-of-the-class*** because the **left** operand in `std::cout << x` is a `std::ostream.`(you can’t add members to ostream).


|   std::cout  | << | x |
|--------------|----|---|
| left operand |operator | right operand |

If you made it a member of `Fixed`, then `Fixed` would have to be on the left (`x << std::cout`), which isn’t what we want.

> The standard pattern is a non-member overload that takes the stream (left) and your object (right).  

In ex01, the subject says to print a floating-point representation of Fixed, so the overload calls toFloat() internally whenever the right operand’s type matches the parameter (i.e., it’s a Fixed that can bind to const Fixed&).  

```cpp
std::ostream& operator<<(std::ostream& os, const Fixed& x);
```

By this definition, whenver `<<` is used, if whatever is to its right is `Fixed&`, the overlapping will be trigger.  

```cpp
Fixed const c( 42.42f );

std::cout << c << '\n';                      // c is a Fixed
std::cout << Fixed(42.42f) << '\n';          // temporary Fixed
std::cout << makeFixed() << '\n';            // function returns Fixed
std::cout << (++c) << '\n';                  // expression yields Fixed& (still a Fixed)
```

If you instead pass a float or int, the compiler picks the library’s operator<<(ostream&, float) or operator<<(ostream&, int).  

```cpp
std::cout << c.toInt() << '\n';              // int
std::cout << c.toFloat() << '\n';            // float
std::cout << &c << '\n';                     // pointer-to-Fixed (prints address)
std::cout << "c is " << c.toInt() << '\n';   // string then int
```