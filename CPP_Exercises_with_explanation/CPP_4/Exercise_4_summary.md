# Module 4 - Runtime polymorphism / virtual functions and abstract classes

Module 4 is about learning runtime polymorphism in C++. Until now we worked with inheritance, but objects were created and used directly. In this module we explore how base class pointers/references can manipulate derived objects, and how the correct behavior is chosen at runtime using virtual functions.

## Key concepts covered:

* Virtual functions: Functions declared virtual in the base class can be overridden in derived classes. When called through a base pointer/reference, the derived implementation is used. Without virtual, you get static binding (wrong behavior).  

* Virtual destructor: Essential when deleting objects through a base pointer, so the full destructor chain executes and resources are released correctly.  

* Abstract classes: A class with at least one pure virtual function (= 0). They can’t be instantiated directly, but serve as blueprints for derived classes. This forces only meaningful, specialized subclasses (e.g., Dog, Cat) to be created.  

* Deep copy and the Rule of Three: When a class owns heap-allocated memory (like Brain*), it must correctly implement copy constructor, copy assignment operator, and destructor to avoid shallow copies, leaks, or double deletes.  

* Polymorphic arrays: Storing Animal* in arrays and filling with Dogs/Cats shows the power of polymorphism — you can treat different objects uniformly and still get specific behavior at runtime.  

---

## Progression of exercises:

- ex00: Introduce virtual functions with Animal, Dog, Cat. Show the difference between correct and incorrect polymorphism using WrongAnimal.  

- ex01: Add Brain to demonstrate ownership of heap memory. Dogs and Cats now manage their own Brain* → requires Rule of Three and deep copy.  

- ex02: Make Animal abstract by turning makeSound() into a pure virtual function. This prevents instantiating meaningless base objects. Only Dog and Cat can be created.  

(later ex03/ex04): Explore deeper polymorphism with Materia/Character and Interfaces.

---

## Big picture takeaway:
Module 4 teaches how C++ achieves runtime polymorphism through virtual functions and abstract base classes, and how to combine it with proper memory management when using heap-allocated resources.