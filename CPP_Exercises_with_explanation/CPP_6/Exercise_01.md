- [C++ Module 6 - Exercise 01 - Pointer representation](#c-module-6---exercise-01---pointer-representation)
  - [TASK](#task)
  - [GOALS](#goals)
  - [Workflow](#workflow)
  - [How does reinterpret\_cast() works?](#how-does-reinterpret_cast-works)


# C++ Module 6 - Exercise 01 - Pointer representation

## TASK

You must implement a `Serializer` class that **cannot be instantiated by the user and exposes two static functions:
```c++
serialize(Data* ptr)
//Takes a Data* pointer and converts it into an unsigned integer type uintptr_t.

deserialize(uintptr_t raw)
//Takes that uintptr_t value and converts it back into a Data* pointer.
```

Then you write a small test program that:
1. creates a non-empty Data struct (it must have data members),
2. "serializes" the address of a Data object,
3. "deserializes" it back,
4. verifies the resulting pointer is exactly equal to the original pointer.

⚠️ This exercise is not about "real" Serialization, as the value of an object will not be copied, transmited or re-built anywhere. I am just keeping the name as it is the way it figures in the exercise guide of some very well known programming school. This is a low-level C++ concept, not a practical serialization task.

---

## GOALS

This exercise only converts a pointer’s address into a number and back, to teach how representation and interpretation differ in C++. 

1) Continue working on *representation vs interpretation*: you are only `converting a pointer value into an integer and back`. So it’s really about pointer representation, not about copying object contents.

> “Treat this address as a number”   
> then later   
> “Treat this number as an address again”  

1) `uintptr_t`: an integer type meant to hold pointers safely

`uintptr_t` is an unsigned integer type guaranteed to be able to store a pointer value without losing bits (when it exists on the platform).

3) The right cast: `reinterpret_cast`

In Module 06, conversions must use an appropriate explicit cast, and for pointer↔integer conversions, the intended tool is `reinterpret_cast`.

You'll be learning that the same bits can be seens as different types using reinterpret_cast (as a pointer or as an integer) without changing the underlying values.  

---

## Workflow

1) Create Data.cpp and .hpp  
* Create a `struct Data` with some random attributes (for example 1 int, 1 string and 1 double)  
* Create all OCF methods  
2) Create Serialize.hpp and .cpp  
* Create a class Serialize with private OCF methods ("not instantiable for the user").  
* Create the serialize() public method 
    * [takes a (Data *ptr) as parameter]
    * return [uintptr_t] 
* Create deserialize() public method.
    * takes (uintptr_t) as parameter
    * returns [Data *]   
* Both serialize() and deserialize() uses reinterpret_cast()
3) Create main.cpp   
* create a `Data object "original"` providing the corresponding values of the chosen attributes.  
* create a `uintptr_t variable "raw"`, and initilize it using `serialize(original)`
* create a `2nd Data object "is_a_copy`, and use `deserialize(raw)` to get a Data* to initialize it.  
* use `std::cout` to print each variable and any other necessary message to explain the goal of the exercise.  

---

## How does reinterpret_cast() works?

At the lowest level, memory is just bits:  
```text
01001110 10100101 00001011 ...
```
Those bits have no type by themselves. A type only exists in the **compiler’s head**.  
When you declare a variable with a certain data type (p.e. INT), you are telling the compiler *“Please interpret the next N bytes as an INT.”*  
If then you declare another variable (p.e. a DOUBLE), you are telling the compiler *“Please interpret the next N bytes as an DOUBLE.”*   

`The bits don’t change — only the rules used to read them do.`  

A pointer is just a number that represents a memory address.  

```css
Data* ptr = &d;
//Data object lives at address: 140724696281096
//ptr = 140724696281096

```

What `reinterpret_cast` does is tell the compiler:

```yaml
“Do NOT transform the value.
Just reinterpret these bits as another type.”
No adjustment.
Just: same bits, new meaning.
```
```c++
// in code
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}
`//“Take the bits that represent this pointer
//and treat them as an unsigned integer.”


Data* ptr  →  0x7ffd05887008  
uintptr_t →  140724696281096

> Same bits. Different label.
```