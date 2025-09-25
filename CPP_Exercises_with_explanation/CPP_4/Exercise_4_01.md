# C++ Module 4 - ex01 - Polimorphism - “Brains attached”

## TASK 

1. Deliver: previous exercise’s files + your new sources/headers.  
2. Create a class `Brain` that stores `100 std::string` elements named `ideas`.  
3. All constructors/destructors must print distinct messages.  
4. Update `Dog` and `Cat` so each one owns a Brain* as a private member.  
5. On construction, allocate the brain with new Brain().  
6. On destruction, free it with delete.  
7. In main, build an array of Animals and populate it with Dogs and Cats (half and half). In the shutdown phase, iterate that array and delete them through Animal*. The destructor chain must run in the right order (no leaks).
8. Copies of Dog and Cat must be deep: copying one must also copy the underlying Brain contents (no shared pointer, no shallow copy). Add tests to prove it.

---

## POLYMORPHISM MEETS OWNERSHIP

This exercise dives deeper into a concept of runtime polymorphism that was treated in the ex00 of this module. Now it includes copying element from a class in a deep way instead of a shallow way.

You are asked not only to create a new class (Brain) with multiple elements in it (ideas), but also to include a deep copy of it in every other element (Dogs and Cats), which are subclasses of the reference class (Animal).

Dog & Cat will own a raw pointer (Brain*). Brian needs to be a OCF class so lifetime of its elements is correct.

As during construction, **Dog and Cat will create their OWN Brain (`new Brain()`)**. 
* Copying must allocate a fresh Brain and copy the 100 strings.  
* Assignment must self-assign check, then copy element-by-element (or *this->brain = *rhs.brain; after ensuring both exist).
* During destruction, Dog and Cat will delete their OWN Brain.  

---

### What does `deep copy` mean?

|   Shallow copy    |   Deep copy   |
|-------------------|---------------|
| copies pointer values. Two objects end up pointing to the same Brain | duplicates the owned resource. Each object gets its own Brain with its own 100 strings. |
| Issues: double-delete at destruction, surprising shared state (changing one affects the other). | Replace contents. Each copy is independent (no shared pointer between copies.) |

---

> TIPS!
* ~Animal() destructor HAS TO be virtual in order to allow runtime polymorphism.
* Consider how all the constructor and the destructor in Dog and Cat class have to handle the new element Brain.
* Consider including setters and getter for the ideas.