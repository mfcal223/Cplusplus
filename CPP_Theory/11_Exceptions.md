# Exceptions Handling

Exception handling in C++ is a mechanism for detecting and managing runtime errors—errors that occur while the program is running, not during compilation.  
It allows programs to transfer control from the point where an error occurs to a separate piece of code called an exception handler, keeping normal logic and error-handling logic clearly separated.   
Typical runtime errors are:
- Division by zero  
- Accessing invalid memory  
- File I/O failures  
   
To monitor a section of code for potential errors, we place it inside a try block. When an error occurs, we throw an exception, and control is transferred to the corresponding catch block, which handles it. If no exception is thrown, the code continues normally and all handlers are ignored.  

* **Throwing an Exception:** When an error or unexpected situation occurs, the program uses the `throw` keyword to signal an exception.
* **Catching an Exception:** The program searches for a matching `catch block` to intercept and handle the thrown exception.
* **Handling the Exception:** The catch block contains the logic to respond to the error, allowing the program to recover or terminate gracefully.

```cpp
// exceptions
#include <iostream>
using namespace std;

int main () {
  try
  {
    throw 20;  // throw an integer exception
  }
  catch (int e)
  {
    cout << "An exception occurred. Exception Nr. " << e << '\n';
  }
  return 0;
}
```
Output:
```shell
An exception occurred. Exception Nr. 20
```

> **try** marks code that might throw.  
> **throw** signals an error by creating an exception object.
> **catch** defines how to handle the exception.


### Standard Exceptions

The C++ Standard Library defines a hierarchy of exception classes in the header <exception>.
The base class std::exception provides a consistent interface through the virtual method `what()`, which returns a description of the error.
It also provides consistent interface to handle errors through the *throw* expression.


For example, `std::out_of_range` defines a type of object to be thrown as exception. It reports errors that are consequence of attempt to access elements out of defined range.

```cpp
#include <iostream>
#include <stdexcept>  // contains standard exception types

int main() {
    try {
        throw std::out_of_range("Index out of bounds!");
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Caught an out_of_range exception: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Caught a generic exception: " << e.what() << '\n';
    }
}
```

### Custom Exceptions

When the standard exceptions are not enough, we can define our own exception classes.
It’s recommended to `inherit from std::exception` so that custom errors integrate smoothly with standard ones.

```cpp
#include <iostream>
#include <exception>

class GradeTooHighException : public std::exception {
public:
    const char* what() const throw() {
        return "Grade is too high!";
    }
};

int main() {
    try {
        throw GradeTooHighException();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

```
### 💡 Why Use Exceptions?
Without exceptions, error handling requires manual checks scattered throughout the code (e.g., if-else statements), which can make it messy and hard to maintain.
Using exceptions separates the normal logic from error-handling logic, making code cleaner and easier to reason about.

| #     | Principle                                                                                                                             | Example                                                                                                                                   |
| ----- | ------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| **1** | **Use exceptions only for exceptional cases**, not normal control flow.                                                               | ❌ Don’t use `throw` to break loops or signal normal states.<br>✅ Use it for unrecoverable errors (e.g., invalid input, resource failure). |
| **2** | **Catch exceptions by reference**, usually `const &`, to avoid slicing and unnecessary copies.                                        | `catch (const std::runtime_error& e)`                                                                                                     |
| **3** | **Throw by value, catch by reference.**                                                                                               | `throw MyException("error");` <br> `catch (const MyException& e)`                                                                         |
| **4** | **Be specific when catching exceptions.** Catch base types (`std::exception`) only when you truly don’t know what to expect.          | `catch (const std::out_of_range& e)` before `catch (const std::exception& e)`                                                             |
| **5** | **Ensure cleanup after exceptions** to prevent resource leaks. Use RAII objects like `std::vector`, `std::string`, or smart pointers. | `std::unique_ptr<File> file(new File("data.txt"));` → automatically cleaned up if exception occurs                                        |
| **6** | **Don’t ignore exceptions silently.** Always log or rethrow them if they can’t be handled locally.                                    | `catch (...) { std::cerr << "Unexpected error.\n"; throw; }`                                                                              |


### Reading material:  
[Exceptions - cplusplus.com](https://cplusplus.com/doc/tutorial/exceptions/)
[](https://www.geeksforgeeks.org/cpp/exception-handling-c/)
[std::exception - cppreference.com](https://en.cppreference.com/w/cpp/error/exception.html)

---

> Exception handling are practice in [Module 5](/CPP_Exercises_with_explanation/CPP_5) exercises.