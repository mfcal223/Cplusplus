# C++ Module 07 - Exercise 01 - Function Templates & Const-correctness

- [C++ Module 07 - Exercise 01 - Function Templates \& Const-correctness](#c-module-07---exercise-01---function-templates--const-correctness)
  - [📬 TASK](#-task)
  - [🔍 What is the exercise REALLY about?](#-what-is-the-exercise-really-about)
    - [📍 Const vs Non-Const](#-const-vs-non-const)
  - [Designing Iter.hpp](#designing-iterhpp)
  - [🔮 Const / non-const flow diagram (mental model)](#-const--non-const-flow-diagram-mental-model)

## 📬 TASK  

> This exercise focuses on applying a generic operation to each element of an array without knowing the array’s element type in advance.

Implement a function template named `iter` that applies a given function to each element of an array.  

The function must take three parameters:
1. A pointer to the first element of an array  
2. The number of elements in the array (passed as a constant value)  
3. A function that will be executed on each element of the array

The iter function itself returns nothing.  

* Requirements:  
    * The function must work with arrays of any type  
    * The function passed as the third argument may:  
        * Take elements by non-const reference (to modify them)
        * Or by const reference (to read them only)
    * Your implementation must support both const and non-const arrays  
    * All template code must be placed in the header file  
    * A main.cpp must be provided with meaningful tests

---

## 🔍 What is the exercise REALLY about?

This exercise is not about arrays, but it is about designing a generic interface that respects const-correctness.  
This is compile-time safety, not runtime checking.  

`iter` abstracts the idea of: `“Apply the same operation to every element in a sequence.” ` and this needs to work for int[], std::string[], and any other future type.  

### 📍 Const vs Non-Const

***THIS is the tricly part of iter.***  
*Using a function (3rd parameter) that modifies the data in the array must NOT work for a const arr[].*  
*If the function is a read-only operation, it will work both with const and non-const arr[].*  

```c++
void printInt(int const &x)
{
    std::cout << x << std::endl;
}
```

**BUT this one:** 

```c++
void increment(int &x)
{
    x++;
}

```

This should work with `int arr[]` but **must NOT** with `const int arr[]` because modifying `const data` is **forbidden**. 💣 

This means:
* You cannot force everything to be non-const.  
* You cannot strip constness.  
* You must let the compiler enforce correctness.  

|    iter() must NOT decide:   |  iter() must ONLY:         |
|-------|-----------|
|whether elements are const | iterate |
| whether they can be modified | forward elements exactly as they are |

> Templates do not enforce rules — they propagate them.

* If the array is const → only const functions will compile.  
* If the array is non-const → both kinds may compile.  
📌 `The compiler enforces this for you`.  

---

## Designing Iter.hpp

❓ `What iter must do?`

- Work for any element type **>>> it has to be a template**
- Receive a pointer to the first element of an array
    - Work for const arrays and non-const arrays
- Receive the array length
- Call a function on each element
    - Allow the function to accept either:
        - T& (modifiable)
        - T const& (read-only)

📑 `Overloading iter function templates`

Use what was learned in preivous modules! Overloading! 

```
iter(T* array, ...) → gives elements as T&

iter(T const* array, ...) → gives elements as T const&
```
This automatically enforces:
* const arrays can’t be modified
* non-const arrays can

📑 `The callback type`

We’ll accept a function pointer:
* For non-const:
```
void (*f)(T&)

void (*f)(T const&) (also allowed)
```
* For const:
```
void (*f)(T const&)
```

⚠️ **Why 3 overloads (and not 2 or 4)?**
Because you need to cover the `3 possible combinations`: 
✳️ Non const array - non const function
✳️ Non const array - const function
✳️ Const array - const function


---

## 🔮 Const / non-const flow diagram (mental model)

“Constness flows from the array pointer type into the element reference type, and the compiler checks callback compatibility.”

```vbnet
                +-----------------------+
                |      call iter()      |
                +-----------+-----------+
                            |
                            v
              Is the array pointer const?
                 (T const* vs T*)
                            |
           +----------------+----------------+
           |                                 |
           v                                 v
     array is NON-CONST                 array is CONST
          (T*)                           (T const*)
           |                                 |
           |                                 |
    iter can access elements as:       iter can access elements as:
           |                                 |
      element type is T&                 element type is T const&
           |                                 |
           +-----------+---------------------+
                       |
                       v
        Does callback accept the element type?
         - For T*: callback can be (T&) or (T const&)
         - For T const*: callback must be (T const&)
                       |
          +------------+------------+
          |                         |
          v                         v
       YES: compiles            NO: compile error
       and runs                (const correctness enforced)
```

---
🔝 [TOP OF PAGE](#c-module-07---exercise-01---function-templates--const-correctness)   
⏪ [CPP 7 - ex00 - Function templates ](/CPP_Exercises_with_explanation/CPP_7/Exercise_00.md)  
⏩ [CPP 7 - ex02 - ](/CPP_Exercises_with_explanation/CPP_7/Exercise_02.md)  
🔙 [INDEX](/README.md)  