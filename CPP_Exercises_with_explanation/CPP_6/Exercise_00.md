# CPP Module 06 - Exercise 00 - Scalar type conversion

- [CPP Module 06 - Exercise 00 - Scalar type conversion](#cpp-module-06---exercise-00---scalar-type-conversion)
- [TASK](#task)
  - [GOALS Explanation](#goals-explanation)
  - [Why “the class must not be instantiable”?](#why-the-class-must-not-be-instantiable)
  - [Representation vs Interpretation (core idea of the exercise)](#representation-vs-interpretation-core-idea-of-the-exercise)
  - [What "literal" means?](#what-literal-means)
- [Work that needs to be done 🔨](#work-that-needs-to-be-done-)
  - [Why "static\_cast()" is the right call in ScalarConverter?](#why-static_cast-is-the-right-call-in-scalarconverter)
  - [Checking for empty string](#checking-for-empty-string)
  - [Detecting each data type](#detecting-each-data-type)
    - [Literal Integer](#literal-integer)
    - [Literal Char](#literal-char)
    - [Literal Double](#literal-double)
    - [Literal Float](#literal-float)
    - [Helper function to check valid decimal number](#helper-function-to-check-valid-decimal-number)
    - [Pseudo-Literals (NaN and Infinity)](#pseudo-literals-nan-and-infinity)
  - [Conversions](#conversions)
    - [Conversion for Pseudo-Literals](#conversion-for-pseudo-literals)
    - [Conversion from a Chars Literal](#conversion-from-a-chars-literal)
    - [setf() +  setprecision(1) = Enabling fixed-point notation + Decimal precision control](#setf---setprecision1--enabling-fixed-point-notation--decimal-precision-control)
    - [Conversion from Int Literal](#conversion-from-int-literal)
      - [Check string parsing is complete](#check-string-parsing-is-complete)
      - [std::strtol](#stdstrtol)
      - [std::strtod](#stdstrtod)
      - [string.c\_str()](#stringc_str)
      - [Check whether the integer value is within INT limits and representable.](#check-whether-the-integer-value-is-within-int-limits-and-representable)
    - [Printing from INT](#printing-from-int)
      - [Printing Char from a Number](#printing-char-from-a-number)
    - [Printing from Float \& Double](#printing-from-float--double)
    - [Printing from Pseudo-Literals](#printing-from-pseudo-literals)


# TASK
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
- doubles: `0.0`, `-4.2`, `4.2`, …

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

## GOALS Explanation

At first glance, the exercise seems simple enough. *What is the point then?*  

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

4. **Handle numeric edge cases such as:**   
- Overflow when converting large double or float to int or char.  
- Non-displayable ASCII characters.  
- Special floating values: nan, +inf, -inf.  

> This includes distinguishing between “impossible” and “Non displayable”.  

5. **Output formatting**  
- Using std::fixed and std::setprecision to print 0.0f, 42.0, etc.  

---

## Why “the class must not be instantiable”?  

That sentence means there is no point in trying :   
```c++
ScalarConverter sc;  // <- this should NOT be allowed
sc.convert("42");
```

`ScalarConverter is stateless; it only provides a service via a static function.`

How do we enforce that in C++98? The usual way is making all constructors (and the destructor, and the assignment operator) `private`. This way we still respect the OCF rule. The members exist, just with restricted access.

---

## Representation vs Interpretation (core idea of the exercise)

This exercise is not about converting numbers — it is about understanding the difference
between **how a value is written** and **what that value actually is at runtime**.

A *literal* is only a **representation**:
- it is text
- it follows syntax rules
- it has no type yet

A *value* is the **interpreted result**:
- it exists in memory
- it has a concrete type (`char`, `int`, `float`, `double`)
- it can be converted safely or not

In this exercise, the input is always a `std::string`.
Your job is to:
1. Interpret what kind of C++ literal that string represents
2. Create the corresponding runtime value
3. Convert that value explicitly into other scalar types

This is why type detection must happen **before** conversion, and why syntax matters.

## What "literal" means?

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
> When **casting** to a different data type, you are simply telling the compiler to **change the set of rules it uses to read that variable**. The information in it doesn't change, it just need to be interpreted differently.

Example:
```c++
"42"
```
* Is it a char literal? → ❌ no ('4' would be a char literal, "42" is not)
* Is it convertible to char? → yes ('*')

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

# Work that needs to be done 🔨

1. Create `class ScalarConverter` and its OCF methods (constructors and destructor as private).    
2. Create `main.cpp` that should check for `(ac == 2)` and simply call `ScalarConverter::convert()`.  
3. Create ScalarConverter.cpp. It should include the code to complete these tasks:    
- `main converter() function`--> receives a string (&string). Checks if it's empty and checks the correct type conversion (+ printing when it is succesful), or declare the conversion *impossible* if no match is found.    
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

## Detecting each data type

Remember the premise: you have a string, you do not know the content. How would you confirm if its an integer, a char or any of the other literal data types?

I will list here the strategy and methods I used:  

### Literal Integer
- check for sign '+' or '-' in position [0].  
- [std::isdigit()](https://en.cppreference.com/w/cpp/string/byte/isdigit.html) != 0 

```c++
int isdigit(static_cast<unsigned char>(ch));
```

Checks if the given character is one of the 10 decimal digits: (0123456789).  
It will return a Non-zero value if the character is a numeric character, zero otherwise.
The behavior is undefined if the value of `ch` is not representable as `unsigned char` and is `not equal to EOF`.  

If `isdigit() is 0` (!isdigit()) then it is `NOT a literal int`. 

###  Literal Char
True for these 2 conditions:
- string.length() == 1 
- isdigit(string[0]) == 0 (NOT a digit), meaning !isdigit(string[0])


### Literal Double

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

### Literal Float

A float literal in this exercise follows this simplified syntax:
* optional sign `+` or `-`
* at least one digit
* exactly one decimal point `'.'`
* mandatory suffix `'f'`

**Valid float has these conditions**  :
- length > 2 
- `last character == 'f'`
- remaining string has to be `valid decimal number` with exactly one dot (like a ***double***)

### Helper function to check valid decimal number

* Accepts an optional sign at position [0] / moves the index past it
* Rejects strings that are only the sign sign `+` or `-`
* checks at least 1 digit exist (std::isdigit(static_cast<unsigned char>(c)))
* checks there is only 1 decimal point (if more than 1 dot, then it is not valid)

> the function will return true if (Has_1_dot && has_1_digit) is true.

---

### Pseudo-Literals (NaN and Infinity)

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
|  "-inf"       | "-inff"       |

---

## Conversions

### Conversion for Pseudo-Literals

Pseudo-literals are the only case where no numeric conversion is performed at all.  
This is intentional and required by the subject. **No casting is performed** for `char` and `int`, because these conversions do not make sense.

| Target type | Result                   |
| ----------- | ------------------------ |
| `char`      | `impossible`             |
| `int`       | `impossible`             |
| `float`     | `nanf`, `+inff`, `-inff` |
| `double`    | `nan`, `+inf`, `-inf`    |

---

### Conversion from a Chars Literal

**1st** : check - is it a printable character?

```c++
if (std::isprint(static_cast<unsigned char>(c)))
```

`isprint()` checks whether a character:
* has a visible representation
* can be printed safely to the terminal

`Printable characters` include:
* letters (A–Z, a–z)
* digits (0–9)
* punctuation (!, *, ?, etc.)
* space

`Non-printable characters` include:
* control characters (\n, \t, \0, etc.)
* ASCII values < 32 or 127

**2nd** Actual Printing  

| Printing from | Printing a :  |  How?         |
|---------------|---------------|---------------|
|  Char         | char     c    |  std::cout << c |
|               | int           | static_cast<int>(c) |
|               | float         | setf() --> static_cast<float>(c) |
|               | double        | setf() --> static_cast<double>(c)|

### setf() +  setprecision(1) = Enabling fixed-point notation + Decimal precision control 
To be able to match the subject's printing format for decimal values we need the aid of these 2 methods.

`setf(std::ios::fixed)`
* Forces floating-point output to use fixed decimal notation.
* Prevents scientific notation.  

`setf()` sets formatting flags on the output stream, meaning it always print floating-point numbers in fixed-point notation.

```c++
std::cout.setf(std::ios::fixed);
```

`setprecision(1)`
* With fixed, controls the number of digits after the decimal point.
* setprecision(1) == print exactly 1 digit after the decimal point

```c++
std::cout << std::setprecision(1)
```

Afterwards, the stream state needs to be restore, 
```c++
std::cout.unsetf(std::ios::floatfield);
```

--- 

### Conversion from Int Literal

There is a ***big consideration*** for INTs to keep in mind: 

> What happens if there is an invalid char in the middle of the string or for some reason the conversion stopped earlier? How does the code ensure the conversion reached the end of the string?

#### Check string parsing is complete
   * use a `char*` to store the last char that was parsed. (`char *end`)
   * use `C functions` = `std::strtol()` (integer attempt) or `std::strtod` (floating-point attempt)
   * Use `c_str()` to be able to pass `std::string` (our input) to C APIs.

#### std::strtol

[std::strtol](https://en.cppreference.com/w/cpp/string/byte/strtol.html) interprets an integer value in a byte string pointed to by `str`.

```c++
long      strtol( const char* str, char** str_end, int base );
```
`str` = our input string
`str_end` = the `char* end`
`base` = 10 (as we are working with the decimal system)
Returns a `long` as it must be able to handle ***overflow.***

`strtol()` reads characters from left to right; it stops when it encounters a character that is not valid for a number. `str_end` is set to point to the first character that was NOT parsed.  

This is the key 🔑 : as read in the manual `the function sets the pointer pointed to by str_end to point to the character past the last character interpreted. If str_end is a null pointer, it is ignored`.

```c++
const char *s = "123abc";
char *end;

long v = strtol(s, &end, 10);

//v = 123
//end points to 'a'
```

#### std::strtod

As part of the method that handle null-terminated byte strings, [std::strtod](https://en.cppreference.com/w/cpp/string/byte/strtof.html), this method interprets a floating point value in a byte string pointed to by str.

```c++
double      strtod ( const char* str, char** str_end );
```

`strtod()` converts a string into a double. It works similarly to strtol().  
It returns a double as it is ***the widest standard floating type***.It is the safest fallback as it can represent *+/-inf*.

#### string.c_str()

[c_str()](https://cplusplus.com/reference/string/string/c_str/) returns a const char* pointing to a null-terminated copy of the string.  
This is the only correct way to pass a std::string to C APIs.

#### Check whether the integer value is within INT limits and representable.

* `errno != ERANGE` (error code ).

```c++
//errrno-base.h
#define	ERANGE		34	/* Math result not representable */
```
* value within `<int>limits`

```c++
value >= std::numeric_limits<int>::min()
&& value <= std::numeric_limits<int>::max()
```

[std::numeric_limits library](https://en.cppreference.com/w/cpp/types/numeric_limits.html) provides a standardized way to query various properties of arithmetic types.
2 of the methods included in this template are [min()](https://en.cppreference.com/w/cpp/types/numeric_limits/min.html) and [max()](https://en.cppreference.com/w/cpp/types/numeric_limits/max.html)

```yaml
If these checks are succesful, then we can print the value as an INT.  
If these checks fails, then the code will try to fit the number as a DOUBLE.  
```

---

### Printing from INT  
Once these validations are finished, we can move on to actual printing the Int and the converted values.  

* `INT` : simply print the int variable with `std::cout`  
* `FLOAT` & `DOUBLE`:  
    * declare new long and double variables + use static_cast<>   
    * use `std::ios::fixed` and `setprecision(1)` to guarantee consistent floating-point with decimal notation.  
* `CHAR`: as printing a char from a numeric value is something that will happen when converting from an INT, a DOUBLE and a FLOAT, this explanation will be base for all 3.
The numeric value needs to be check validity and printability.  

---

#### Printing Char from a Number  

1) Check it is a valid finite value.   
      * this will be true for all INT (always finite numer1ic values) but might NOT be the case for all Float or Double  
2) Check <char>Limits  
      *  A char can only store a small range of integer values. This check ensures that the numeric value can actually be represented by a char without overflow (number inside  that range).  
      *  as mentioned in previous section: [std::numeric_limits library](https://en.cppreference.com/w/cpp/types/numeric_limits.html) provides a standardized way to query various properties of arithmetic types. 2 of the methods included in this template are [min()](https://en.cppreference.com/w/cpp/types/numeric_limits/min.html) and [max()](https://en.cppreference.com/w/cpp/types/numeric_limits/max.html)  
      *  the signedness of char is implementation-defined  
            *  on some systems: char is signed → range `-128 … 127`  
            *  on others: char is unsigned → range `0 … 255`  
3) Check printability : `int isprint(unsigned char ch)`  
      * [std::isprint()](https://en.cppreference.com/w/cpp/string/byte/isprint)    
          * Checks if ch is a printable character as classified by the currently installed C locale.    
               * digits (0123456789)  
               * uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)  
               * lowercase letters (abcdefghijklmnopqrstuvwxyz)  
               * punctuation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)  
               * space ( )  
           * `ch` must be `unsigned char` and `!= EOF`.  
           * Return = Non-zero value if the character can be printed, zero otherwise.  
4) Char gets printed with `std::cout`.  

---

### Printing from Float & Double

A float cannot always be converted meaningfully to a char. If the float is nan or +inf, it is meaningless, or if it stores very large values it will be outside char range.  

**Printing** :  

* print `CHAR` from Float
      * needs casting to `LONG`: this truncates the fractional part.  
          * The Print-char-from-number function will check limits and printability (as mentioned in previous section).  
      * checking `!std::isnan(f) && !std::isinf(f)`.  

* print `INT` from Float: (will also become a helper function)  
      * calling the helper function, will send the value as a parameter == double.   
          * in the float case, it needs casting to `DOUBLE`.  
          * I decided to make it a double so I can easily reused the helper when printing from a Double.  
      * also check `!std::isnan(f) && !std::isinf(f)` before calling the helper function.  
      * Helper function will `check INT limits` to avoid overflow issues.  
      * `re-cast` the value to INT to be printed with `std::cout`.  

* print `Float` or `Double`
      * needs setf() and setprecision() to keep a consistent format.  
      * static_cast will be call to go from float -> double, and double-> float.  
      * suffix f is added manually.  
      * no extra checks needed.  

### Printing from Pseudo-Literals

These are the simplest printing functions.

* for `INT` and `CHAR`: print "not possible" or "impossible"
* Pseudo-Double -> will need to append "f" to print pseudo-float
* Pseudo-Float -> will need to erase the "f" when printing pseudo-double

```c++
string.substr(0, string.length() - 1)
```

