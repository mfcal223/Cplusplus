# C++ Module 07 - Exercise 00 - First steps with templates

- [C++ Module 07 - Exercise 00 - First steps with templates](#c-module-07---exercise-00---first-steps-with-templates)
  - [TASK](#task)
  - [Key concepts for evaluation](#key-concepts-for-evaluation)
  - [WORKFLOW](#workflow)


## TASK

* Create three generic utility functions using C++ templates.  

Your goal is to write functions that work with any type, as long as that type supports basic comparison and assignment operations.  

You must implement the following function templates:

1. `swap`
- Exchanges the values of two variables.
- This function does not return anything.

2. `min`
- Takes two values and returns the smaller one.
- If both values are equal, the function must return the second argument.

3. `max`
- Takes two values and returns the larger one.
- If both values are equal, the function must return the second argument.

- Requirements
    * Both parameters must be of the same type.  
    * The type must support comparison operators (<, >, etc.).  
    * These functions must be written as templates, not duplicated for each type.  
    * All template implementations must be placed in header files.  
    * No forbidden functions are listed.  

- Expected behavior  
    * Your functions must work correctly with built-in types (like int) and user-defined types such as std::string, producing exactly the same output shown in the subject.  
    * This exercise demonstrates how templates allow you to write one single implementation that adapts automatically to different data types.

---

> Please chech [Template](CPP_Theory/13_Templates.md) for theory background on this subject.

## Key concepts for evaluation 

1. What is a template?
2. Why it avoids duplication?
3. Why it belongs in headers?
4. How it works with different types?

---

## WORKFLOW

1. Create  `whatever.hpp` 
2. Create the 3 function templates
```
template <typename T>
void swap(T &a, T &b)
{...}

template <typename T>
T min(T const &a, T const &b)
{...}

template <typename T>
T max(T const &a, T const &b)
{...}
```
3. In main.cpp, create main() with pairs of int, string, and other data type to demonstrate the exercise goals. Include "whatever.hpp"

```c++
// MAIN EXAMPLE
int main( void ) {
    int a = 2;
    int b = 3;
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    return 0;
}
//Output example
a = 3, b = 2
min(a, b) = 2
max(a, b) = 3
c = chaine2, d = chaine1
min(c, d) = chaine1
max(c, d) = chaine2
```
4. Create Makefile to compile main.cpp 