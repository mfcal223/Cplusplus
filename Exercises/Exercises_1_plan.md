# Exercises Level 1

## Concepts to Grasp Before/During the Module
1. Core C++ Basics
Class syntax: declaration (.hpp), definition (.cpp), private/public members
Constructors & destructors: what they do, when they’re called
Initialization lists: ClassName::ClassName(...) : member(value) {}

2. Memory & Object Lifetime
Stack allocation (Zombie z("name");) → auto-destroyed at scope end
Heap allocation (Zombie* z = new Zombie("name");) → must delete
new[] and delete[] for arrays of objects
Destructor messages to confirm cleanup

3. Pointers & References
Pointers: store an address, can be nullptr, can be reassigned

References: alias to an existing variable, must be initialized, cannot be reseated

Printing addresses vs values

4. Object Composition
Having one object as a member of another (HumanA has a Weapon&)

Deciding between reference (always valid) vs pointer (nullable)

5. File Handling
- Using std::ifstream and std::ofstream
- Reading entire file contents into a string
- Using std::string::find and substr for manual replace (since replace is forbidden)

6. Function Pointers (Member Version)
- Syntax for pointer-to-member:
    - void (ClassName::*ptr)(); and calling via (object.*ptr)() or (objectPtr->*ptr)()

1. Control Structures
- switch statement
- break vs fall-through behavior for cumulative actions

---

## Suggested Step-by-Step Plan

### Phase 1 – Foundation
- Review class creation in C++ with .hpp + .cpp separation.
- Practice constructors/destructors with std::cout debug output.
- Refresh on heap vs stack allocation in C++.

--- 

### Phase 2 – Exercises 00–02

---

**(1) Ex00:**
- Create Zombie with announce()
- Implement newZombie() (heap) and randomChump() (stack)
- Understand when to delete

--- 

**(2) Ex01:**
- Allocate N zombies in one go with new[]
- Loop to set their names

**(3) Ex02:**
Practice with pointers & references, printing addresses and values

--- 

### Phase 3 – Exercises 03–04
Ex03:

Weapon class with getType() returning const std::string&

HumanA stores a reference (must have weapon at creation)

HumanB stores a pointer (can be armed later)

Ex04:

Open file, read into string

Manual find/substr replacement for all occurrences of s1 with s2

Write to <filename>.replace

Phase 4 – Exercises 05–06
Ex05:

Create an array of pointers-to-member-functions

Map string levels to correct function

Avoid if/else by using loop through array

Ex06 (optional):

Implement level filtering using switch with intentional fall-through

Phase 5 – Testing & Debugging
Compile with -Wall -Wextra -Werror -std=c++98

Run valgrind to check for leaks

Write minimal but clear Makefile

Add debug prints to constructors/destructors to trace object lifetimes

---


