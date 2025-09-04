# CPP Module 2 - Ex 00 - My First Canonical Class

You’ve worked with integers and floating-point numbers so far. This task introduces another way of representing numbers: **fixed-point arithmetic**. Unlike floats and ints, fixed-point keeps a fixed number of fractional bits and is commonly used in domains like graphics or audio processing.  

Since C++98 does not provide such a type, you’ll begin by building the foundation of one.  

---

## TASK

1️⃣ Create a class `Fixed` that follows the **Orthodox Canonical Form (OCF)**.  

The class must have:
1. Private members
- An integer to hold the raw fixed-point value.
- A `static const int` representing the number of fractional bits (always set to 8).

2. Public members
- A default constructor initializing the raw value to 0.
- A copy constructor.
- A copy assignment operator.
- A destructor.
- A method `int getRawBits(void) const;` returning the raw stored integer.
- A method `void setRawBits(int const raw);` to set the raw stored integer.

2️⃣ Expected behavior

You are provided with `main.cpp`, which will:
- Create instances of `Fixed`.
- Copy them using the copy constructor and assignment operator.
- Call the `getRawBits()` method and print the results.

The output should demonstrate calls to constructors, assignment, and destructors, along with the trace from `getRawBits()`. The printed numbers will be `0` since only raw storage is implemented at this stage.

> Here are the code for those files:  
  
<details> <summary> Click for Main.cpp </summary> 

```
 #include <iostream>
 int
 main( void ) {
 Fixed a;
 Fixed b( a );
 Fixed c;
 c = b;
 std::cout << a.getRawBits() << std::endl;
 std::cout << b.getRawBits() << std::endl;
 std::cout << c.getRawBits() << std::endl;
 return 0;
 }
 ```
</details>

<details> <summary> Click for Expected output </summary> 

```
 $> ./a.out
 Default constructor called
 Copy constructor called
 Copy assignment operator called 
 getRawBits member function called
 Default constructor called
 Copy assignment operator called
 getRawBits member function called
 getRawBits member function called
 0
 getRawBits member function called
 0
 getRawBits member function called
 0
 Destructor called
 Destructor called
 Destructor called
 $>
 ```
</details>

---

## OCF

To understand Orthodoxal Canonical Form, please go to [Explaining Orthodoxal Canonical Form](/home/florencia/proyectos/CPP/Cplusplus/9_OrthodoxCanonicalForm.md)

--- 






