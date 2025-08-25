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

> Example

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
        Example(void);							// Default constructor
        Example(const Example& ex);				// Copy constructor
        Example &operator=(const Example& e);	// Copy assignment
        ~Example(void);							// Destructor
}

#endif
```

--- 




---

Once you are sure you CAN write this without mistakes: 

Here is a bash script that helps you create hpp and cpp files filled with templates for the class >>> https://github.com/Laendrun/ocf_script