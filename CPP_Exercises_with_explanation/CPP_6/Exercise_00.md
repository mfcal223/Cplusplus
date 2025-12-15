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

# Work that needs to be done 🔨

1. Create `class ScalarConverter` and its OCF methods (constructors and destructor as private).    
2. Create main.cpp that should check for `(ac == 2)` and simply call `ScalarConverter::convert()`.  
3. Create ScalarConverter.cpp. It should include the code to complete these tasks:    
- `main converter() function`--> receives a string (&string). Checks if it's empty and checks the correct type conversion (+ printing when it is succesfull), or declare it *impossible* if no match is found.  
- `every Type check function` --> is it a literal digit? a literal char? a literal float or double? is it a pseudo type?  
- `helper functions`--> is there a decimal point?  
- `printing functions for each type` --> char, int, float, double, pseudo.  

```text
+-----------+----------+
| Detect literal type  |
+-----------+----------+
            |
            |
            v
+------------+-----------+
| Parse into the correct |
|       base type        |
+------------+-----------+
            |
            |
            v
+-----------+-----------+
| Cast into the others  |
|    (static cast)      |  
+-----------+-----------+
            |
            |
            v
    +------+-----+
    |    Print   |  
    +------+-----+

```
 

---

## What "literal" means ?

> Module 06 is about representation vs interpretation.  
> A literal is a representation.  
> A value is a runtime object.  
> You’re learning to bridge that gap safely.  

A `literal` is a value written directly in source code, not stored in a variable and not computed. These are syntactic forms, not runtime values.  

```c++
'a'        // char literal
42         // int literal
-42        // int literal
4.2f       // float literal
4.2        // double literal
"hello"    // string literal
```

> This is the premise of this exercise: “Given a string that looks like a C++ literal, determine which kind of literal it is, then convert it.”  
> All the check-the-type functions will try to answer “Does this string follow the syntax rules of a C++ literal of that type?”

Example:
```c++
"42"
```
* Is it a char literal? → ❌ no ('4' would be a char literal, "42" is not)
* *s it convertible to char? → yes ('*')

So...
```c++
isCharLiteral("42")  // false
isIntLiteral("42")   // true
```

| Input string | Literal type detected | Reason                     |
| ------------ | --------------------- | -------------------------- |
| `"a"`        | char literal          | single non-digit character |
| `"4"`        | int literal           | digit, not `'4'`           |
| `"42"`       | int literal           | decimal integer syntax     |
| `"42.0f"`    | float literal         | decimal + `f` suffix       |
| `"42.0"`     | double literal        | decimal without suffix     |
| `"nan"`      | pseudo-double literal | special floating literal   |
| `"nanf"`     | pseudo-float literal  | special floating literal   |

---

## Why "static_cast()" is the right call in ScalarConverter?

Module 06 is about explicit type conversions and knowing `exactly what kind of cast` you are performing.  

```c++
double d = 42.0;
int    i = static_cast<int>(d);

float  f = static_cast<float>(i);
char   c = static_cast<char>(i);
```

`static_cast<T>(x)` says: “Convert `x `to `type T` using the language’s standard conversion rules.”

Other casting types are incorrect for this use case, irrelevant / dangerous, invalid or directly forbidden by the *"spirit"* the exercise prompt (C-style cast).

**All conversions in ScalarConverter are value conversions between fundamental scalar types, known at compile time, and static_cast expresses that intent clearly and safely.**

> Module 06 wants you to show understanding, not shortcuts.


---

## Checking for empty string

Use [std::string::empty](https://cplusplus.com/reference/string/string/empty/). Tests if string is empty.  

```c++
bool empty() const;
```

If empty (length == 0) returns true. Otherwise == false.

> Conversion is impossible if this is the case.  


---

# Detecting each data type

Remember the premise: you have a string, you don't know the content. How would you confirm if its an integer, a char or any of the other literal data types?

I will list here the strategy and methods I used:  

## Literal Integer
- check for sign '+' or '-' in position [0].  
- [std::isdigit()](https://en.cppreference.com/w/cpp/string/byte/isdigit.html) != 0 

```c++
int isdigit(static_cast<unsigned char>(ch));
```

Checks if the given character is one of the 10 decimal digits: (0123456789).  
It will return a Non-zero value if the character is a numeric character, zero otherwise.
The behavior is undefined if the value of `ch` is not representable as `unsigned char` and is `not equal to EOF`.  

If `isdigit() is 0` (!isdigit()) then it is `NOT a literal int`. 

##  Literal Char
True for these 2 conditions:
- string.length() == 1 
- isdigit(string[0]) == 0 (NOT a digit), meaning !isdigit(string[0])


## Literal Double

A double literal in this exercise follows this simplified syntax:  
* optional sign `+` or `-`
* at least one digit
* exactly one decimal point `'.'`
* no suffix

> **All these conditions == valid decimal number**

```c
0.0
-4.2
+42.0
```

## Literal Float

A float literal in this exercise follows this simplified syntax:
* optional sign `+` or `-`
* at least one digit
* exactly one decimal point `'.'`
* mandatory suffix `'f'`

**Valid float has these conditions**  :
- lenght > 2 
- `last character == 'f'`
- remaining string has to be `valid decimal number` with exactly one dot (like a ***double***)

## Aider function to check valid decimal number

* Accepts an optional sign at position [0] / moves the index past it
* Rejects strings that are only the sign sign `+` or `-`
* checks at least 1 digit exist (std::isdigit(static_cast<unsigned char>(c)))
* checks there is only 1 decimal point (if more than 1 dot, then it is not valid)

> the function will return true if (Has_1_dot && has_1_digit) is true.

## Pseudo-Literals (NaN and Infinity)

Pseudo-literals are special floating-point values defined by the IEEE-754 standard.  
**They do not follow normal numeric syntax** (digits and dots), but they are valid floating-point values in C++.  

These literals represent:  
* NaN → Not a Number
* ±Infinity → results of overflow or division by zero

> Because they do not contain digits, they must be detected explicitly (string comparison), before numeric parsing.  

| Pseudo Double | Pseudo Float |
|---------------|--------------|
|  "nan"        | "nanf"       |
|  "+inf"       | "+inff"      |
|  "-inf"       | "-inf"       |

---

# Conversions

## Conversion for Pseudo-Literals

**No casting is performed** for `char` and `int`, because these conversions do not make sense.

| Target type | Result                   |
| ----------- | ------------------------ |
| `char`      | `impossible`             |
| `int`       | `impossible`             |
| `float`     | `nanf`, `+inff`, `-inff` |
| `double`    | `nan`, `+inf`, `-inf`    |
