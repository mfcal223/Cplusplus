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

---

## **4️⃣ Polymorphism – One interface, multiple behaviors**

**Definition**
Polymorphism means you can **call the same function on different objects**, and each object can respond in its own way.

**In C**

* You’d simulate this using `switch` statements or function pointers, and manually manage behavior.

**In C++**

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

