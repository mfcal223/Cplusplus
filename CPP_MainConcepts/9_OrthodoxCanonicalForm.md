# The “Orthodox Canonical Form” (OCF aka the Rule of Three in C++98)

From CPP Module 2 onward, every class (unless the subject explicitly says otherwise) must define these four members, split into header/implementation files:  

a) Default constructor.  
- What it is: A constructor that can be called with no arguments.  
- When it runs: When you create an object with no parameters (e.g., Fixed a;).  
- Why it matters: It puts your object in a valid initial state. In ex00, it should set the internal fixed-point value to 0.  

b) Copy constructor.  
- Signature: ClassName(const ClassName& other).  
- When it runs: When you create a new object from an existing one (e.g., Fixed b(a); or passing/returning by value).  
- What it should do: Build a new object that is a copy of other. If your class ever owns dynamic memory, this is where you’d “deep-copy” it (ex00 doesn’t allocate, but the form is still required).  

c) Copy assignment operator.  
- Signature: ClassName& operator=(const ClassName& other).  
- When it runs: When you assign an already‑existing object from another (e.g., c = b;).  
- What it should do: Guard against self‑assignment, copy fields from other, and return *this. If you owned resources, release old ones safely, then copy (again, ex00 doesn’t own resources, but the operator is still required).  

d) Destructor
- Signature: ~ClassName()
- When it runs: When the object’s lifetime ends (goes out of scope, delete, etc.).  
- What it should do: Free/cleanup any owned resources. For ex00, there’s nothing to free, but you still implement it (and usually print a message in these modules so the evaluator can see call order).  

### Example

> You will find the files for the Example in Exercises/CPP_2/copy_constructor  

Imagine you have this class "Example":  


```cpp

#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP

#include <string>

class Example
{
	private:
		int			num;
		std::string	name;

    public:
    // Orthodox Canonical Form
    Example();                         		// Default constructor
    Example(const Example& ex);        		// Copy constructor
    Example& operator=(const Example& ex); 	// Copy assignment
    ~Example();                        		// Destructor

    // Small public API for your main()
    void setNum(int n);
    void setName(const std::string& s);
    int getNum() const;
    const std::string& getName() const;
};

#endif
```
<details> <summary> This would be Example.cpp </summary> 

```cpp
// Example.cpp
#include "Example.hpp"
#include <iostream>

// Default ctor: put object in a valid state
Example::Example() : num(0), name("")
{
    std::cout << "Default constructor\n";
}

// Copy ctor: build *new* object as a copy of ex
Example::Example(const Example& ex) : num(ex.num), name(ex.name)
{
    std::cout << "Copy constructor\n";
}

// Copy assignment: overwrite an *existing* object from ex
Example& Example::operator=(const Example& ex)
{
    std::cout << "Copy assignment operator\n";
    if (this != &ex) {
        this->num = ex.num;
        this->name = ex.name;
    }
    return *this;
}

Example::~Example()
{
    std::cout << "Destructor\n";
}

// Simple accessors
void Example::setNum(int n) { num = n; }
void Example::setName(const std::string& s) { name = s; }
int Example::getNum() const { return num; }
const std::string& Example::getName() const { return name; }

```

</details>

<details> <summary> This would be a simplify version of main.cpp </summary> 

```cpp
#include "Example.hpp"
#include <iostream>

int main()
{
    Example a;          // Default constructor
    Example b;          // Default constructor

    a.setNum(10);
    a.setName("Simon");

    b = a;              // *** Copy assignment operator ***

    Example c(a);       // *** Copy constructor ***

    std::cout << a.getName() << " " << a.getNum() << "\n";
    std::cout << b.getName() << " " << b.getNum() << "\n";
    std::cout << c.getName() << " " << c.getNum() << "\n";
}

// TO COMPILE: c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o example
```

</details>
--- 

## Copy constructor & Copy-assignment

### Copy constructor
`Example(const Example& ex)`

It builds a brand-new object as a copy of another.  
Examples:  
- Direct copy-init: Example c(a);    
- Copy-init: Example c = a;   
- Pass/return by value: parameter/return value copies use the copy ctor
- Creating temporaries from another Example

```cpp
// Copy ctor: build *new* object as a copy of ex
Example::Example(const Example& ex) : num(ex.num), name(ex.name)
{
    std::cout << "Copy constructor\n";
}
```

### Copy-assignment operator
`Example& operator=(const Example& ex)`

It runs when an already-existing object is assigned from another, or in a different set of words: it replaces the state of an already-existing object with the state of another (“make this existing thing look like that other thing.”).  
Example:  
- Example b; b = a; → copy-assignment (b was already constructed)  
- Self-assignment is possible: a = a; (hence the if (this != &ex) guard)  

> **Why both exist?** Because construction and assignment are different phases with different needs:  
- the **copy ctor** initializes members from scratch. It is perfect for building a new object cleanly with an initializer list.
- **assignment** first discard/overwrite the current state safely, then copy in new state (and protect against self assignment). This matters for resource-owning classes.  

If your class managed resources (heap buffers, file handles), you’d typically release/reacquire them in operator=, and clone in the copy ctor.  

| Code shape                      | What happens                             |
| ------------------------------- | ---------------------------------------- |
| `x = a;`                        | **Copy-assignment**                      |
| `Example x(a);`                 | **Copy constructor**                     |
| `Example x = a;`                | **Copy constructor** (copy-init)         |
| `void f(Example e); f(a);`      | **Copy constructor** (pass-by-value)     |
| `Example g(); Example x = g();` | **Copy constructor** (return-by-value)\* |

---

## Ad-hoc polymorphism & operator overloading  

Ad-hoc polymorphism in C++ means overloading: you provide multiple functions (or operators) with the same name but different parameter types/signatures, and the compiler picks the right one at compile time.

For example:
If you had these 3 functions in C
```c
void print(int i);
void print(unsigned int j);
void print(int i, unsigned int j);
```
You would have a problem when trying to compile:  
`main.c:4:6: error: conflicting types for 'print'`

But that would not happen in C++. Function overloading is authorised in C++ to allow to define two or more function with the same name in the same scope.

You can also overload operators like =, >=, <=, ==, just to mentione some of them. 
![Operators](/images/operator_overloading.png)  
(image from [Laura & Simon Gitbook](https://42-cursus.gitbook.io/guide/4-rank-04/cpp-00-04-doing/cpp02))  
  
For more information about operator overloading  : [cppreference.com > operators](https://en.cppreference.com/w/cpp/language/operators.html)


In CPP_" / ex00:
- You see function overloading with constructors: the default constructor and the copy constructor have the same name (Example) but different parameters. That’s ad-hoc polymorphism.  
- You also see operator overloading for operator= (assignment). You’re defining how “=” behaves for your custom type.  

In CPP_2 / ex01, you’ll also overload operator<< to stream your Fixed as text (ad-hoc polymorphism on the << operator).  

In CPP_2 / ex02 you’ll overload comparison (<, >, ==, …) and arithmetic (+, -, *, /) operators so Fixed “feels” like a number. That’s more ad-hoc polymorphism: the same operator symbol means different code depending on operand types.  

---

### Once you are sure you CAN write this without mistakes: 

Here is a bash script that helps you create hpp and cpp files filled with templates for the class  
[OCF script by @Laendrun](https://github.com/Laendrun/ocf_script)