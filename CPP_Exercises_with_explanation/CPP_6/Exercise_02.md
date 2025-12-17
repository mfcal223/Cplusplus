# C++ Module 06 - Exercise 02 - "Identify yourself!"

# TASK
Create a small class hierarchy with a base class and three derived classes.  
The program must be able to determine the real (dynamic) type of an object at runtime, even when it is accessed through a base class pointer or reference.

### Requirements
* Implement a Base class containing only a public virtual destructor.
* Implement three empty classes A, B, and C, each publicly inheriting from Base.
* These classes do not need to follow the Orthodox Canonical Form.

#### Functions to implement
```
Base* generate();

Randomly creates an instance of A, B, or C and returns it as a Base*.
```
```
void identify(Base* p);

Prints the actual derived type of the object pointed to by p:
"A", "B", or "C".
```
```
void identify(Base& p);

Prints the actual derived type of the object referenced by p:
"A", "B", or "C".

Using a pointer inside this function is forbidden.
```
### Restrictions
* Including <typeinfo> or using typeid is forbidden.  
* The program must demonstrate that all functions behave correctly.  

---


# GOALS

This exercise is not about class design — it is about runtime type identification without [RTTI](https://www.codeguru.com/cplusplus/what-is-runtime-type-identification-rtti-in-c/#:~:text=Overview-,RTTI%20stands%20for%20Runtime%20type%20identification.,by%20the%20virtual%20function%20mechanism.).

`RTTI stands for Runtime type identification. It is a mechanism to find the type of an object dynamically from an available pointer or reference to the base type.`  


1. RTTI without `typeid`
* You must infer the dynamic type by attempting casts.

2. Dynamic casting
* Learn how dynamic_cast works:  
    * On pointers → returns NULL if the cast fails  
    * On references → throws std::bad_cast if the cast fails  

3. Difference between pointer and reference identification:  
* Pointer version: test for NULL  
* Reference version: use try/catch  
* Understand why the rules are different

4. Why a virtual destructor is required
* dynamic_cast only works on polymorphic classes.  
* A virtual destructor ensures the class has a `vTable`.

### vTable
The [vTable](https://www.geeksforgeeks.org/cpp/vtable-and-vptr-in-cpp/), or `Virtual Table`, is a table of function pointers that is created by the compiler to support dynamic polymorphism.  
Whenever a class contains a virtual function, the compiler creates a Vtable for that class. Each object of the class is then provided with a hidden pointer to this table, known as `Vptr`.

---

# Workflow of the exercise

1. Create `Base class` contains only a public virtual destructor. 
   1. create Base.hpp and Base.cpp
2. Create classes `A`, `B` and `C`
   1. empty / NO OCF
   2. inherit publicly from Base
3. Create Identify class to "store" the needed functions: 
   1. Create generate() function that randomly instantiates one of the derived classes and returns it as a Base*.
   2. overloaded identify() functions:
      1. One that receives a Base* and determines the real type of the object using pointer-based dynamic_cast.
      2. One that receives a Base& and determines the real type using reference-based dynamic_cast, without using pointers..

Identify() functions will use dynamic_cast() to check which class the Base object corresponds to:

```yaml
“dynamic_cast<A*>(p) 
asks: ‘Is the object behind p really an A?’”

If the answer is ...
... Yes → you get a valid pointer/reference

... No → you get NULL (pointer) or an exception (reference)

>>> Nothing is converted.
>>> Nothing changes in memory.
```

```c

[create an object +  vTable ] ------> I do not know which type of object is!
            |
   [I will use my identify() functions]
[I dont know what I am sending as parameter]
   |
   |__ [identify() asks] --> is it A ? --> yes == prints "A"
                                 | 
                                 NO 
                                 |
                                 is it B? --> yes = prints "B"
                                          |
                                          NO
                                          |
                                          is it C? --> yes = prints "C"
                                                   |
                                                   NO = prints "Unknown"
```
The big difference between the 2 overloaded identify() is the way the handle the miss-matchs.   
* On the pointer version, a pointer CAN be null. So there is no need to complicate things.
* On the reference version, a reference cannot be NULL. So when the subclass doesn't match the alias (reference), the function catches the exception.

| You cast…             | If it fails…           | How you detect                               |
| --------------------- | ---------------------- | -------------------------------------------- |
| `dynamic_cast<A*>(p)` | returns `NULL`         | `if (dynamic_cast<A*>(p))`                   |
| `dynamic_cast<A&>(p)` | throws `std::bad_cast` | `try { dynamic_cast<A&>(p); } catch(...) {}` |
