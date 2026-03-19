# C++ Module 08 - Exercise 02 - Container Adapter

## TASK

- Files to submit: Makefile, main.cpp, MutantStack.hpp (or .h)  
Optional: MutantStack.tpp

In this exercise, you must create a `custom stack type` called `MutantStack`.  

The standard std::stack is useful when you want classic stack behavior such as:
* push()  
* pop()  
* top()  
* size()   

However, unlike most STL containers, `std::stack does not provide iterators`, so you cannot traverse its contents with a loop.  
*Your task is to design a class that behaves like std::stack, while also allowing iteration through its stored elements.*   

This new class must:
- be based on std::stack
- preserve all normal stack operations
- add support for iterators

You must also prepare your own tests.  

Here is the reference test:
```cpp
int main()
{
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    // ...
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;

    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack);

    return 0;
}
```
Running the program using the MutantStack, running an equivalent version using a standard iterable container such as std::list, should display the same values in the same order.

When adapting the test to another container, use the appropriate member functions for that container.

---

## Educational Goal

This exercise is mainly about understanding that `std::stack` is not a real standalone container. It is a `container adapter` that uses another container internally but it exposes only a restricted interface: instead of giving you full access to the stored data, it only lets you interact with it in a stack-shaped way:
1. push at the top  
2. pop from the top  
3. read the top  
Nothing else.

A stack is an abstract data type, define by its behaviour: `Last In, First Out` + `only the top is directly accessible`. 

So it **deliberately hides iteration** because iteration is not part of the classical stack interface: even though the stack has an **internal container which DOES HAVE iterators**, **std::stack chooses NOT to expose them**. 

> It is not that the elements cannot be iterated, but the stack interface does not allow you to iterate them.  

To bypass this limitating, this MutantStack inherited from `std::stack`, one needs to expose the iterators of the underlying container. 

So this class inherits all normal stack operations from `std::stack`, and then simply adds:
* begin()
* end()
* optionally reverse iterators and const iterators

These functions delegate directly to the underlying container.

That is why MutantStack remains:
* usable as a stack
* copyable as a stack
* but also iterable like a normal container

---

## Important NOTE
Because MutantStack is a template class, its implementation must be visible in the header at compile time. That is why declarations go in `.hpp` and definitions in `MutantStack.tpp`, included at the end of the header.  

---

## Notes regarding building the class template

A stack needs:
* Fast insertion/removal at one end (LIFO)  
* No need for random access  
* No need for insertion in the middle  

These factors are important to define which container will be the inside the stack (container adapter) which needs an underlying container that supports:
- push_back()
- pop_back()
- back()  

`std::deque` is chosen because it provides stable and efficient insertion/removal at the back without the reallocation cost of `vector`, while being more memory-efficient and cache-friendly than `std::list`. It satisfies all requirements of a stack with stable performance.

At the beginning of the template definition, there should be a default container type defined as default 
```cpp
template <typename T, typename Container = std::deque<T> >
```

This is providing a default container == `deque`. 
If the type of container is not specify in main() (or other function), the class will use deque because the class INHERITS from stack,
So the Container MUST be compatible with:
- push_back
- pop_back
- back
If there is nothing set as default, and main tries to use a container not compatible, it will fail at compile time.

An example to ilustrate this idea:  
```cpp
template <typename Drink = Coffee>
👉 If you don’t choose → you get coffee
👉 But you can still order tea 😄
```

To show that the template can support other data types, I have added a test that uses `std::string` and program compiles.
You can try using 
```cpp
MutantStack<int, std::set<int> > s;
```
And see what happens...

<details><summary> Spolier </summary>

`std::set` doesn’t support those operations.
Program will fail at compile time.
</details>