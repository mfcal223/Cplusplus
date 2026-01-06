# C++ Module 07 - Exercise 02 - Class Templates

- [C++ Module 07 - Exercise 02 - Class Templates](#c-module-07---exercise-02---class-templates)
  - [TASK](#task)
  - [GOALs](#goals)
  - [Exercise summary](#exercise-summary)
  - [WORKFLOW](#workflow)
    - [Creating Array.hpp and the class template](#creating-arrayhpp-and-the-class-template)

## TASK

* Implement a `class template` named `Array` that stores a sequence of `elements` of a generic type `T`.
* The class must behave like a simplified, safe dynamic array and support the following features:  
    * `Default construction`:  
        * Creating an Array with no arguments must result in an empty array  
    * `Construction with size`
        * Creating an Array with an unsigned integer `n` must allocate space for `n` elements, each initialized using their default value.
    * `Copy and assignment`
        * Copying an Array (via copy constructor or assignment operator) must create a deep copy.
        * After copying, modifying one array must not affect the other.
    * `Dynamic memory management`.
        * Memory must be allocated using new[].
        * Pre-allocating extra memory is forbidden, and the program must never access memory outside the allocated range.
    * `Element access`
        * Elements must be accessible using the subscript operator (operator[]).
    * `Bounds checking`
        * If an index passed to operator[] is outside the valid range, the function must throw an std::exception.
    * `Size query`
        * A member function `size()` that takes no parameters, and must return the number of elements in the array without modifying the object.  
* Provide a `main.cpp` containing sufficient tests to prove that all features work correctly.  

---

## GOALs

1. **Using Class templates**  
This time, instead of templating a function, you template an entire type.

```c++
template <typename T>
class Array
{
    // T is the element type
};

```

This will allow one implementation for:
```c++
Array<int>
Array<double>
Array<std::string>
```

2. **Deep copy vs shallow copy**

Consider this crucial instruction:
>*After copying, modifying one array must not affect the other.*

❌ This is forbidden (shallow copy):
```c++
this->_data = other._data;
```

`The deep copy needs to allocate new memory and copy each element.`  
The thing is the type is unknown and the size is dynamic.  
The use of `operator new[]` is mandatory. It should have a `matching delete[]`.

3. **size() and const-correctness**

As defined in the subject's prompt: *"size() takes no parameters and must not modify the current instance"*.
const-propagation must be considered.  

---

## Exercise summary

> **“This exercise teaches how to implement a generic container using class templates, ensuring safe memory management, deep copying, bounds-checked access, and const-correct interfaces.”**

This exercise seemed a bit overwhelming. It is the combination of several topics covered through the previous modules: 
1. Templates (CPP07 theme)
2. Orthodox Canonical Form (CPP02)
3. Dynamic memory ownership (CPP01 / CPP04)
4. Operator overloading (CPP02)
5. Const correctness (CPP01 + ex01 of this module)
6. Exception safety (CPP05)

---

## WORKFLOW

### Creating Array.hpp and the class template

> The class Array<T> owns a dynamically allocated array of elements of type T.  
> The class manages two things: a pointer to heap-allocated memory and the number of elements.  

You will need to private attributes to store data and the size (max number of elements in the array).  

1. **Default Constructor**

The `default constructor` creates an empty array with no allocation.

```c++
Array<int> a;

//memory layout
STACK                           HEAP
─────────────────────────       ───────────────
a                               (nothing)
┌──────────────┐
│ _data = NULL │
│ _size = 0    │
└──────────────┘

```
* a lives on the stack  
* No allocation happened  
* Destructor will do delete[] NULL → safe

2. **Size constructor**

The `size constructor` allocates exactly **n elements** using **new[]**, with default initialization depending on the type.   

```c++
Array<int> a(3);

//memory layout
STACK                           HEAP
─────────────────────────       ─────────────────────────
a                               new int[3]
┌──────────────┐                ┌───────┬───────┬───────┐
│ _data ───────┼──────────────▶ │  ?    │  ?    │  ?    │
│ _size = 3    │                └───────┴───────┴───────┘
└──────────────┘

```
* `a` still lives on the stack. 
* Elements live on the heap. 
* `?` = default-initialized (for int, undefined).  

>  `a` is the only owner of that heap memory

3. **Copy Constructor & operator=** 

The copy construtor will create a deep copy of the array on initialization. To ensure a DEEP COPY of the information inside data, an overload of the operator= (assignment operator) is needed.

```c++
Array<int> b = a;

STACK                           HEAP
─────────────────────────       ─────────────────────────
a                               new int[3]
┌──────────────┐                ┌───────┬───────┬───────┐
│ _data ───────┼──────────────▶ │  ?    │  ?    │  ?    │
│ _size = 3    │                └───────┴───────┴───────┘
└──────────────┘

b                               new int[3]
┌──────────────┐                ┌───────┬───────┬───────┐
│ _data ───────┼──────────────▶ │  ?    │  ?    │  ?    │
│ _size = 3    │                └───────┴───────┴───────┘
└──────────────┘
```
* a._data != b._data  
* Modifying one does not affect the other  
* Each destructor deletes its own memory

> This is the core requirement of ex02



> The destructor releases the allocated memory using **delete[]**.

```c++
data = new T[_size];
```
```c++
delete[] _data;
```

---


