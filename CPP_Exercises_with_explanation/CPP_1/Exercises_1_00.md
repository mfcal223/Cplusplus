# Exercise Level 01 - Nr 00 - Zombieland

## Objectives: 
- Create a class called "Zombie" with a private attribute to store its name.
- Class needs a member function to announce a message: by using "announce()" they will say "BraiiiiiiinnnzzzZ...".
- Implement 2 other functions: newZombie() that creates a zombie, name it, and return it so you can use it outside of the function scope,  and randomChump() that creates a zombie, name it, and the zombie announces itself.  
- "Determine in what case it’s better to allocate the zombies on the stack or heap"
- Understand when/how to delete each.  


## Plan: 
1. Create header for Zombie
- Class declaration that includes:
* No `using namespace`.
* Private `std::string name`.
* Ctor, Dtor, and `announce()`.

2. Create source file for "Zombie"
* Constructor initializes `name` via initializer list.
* Destructor prints a debug line with the zombie’s name.
* `announce()` prints the required message.

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


3. Create file for `newZombie`

* free function (no ClassName::)  
* Heap allocation, return pointer (caller must `delete`).

```cpp
#include "Zombie.hpp"

Zombie* newZombie(std::string name) {
    return new Zombie(name);
}
```
> KEY WORD HERE IS ***"NEW"***
> **"new"** allocates memory on the heap and calls the constructor.  
> It returns a pointer to the object created.  
> Without new, you’d just be making a stack object that vanishes at the end of the function.  
> Every new should be paired with a delete, otherwise you **leak memory**.


**newZombie** is a free function, not a member of Zombie. That’s why there’s no `Zombie::`.  
The `*` is part of the return type: it returns a pointer to Zombie.   

> The **::** scope operator is only used when you’re defining a member function (e.g., void Zombie::announce()).  

Calling `announce()` can be done in main.cpp or elsewhere, as this new zombie is created on the heap and is returned as a pointer that survivs after the function ends.   

4. Create file for  `randomChump`

* free function (no ClassName::)  
* Stack allocation, announce immediately, auto‑destroy at function end.

```cpp
#include "Zombie.hpp"

void randomChump(std::string name) {
    Zombie z(name);
    z.announce();
}
```
The `Zombie object z` is created on the stack.  
Since it exists only inside this function, if you don’t call `announce()` in here, you’ll never be able to use it outside.

---

> Note: declare the two free functions in a shared header is optional for this module; the subject doesn’t require it. Since each `.cpp` includes `Zombie.hpp` (for the class) and defines one free function, `main.cpp` can forward‑declare them.

```cpp
Zombie* newZombie(std::string name);
void randomChump(std::string name);
```

(Original exercise demanded specific files, so no extra headers were allowed. But that would be an alternative to declare them in main.cpp)

---

5. Create `main.cpp` (simple tests that show both stack & heap usage)

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

--- 

## Quick self‑tests

* Run your program; check you see:

  * `Bob: BraiiiiiiinnnzzzZ...`
  * `Jim: BraiiiiiiinnnzzzZ...`
  * destruction messages for `Bob`, `Jim`, `Ana` (names should match).
* (If you can) run under Valgrind: **no leaks** (all heap zombies are deleted).
* You can try commenting the "delete Jim" or "delete ana" line and check again with valgrind to notice the difference.

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