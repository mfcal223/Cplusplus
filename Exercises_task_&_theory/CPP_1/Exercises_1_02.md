# Exercise Level 01 - Nr 02 - "Where is my Brain?"

This exercise is about memory address "manipulation".
It will be necessary to understand **pointers** and **references**.

## Goals
Initialize a string varible as "HELLO THIS IS YOUR BRAIN".  
Create a pointer to that string and a reference to the string.  
Write a program that prints the memory address of the string, the one held by the pointer, and the one by the reference.  
Then it should print the value of the string, the value pointd by the string, and the value pointed by the reference.   


## Theory Recap

### POINTERS
A pointer is a variable that holds a memory address. You can change where it points, or even make it NULL.  
- To access the value: use *p (dereference).  
- To access the address: use p itself.  

```cpp
std::string str = "HELLO THIS IS YOUR BRAIN";
std::string* stringPTR = &str;

std::cout << "Address held by stringPTR: " << stringPTR << std::endl;
std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
```

### REFERENCES
- A reference is an alias (another name) for an existing variable.  
- You declare it with & (in a declaration).  
- Once bound, it cannot be reseated to refer to something else.  
- You don’t need to dereference it with *; you use it just like the original.  

```cpp
std::string str = "HI THIS IS BRAIN";
std::string& stringREF = str;   // reference bound to str

std::cout << "Address held by stringREF: " << &stringREF << std::endl;
std::cout << "Value referred to by stringREF: " << stringREF << std::endl;
```

Summary of differences Pointer vs Reference
| Feature          | Pointer                        | Reference (C++ only)         |
| ---------------- | ------------------------------ | ---------------------------- |
| Can be `NULL`?   | Yes                            | No (must alias something)    |
| Can be reseated? | Yes (can point to another var) | No (always aliases same var) |
| Syntax           | `*p` to get value              | Use it like the variable     |
| Declaration      | `int* p = &x;`                 | `int& r = x;`                |
