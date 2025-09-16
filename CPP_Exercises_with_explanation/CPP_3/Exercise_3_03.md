# CPP Module 3 - Exercise 02 - This gets stranger and stranger

## TASK
1. Files required: all files from earlier exercises, plus DiamondTrap.{h|hpp} and DiamondTrap.cpp
2. This time, you must design a hybrid robot: a creature that mixes traits from both FragTrap and ScavTrap. Its name will be DiamondTrap, and it must inherit from both of these classes. 

> Yes — this is risky multiple inheritance!

3. The DiamondTrap class introduces a new private attribute called name.
* this attribute must have the exact same identifier as the one already used in the ClapTrap class. (If ClapTrap uses name, use name; if it uses _name, then you must also call it _name.)  

4. The behavior of DiamondTrap comes partly from FragTrap and partly from ScavTrap:
- Name: provided as argument in the constructor.  
- ClapTrap::name: constructed as <parameter> + "_clap_name".  
- Hit points: inherited from FragTrap.  
- Energy points: inherited from ScavTrap.  
- Attack damage: inherited from FragTrap.  
- attack() function: inherited from ScavTrap.

5. Special ability: `void whoAmI();`
- This function should display both its own name and the ClapTrap’s name.

---

###⚠️ Note: 
Even though multiple inheritance is involved, the ClapTrap sub-object that DiamondTrap relies on must exist only once. There’s a catch here you’ll nee to solve.

---

## MULTIPLE INHERITANCE

In this exercise, you are asked to build a class that inherits from two parents (FragTrap and ScavTrap), each of which already inherits from ClapTrap. This introduces a diamond-shaped inheritance structure, where the same base (ClapTrap) could be inherited twice unless handled properly (virtual inheritance).  

#### Analogy with Fruit 🍊🍌
```cpp
class Fruit {
protected:
    std::string shape;
    std::string color;
};

class Orange : public Fruit {
public:
    Orange() { shape = "round"; color = "orange"; }
};

class Banana : public Fruit {
public:
    Banana() { shape = "curved"; color = "yellow"; }
};

class Smoothie : public Orange, public Banana {
public:
    void describe() {
        std::cout << "This smoothie mixes attributes from both: "
                  << "Shape: " << Orange::shape << ", Color: " << Banana::color << std::endl;
    }
};
```

---

> Multiple inheritance is an object-oriented programming concept where a class inherits properties and methods from more than one parent class.


It enables the creation of complex classes with rich behavior by combining features from different class hierarchies. The child class gains access to the members (properties and methods) of all its parent classes.  
Optimizes code re-usability: it allows sharing and combining functionalities from various sources without extensive copying.  

Among the issues, one can name the complexity of the codebase. It turns quite harder to understand, maintain and debug; some issues causes by *ambiguity* may arise, as the compiler may not know which method to call when a conflict arises, requiring explicit resolution by the programmer. Lastly, in the context of the current exercise, it is necessary to talk about `The Diamond Problem`.

## The Diamond Problem

The `diamond problem` occurs when two superclasses of a class have a common base class.

![Diamond Inheritance](/CPP_Exercises_with_explanation/images/diamond_inheritance.png)

The solution to this problem is `'virtual'` keyword: Make the classes in level 2 (*Orange* and *Banana* in the previous example)  as `virtual base classes` to avoid 2 copies of the base class (*Fruit*) in the final class (*Smoothie*).  

In general, it is not allowed to call the grandparent's constructor directly, it has to be called through parent class. It is allowed only when 'virtual' keyword is used.  
Only the most derived class (here: Smoothie) initializes the virtual base.
So in Smoothie.cpp, constructor initializer list, you must call Fruit(...) yourself.  

**Check**: [Multiple Inheritance in C++](https://www.geeksforgeeks.org/cpp/multiple-inheritance-in-c/)

---

## What's with the name ambiguity?

`Why differentiate between “its name” and “its ClapTrap name”?`

At first it looks redundant, but here’s why:  
- DiamondTrap has two notions of identity:  
    - DiamondTrap::name: its own name (the one you pass when you create it).  
    - ClapTrap::name: automatically set to <DiamondTrap name> + "_clap_name".  

This highlights the ambiguity caused by `multiple inheritance`. If both parents (FragTrap and ScavTrap) already inherit ClapTrap, you’d normally end up with two copies of `ClapTrap::name`. The exercise forces you to disambiguate:

--> The robot has a DiamondTrap identity (name).
--> It also has an underlying ClapTrap identity (ClapTrap::name).

So when you call `whoAmI()`, you’ll print something like:
```cpp
I am DiamondX, and my ClapTrap name is DiamondX_clap_name
```

This shows you understand the distinction between the two layers of inheritance.

---

## Summary of robot's stats

ClapTrap (ex00):

HP = 10

EP = 10

AD = 0

ScavTrap (ex01):

HP = 100

EP = 50

AD = 20

FragTrap (ex02):

HP = 100

EP = 100

AD = 30

DiamondTrap (ex03, the mix):

HP = 100 (from FragTrap)

EP = 50 (from ScavTrap)

AD = 30 (from FragTrap)