# Exercise Level 01 - Nr 00 - Zombieland

**(1) Ex00:**
- Create Zombie with announce().  
- Implement newZombie() (heap) and randomChump() (stack).  
- Understand when to delete.  
- "Determine in what case it’s better to allocate the zombies on the stack or heap".  

***Plan:  ***
1. Create header.
- Class declaration. 

2. Create source file

Constructor syntax Recap:  

> Zombie::Zombie(std::string name) : name(name) {}

-  Zombie::Zombie(std::string name)  
`Zombie::` → says “this function belongs to the Zombie class.”  
`Zombie(...)` → the name matches the class, so it’s a constructor.  
Parameter list: `(std::string name)` → here name is a parameter, not the member variable.  

-  The colon `:` marks the start of the member initializer list.  
*Syntax*
`ClassName(parameters) : member1(value1), member2(value2) { ... }`  
This list runs before the constructor body { ... }.  

- `name(name)`

| `name` (left)                                          | `name` (right)                               |
| ------------------------------------------------------ | -------------------------------------------- |
| The **member variable** of the class (`Zombie::name`). | The **constructor parameter** you passed in. |

This means *“Initialize the member variable name with the parameter name.”*


---


Awesome — here’s a complete, defense‑ready plan for **Module 01 — ex00** with file list, minimal code, and what to test.  


# Implementation plan (with minimal code)

## 1 `Zombie.hpp`

* No `using namespace`.
* Private `std::string name`.
* Ctor, Dtor, and `announce()`.


## 2 `Zombie.cpp`

* Constructor initializes `name` via initializer list.
* Destructor prints a debug line with the zombie’s name.
* `announce()` prints the required message.

## 3 `newZombie.cpp`

* free function (no ClassName::)  
* Heap allocation, return pointer (caller must `delete`).

```cpp
#include "Zombie.hpp"

Zombie* newZombie(std::string name) {
    return new Zombie(name);
}
```
**newZombie** is a free function, not a member of Zombie. That’s why there’s no `Zombie::`.  
The `*` is part of the return type: it returns a pointer to Zombie.   

> The **::** scope operator is only used when you’re defining a member function (e.g., void Zombie::announce()).

## 4 `randomChump.cpp`

* free function (no ClassName::)  
* Stack allocation, announce immediately, auto‑destroy at function end.

```cpp
#include "Zombie.hpp"

void randomChump(std::string name) {
    Zombie z(name);
    z.announce();
}
```

> Note: declare the two free functions in a shared header is optional for this module; the subject doesn’t require it. Since each `.cpp` includes `Zombie.hpp` (for the class) and defines one free function, `main.cpp` can forward‑declare them or include a small extra header if you prefer.

If you like the forward‑declare approach, add at the top of `main.cpp`:

```cpp
Zombie* newZombie(std::string name);
void randomChump(std::string name);
```

## 5) `main.cpp` (simple tests that show both stack & heap usage)

* Demonstrates lifetime differences and destructor prints.

```cpp
#include "Zombie.hpp"
#include <iostream>

// Forward declarations (alternatively put them in a small header)
Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main() {
    // Stack allocation: created, announces, destroyed automatically at end of scope
    randomChump("Bob");

    // Heap allocation: created, used outside scope, must be deleted manually
    Zombie* jim = newZombie("Jim");
    jim->announce();
    delete jim;

    // Another quick check
    Zombie* ana = newZombie("Ana");
    delete ana; // ensure destructor message prints with the correct name

    return 0;
}
```

## 6) `Makefile`


# What the evaluator will look for

* ✅ Correct class split (`.hpp` + `.cpp`).
* ✅ Constructor initializes name; **no `using namespace std;`**.
* ✅ `announce()` output exactly: `Foo: BraiiiiiiinnnzzzZ...`
* ✅ `newZombie()` returns a heap zombie; you `delete` it in `main`.
* ✅ `randomChump()` uses a stack zombie; auto‑destruction triggers destructor message.
* ✅ All outputs end with `\n`.
* ✅ Compiles with `-Wall -Wextra -Werror -std=c++98`.

# Quick self‑tests

* Run your program; check you see:

  * `Bob: BraiiiiiiinnnzzzZ...`
  * `Jim: BraiiiiiiinnnzzzZ...`
  * destruction messages for `Bob`, `Jim`, `Ana` (names should match).
* (If you can) run under Valgrind: **no leaks** (all heap zombies are deleted).

If you want, I can also add a tiny **README.md** with build/run instructions and a short explanation of **stack vs heap** tailored to your repo.


---

# **Stack vs Heap Allocation** 

When you create an object in C++, you can put it in two places in memory:

## Stack Allocation
What it means: The object’s memory is reserved automatically in the stack (the part of memory used for function calls and local variables).

Syntax:
```cpp
Zombie z("Foo"); // automatic storage
```
- Lifetime: The object exists until the function/block ends, then it’s destroyed automatically — destructor is called without you having to do anything.
- Pros: Fast allocation/deallocation, no need to call delete.
- Cons: You cannot control lifetime beyond the scope it was created in.

## Heap Allocation
What it means: You manually request memory from the heap using new or new[].

Syntax:
```cpp
Zombie* z = new Zombie("Foo"); // dynamic storage
```
- Lifetime: The object exists until you manually delete it with delete.
- Pros: Lifetime is under your control; you can create objects that outlive the function where they were created.
- Cons: Slower allocation, and you must remember to delete, or else you have a memory leak.

1. How It Applies to This Exercise  
The exercise gives you two functions to implement:
```cpp
Zombie* newZombie(std::string name)
```
This is heap allocation.

Example:
```cpp
Zombie* z = newZombie("Foo");
z->announce();
delete z; // YOU must delete it when done
```
Purpose: Let the zombie live beyond the scope of the function call.

***VERSUS***  

```cpp
void randomChump(std::string name)
```
This is stack allocation.

Example:
```cpp
void randomChump(std::string name) {
    Zombie z(name); // automatic storage
    z.announce();
} // z is destroyed here automatically
```
Purpose: The zombie is only needed during the function, so it’s destroyed right after.

## WHY THE COMPARISON?

The point is to make you notice that With *stack allocation*, you cannot pass the object back out of the function (it will be destroyed immediately after the function ends).  
With *heap allocation*, you can return a pointer and use the object outside — **but you must remember to delete it**.

1. Example in Context
```cpp
// stack version
void randomChump(std::string name) {
    Zombie z(name); // created on stack
    z.announce();
} // destroyed automatically here

// heap version
Zombie* newZombie(std::string name) {
    return new Zombie(name); // created on heap
} // object still exists until delete is called
```

Main program:

```cpp
int main() {
    // Stack example
    randomChump("Bob"); // Bob announces and is destroyed immediately

    // Heap example
    Zombie* jim = newZombie("Jim");
    jim->announce();
    delete jim; // must manually delete
}
```

💡 Rule of thumb for this exercise:  
* If the object needs to outlive the function call → use new (heap).  
* If it’s only used inside the function → use a normal local variable (stack).  
* Destructor runs:  
- automatically for stack objects (end of scope),  
- on delete for heap objects.  