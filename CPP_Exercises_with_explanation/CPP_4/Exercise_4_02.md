# C++ Module 4 - ex02 - Abstract class

## TASK

So far, you could still create objects of type Animal, but this doesn’t make sense: a generic “Animal” has no sound. To prevent misuse, you must ensure that the base Animal class cannot be instantiated directly.

Modify Animal so it becomes an abstract base class.

This is achieved by declaring at least one function as pure virtual (in this case, makeSound() is the natural choice).

The destructor must remain virtual so that deletion through a base pointer still works.

Derived classes such as Dog and Cat continue to implement makeSound() and remain instantiable.

All functionality from the previous exercise must still work. The only difference is that you can no longer do new Animal().

Optionally, you can rename the class to AAnimal to emphasize its abstract nature, but this is not mandatory.

> Animal becomes an abstract base class. Animal class should not be instantiable.

--- 

## Explanation

An instantiable class is one you can create objects of, e.g.:

```cpp
Dog d;           // stack
Dog* p = new Dog();  // heap
```
Conditions:  
- All member functions must have definitions.  
- No pure virtual functions.  
- Class is not marked abstract.  

An NON-Instantiable (abstract) class is one that cannot be instantiated.
It usually serves as a blueprint for derived classes.  
Condition: it has at least one pure virtual function:

Therefore, the only required change to make Animal non-instantiable is to make at least one virtual function pure (+ remove the concrete definition of Animal::makeSound() from Animal.cpp).  
This alone makes Animal abstract → you cannot do new Animal(); anymore.
All derived classes (Dog, Cat) must override it.  

```cpp
//IN HEADER FILE
virtual void makeSound() const = 0;  // pure virtual => Animal is abstract

//IN MAIN.CPP
// Animal* a = new Animal();  // error: cannot declare variable ‘a’ to be of abstract type ‘Animal’
```

### Summary 

```c++
           BEFORE (ex01)                         AFTER (ex02)
      ----------------------              -----------------------------
      Animal (concrete class)             Animal (abstract base class)
      ----------------------              -----------------------------
      + type : string                     + type : string
      + makeSound()   <-- concrete        + makeSound() = 0  <-- pure virtual
      + getType()                         + getType()
      + setIdea()                         + setIdea()
      + getIdea()                         + getIdea()
      ----------------------              -----------------------------
         ⬇ instantiable                      ⬇ cannot be instantiated
         new Animal();   ✅                  new Animal();   ❌ compile error

           /      \                            /        \
          /        \                          /          \
  -------------------                  -------------------   -------------------
  Dog (concrete)       Cat (concrete)  Dog (concrete)       Cat (concrete)
  -------------------  -------------   -------------------  -------------------
  + makeSound()        + makeSound()   + makeSound()        + makeSound()
  (overrides Animal)   (overrides)     (must override)      (must override)
  -------------------  -------------   -------------------  -------------------
     ⬇ instantiable                     ⬇ instantiable
     new Dog(); ✅                      new Dog(); ✅
     new Cat(); ✅                      new Cat(); ✅

```