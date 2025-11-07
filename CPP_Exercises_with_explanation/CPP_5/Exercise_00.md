# Module 05 - Exercise 00 - "How would Asterix have evaluated the roman Bureaucrats?"

## TASK
Module 05 theme is set on practice exceptions (throwing, catching, propagating) and keep applying OOP habits from earlier modules.  

This particular exercise focus on designing a small but robust class that enforces invariants with exceptions, including:  
* throwing in constructors and mutators when invariants are violated,  
* catching via try/catch in client code,  
* clean I/O with operator<<.

In summary, this is what the program should do:  
1. Implement a Bureaucrat class representing a worker.   
2. Each Bureaucrat has :   
      1. ***constant*** name;  ----> inmutable
      2. a grade constrained to [1..150] where 1 is the best and 150 the worst.  
3. Constructing or changing a grade outside that range must throw a specific exception.  
4. Provide accessors, and functions to increase (i.e., move toward 1) or decrease the grade while enforcing the bounds.  (name is constant, there will be no setter)
5. Add an operator<< overload to print: `<name>`, bureaucrat grade `<grade>`.  
6. Demonstrate exception handling with `try/catch ` in tests.  

---

> This module is about Exception Handling. You will find information about that [Here](/CPP_Theory/11_Exceptions.md) 


## Considerations for the Exercise Solution

### -1- Constructors


### Custom Exception types
To fulfill the subject's goals, it is necessary to declare 2 custom exception types. They are small classes that `inherit from std::exception`.  
So instead of throwing a plain integer or string (like throw 20; or throw "Error";), you throw an object that represents a meaningful, typed error.

```cpp
throw Bureaucrat::GradeTooHighException();
```

Here, you’re creating an object of type Bureaucrat::GradeTooHighException and throwing it.  

This lets you later catch it by type, like:  
```cpp
catch (const Bureaucrat::GradeTooHighException& e)
```

`std::exception` defines a standard interface for exceptions in C++:  
```cpp
virtual const char* what() const throw();
```

This function (what()) is meant to return a human-readable message describing the error.  
By inheriting from std::exception and overriding what(), your custom exceptions can integrate seamlessly with the standard exception system.