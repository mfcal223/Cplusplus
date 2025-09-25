## **1️⃣ Encapsulation – Grouping related data and behavior**

**Definition**
Encapsulation means **keeping data (attributes) and the functions (methods) that operate on that data inside the same class**, and controlling how the outside world accesses it.

**In C**

* You’d have a `struct` for data and separate functions to operate on it.
* Anyone can directly modify struct fields without restriction.

**In C++**

* You put **data and functions together in a class**.
* You control access using `private`, `protected`, and `public`.

```cpp
class BankAccount {
private:
    double balance; // hidden from outside
public:
    BankAccount(double initial) : balance(initial) {}
    void deposit(double amount) { balance += amount; }
    double getBalance() const { return balance; }
};
```

**Analogy**
Think of **encapsulation** like a **vending machine**:

* You can *use* it (insert coins, press button), but you **can’t touch the internal mechanism**.
* It keeps the inner workings safe, only exposing a controlled interface.

---

## **2️⃣ Abstraction – Hiding unnecessary complexity**

**Definition**
Abstraction is about **showing only what’s necessary** and hiding the details of how something works.

**In C**

* You may hide complexity by writing functions, but users still need to know a lot about the data and implementation to use them safely.

**In C++**

* You define a **clear interface** (public methods) without exposing internal details.
* The user of the class doesn’t need to know *how* the method works, only *what it does*.

```cpp
car.start();  // You don’t need to know about the ignition system
```

**Analogy**
Using **abstraction** is like driving a car:

* You just turn the key or push a button.
* You don’t need to understand how the starter motor, fuel injection, or combustion work.

---

## **3️⃣ Inheritance – Reusing and extending code**

**Definition**
Inheritance allows one class (**child/derived**) to **reuse** and **extend** the code of another class (**parent/base**).

**In C**

* You’d have to duplicate code or simulate inheritance with function pointers and structs (messy).

**In C++**

* You simply declare:

```cpp
class ElectricCar : public Car { ... };
```

* ElectricCar gets all Car’s attributes and methods, and can add or override behaviors.

**Analogy**
Think of **inheritance** like making **new car models**:

* `Car` class = general blueprint (engine, wheels, steering).
* `SportsCar` inherits from Car but overrides acceleration.
* `ElectricCar` inherits from Car but overrides fuel system.

> For a practical explanation of Inheritance, please check: 
- [Module 03 - ex00](CPP_Exercises_with_explanation/CPP_3/Exercise_3_00.md)
- [Module 03 - ex01](CPP_Exercises_with_explanation/CPP_3/Exercise_3_01.md)
- [Module 03 - ex02](CPP_Exercises_with_explanation/CPP_3/Exercise_3_02.md)
- [Module 03 - ex03](CPP_Exercises_with_explanation/CPP_3/Exercise_3_03.md)

---

## **4️⃣ Polymorphism – One interface, multiple behaviors**

The word polymorphism means having many forms. A real-life example of polymorphism is a person who at the same time can have different characteristics. A man at the same time is a father, a husband, and an employee. So, the same person exhibits different behaviour in different situations.  
In programming, polymorphism means you can **call the same function on different objects**, and each object can respond in its own way.

**In C**  

* You’d simulate this using `switch` statements or function pointers, and manually manage behavior.

**In C++**  

In C++, polymorphism concept can be applied to functions and operators. A single function can work differently in different situations. Similarly, an operator works different when used in different context.  

* You use **virtual functions** in a base class, and override them in derived classes.
* You can store different objects in the same collection and call the same method—behavior adapts dynamically.

```cpp
class Animal {
public:
    virtual void makeSound() const { std::cout << "???" << std::endl; }
};
class Dog : public Animal {
public:
    void makeSound() const override { std::cout << "Woof!" << std::endl; }
};
class Cat : public Animal {
public:
    void makeSound() const override { std::cout << "Meow!" << std::endl; }
};
```

```cpp
Animal* zoo[] = { new Dog(), new Cat() };
for (Animal* a : zoo) a->makeSound();
// Output: Woof! Meow!
```

**Analogy**
Think of **polymorphism** like a **universal remote control**:

* You press the same button (“Play”) on different devices.
* A TV starts a movie, a DVD player spins a disc, a game console launches a game.
* **Same interface → different behaviors.**

### Polymorphism in C++ 

It can be classified into two types:  
1. Compile-time Polymorphism (A.K.A. early binding and static polymorphism)
- the compiler determines how the function or operator will work depending on the context.  
- This type of polymorphism is achieved by function overloading or operator overloading.

2.  Runtime Polymorphism (A.K.A. late binding and dynamic polymorphism)
- It  is resolved at runtime.  
- It is implemented using function overriding with virtual functions.  

#### Compile-time Polymorphism

1. Function Overloading  
When two or more functions can have the same name but behave differently for different parameters.  
Functions can be overloaded either by changing the number of arguments or changing the type of arguments.  

2. Operator Overloading
It is a feature that allows you to redefine the way operators work for user-defined types (like classes). It enables you to give special meaning to an operator (e.g., +, -, *, etc.) when it is used with objects of a class.  
For example, we can make use of the addition operator (+) for string to concatenate two strings and for integer to add two integers. The << and >> operator are binary shift operators but are also used with input and output streams.  

//note>  see exercise Cpp 2???? 3???


#### Runtime Polymorphism

Function Overriding occurs when a derived class defines one or more member functions of the base class. That base function is said to be overridden. The base class function must be declared as virtual function for runtime polymorphism to happen.

Please check [Module 04](/Cplusplus/CPP_Exercises_with_explanation/CPP_4) for more explanation and examples.

***Read more about this in : ***
https://www.geeksforgeeks.org/cpp/cpp-polymorphism/
https://www.geeksforgeeks.org/cpp/operator-overloading-cpp/