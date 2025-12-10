# CPP Module 06 - Exercise 00 - Scalar type conversion

## TASK
In this exercise you must write a utility class ScalarConverter that exposes a single static function:

```cpp
static void convert(std::string const & literal);
```

convert() receives a string representing a C++ scalar literal and prints its value converted into four types:
* char
* int
* float
* double

The class is purely functional (no data members), so it must not be instantiable.  
 
You’ll be given literals in their usual decimal form, for example:  
- chars: `c`, `a`, …  
- ints: `0`, `-42`, `42`, …  
- floats: `0.0f`, `-4.2f`, `4.2f`, …  
- doubles:` 0.0`, `-4.2`, `4.2`, …  

For floats and doubles you also have to support the special values:   
- float: `-inff`, `+inff`, `nanf`  
- double: `-inf`, `+inf`, `nan`  

Your program must:  
1. Detect which kind of literal was passed (char, int, float, double, or special pseudo-literal).  
2. Convert the string to that “real” type.  
3. Explicitly cast it to the three remaining scalar types.  
4. Print the results using the format shown in the subject.  

If a conversion would overflow or is meaningless, print that it’s impossible for that type.  
For conversions to char, if the value is valid but non-printable, print an appropriate “Non displayable” message instead of a character.  
You may use any standard function that converts a `std::string` to `int`, `float` or `double`, and any headers needed to handle numeric limits and special values.  

Here is a sample of what the terminal output should look like:

```bash
./convert 0 
char: Non displayable 
int: 0 
float: 0.0f 
double: 0.0 

./convert nan 
char: impossible 
int: impossible 
float: nanf 
double: nan 

./convert 42.0f 
char: '*' 
int: 42 
float: 42.0f 
double: 42.0
```
---

## GOAL's Explanation

At first hand the exercise seems simple enough. *What is the point then?*  

1. **Static utility classes**  
- ScalarConverter has no state, only behavior.   
- Everything is done through one static method.  

> You learn how to design a class that acts like a namespace of functions but still respects the module rules.   

2. **Type identification from text**  
Given only a string, you must decide:  
* is it a single printable char?  
* an integer literal?  
* a float literal (…f)?  
* a double literal?  
* one of the pseudo-literals (nan, +inf, etc.)?  

3. **Explicit C++ casts**
- Once you know the base type, you use static_cast<targetType>(value) to convert it to the others.  
- The module specifically asks that conversions in each exercise be handled via a precise cast choice (here: static_cast).   

4. **Handle Numeric edge cases such as:**   
- Overflow when converting large double or float to int or char.  
- Non-displayable ASCII characters.  
- Special floating values: nan, +inf, -inf.  

> Distinguishing between “impossible” and “Non displayable”.  

5. **Output formatting**  
- Using std::fixed and std::setprecision to print 0.0f, 42.0, etc.  

---

## Why “the class must not be instantiable”?  

That sentence means there is no point in trying :   
```c++
ScalarConverter sc;  // <- this should NOT be allowed
sc.convert("42");
```

`ScalarConverter is stateless`; it only provides a service via a static function.

How do we enforce that in C++98? the usual way is making all constructors (and the destructor, and the assignment operator) `private`. This way we still respect the OCF rule. The members exist, just with restricted access.

---

## Work

1. Create class ScalarConvert and its OCF methods (constructors and destructor as private).  
2. Create main.cpp that should check for `(ac == 2)` and simply call `Scalarconverter::convert()`.
3. Create ScalarConverter.cpp 