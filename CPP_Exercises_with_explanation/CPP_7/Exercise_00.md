# C++ Module 07 - Exercise 00 - First steps with templates

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

## TEMPLATES

From a C++98 point of view, a template is a blueprint for code that allows us to write code that works for any data type without rewriting it for each type. Instead of writing a function for one specific type, you write a generic version, and the compiler generates the correct function when it sees how you use it. 

> Think of it as:
> “I don’t know the type yet — I’ll decide later.”

Templates can be defined using the keywords "template" and "typename" as shown:

```c++
template <typename T>
return_type function_name(T parameter) {
  // code
} 
```
`T` is a placeholder for a data type (like int, float, etc.).  
You can use any name instead of T, but T is common. The compiler replaces T with the actual type when the function is used.   

### Function Templates 
Templates allow us to write generic code for functions that can be used with different data types, and this can be achieved by `function templates`. For example, we can write a function that adds or that gives you the maximum of two numbers, but it can accept any number whether it is int, float, or double.

```c++
// SUMM 
template <typename T>
T add(T a, T b) {
  return a + b;
}

int main() {
  cout << add<int>(5, 3) << "\n";
  cout << add<double>(2.5, 1.5) << "\n";
  return 0;
}
```

```c++
// GET THE MAX
// function template
#include <iostream>
using namespace std;

template <class T>
T GetMax (T a, T b) {
  T result;
  result = (a>b)? a : b;
  return (result);
}

int main () {
  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax<int>(i,j);
  n=GetMax<long>(l,m);
  cout << k << endl;
  cout << n << endl;
  return 0;
}
```
### Considerations
1. `Templates must be in headers` as they are compiled when they are used (not when they are defined). For this reason, the design constrains say "Any function implementation put in a header file is forbidden (except for templates)"
2. Even if template provide a blueprint for different data types, this means the `compile-time polymorhism` needs to be consider. The types need to support the same operations and the compiler need to check this at compile time (NOT at runtime, as it happens with function overloading)


### Sources: 
[GfG - Templates](https://www.geeksforgeeks.org/cpp/templates-cpp/)  
[CppReference -  Templates](https://en.cppreference.com/w/cpp/language/templates.html)  
[W3Schools - Templates](https://www.w3schools.com/cpp/cpp_templates.asp)  
[Cplusplus - Templates](https://cplusplus.com/doc/oldtutorial/templates/)  
https://aticleworld.com/compile-time-polymorphism-with-templates-in-cplusplus/

---

## Key concepts for evaluation 

1. What is a template?
2. Why it avoids duplication?
3. Why it belongs in headers?
4. How it works with different types?