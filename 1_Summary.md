# Cplusplus
Introduction to the use of C++, following simple exercises. The goal is to learn about Basics of Object-Oriented Programming (OOP). 

This repository will contain key concepts for c++ beginners. 

Every exercise will be based on C++98 standard, adn therefore will compile with `c++ -Wall -Wextra -Werror -std=c++98`.

There will be no external libraries.  
No printf/malloc/free. Instead, it will use C++ alternatives like cout, new, etc.
Also I will not use namespace or friend, STL containers or algorithms.

## **INTRODUCTION**

C++ is a general-purpose programming language that was developed by Bjarne Stroustrup as an enhancement of the C language to add object-oriented paradigm. It is currently used in a wide range of applications from game engines and application software to operating systems and embedded systems.

It is considered as a middle-level language as it combines features of both high-level and low-level languages.  
It has high level language features like object oriented programming, exception handling and templates along with low-level capabilities, such as direct memory manipulation and system-level programming.  
It is used to build embedded systems, game engines, web browsers, compilers and operating systems.  

### C versus C++

`C`  
- C is a basic, structural or procedural programming language (developed in 1972). Being procedural language C does not support Objects or Classes.  
- C has become popular because of its execution speed, simplicity, and flexibility. It is simple and easy to understand. It became the base for many other programming languages. If a user knows C, then it is easy for them to learn all other programming languages.  

> Procedural or Structural Language means C breaks the code into smaller modules in order to minimize the complexity of the program.  

 
- C follows a top-down approach 

`C++`  
- C++ is a general-purpose, object-oriented programming language (OOPs), developed in 1979. It is a multi-paradigm programming language as it supports both procedural and object-oriented programming languages. C++ has the property of the C programming language along with the classes and objects for user-defined data types.

> Object-oriented language means it has properties like classes, objects, polymorphism, inheritance, encapsulation, abstraction, data hiding, etc. The OOPs help in solving problems effectively, prevent data redundancy and ensure the flexibility of the code.

- C++ follows the bottom-up approach.
- C++ offers security features such as data hiding and encapsulation

`Both languages share similar features:`  
- Dynamic memory allocation: which helps programmers as they are not aware beforehand of the space or memory required while running the code.
- Fast and Powerful: they are compiler-based languagues containing many built-in functions and data types. 
- Portability. They are machine-independent languages. 
- They are case-sensitive languages which means small letters and capital letters are treated differently. 

🧩 Summary: Key Differences from C

| C                       | C++                                          |
| ----------------------- | -------------------------------------------- |
| Procedural              | Object-oriented                              |
| Struct = data only      | Class = data + behavior                      |
| `malloc/free`           | `new/delete` (with constructors/destructors) |
| No encapsulation        | `private`, `protected`, `public`             |
| No function overloading | Function and operator overloading            |
| No virtual functions    | Virtual functions for polymorphism           |

---

Sources: 
https://cplusplus.com/
https://www.mygreatlearning.com/blog/difference-between-c-and-c
https://www.geeksforgeeks.org/cpp/difference-between-c-and-c/



---
📌 Namespace Rules in CPP Modules (CPP0–CPP4)

| Case                                             | Allowed?        | Notes                                                                                                     |
| ------------------------------------------------ | --------------- | --------------------------------------------------------------------------------------------------------- |
| **`using namespace std;`**                       | ❌ **Forbidden** | Explicitly forbidden in all modules unless subject says otherwise.                                        |
| **Explicit `std::` prefixes**                    | ✅ **Allowed**   | Always use `std::cout`, `std::string`, `std::cin`, etc.                                                   |
| **Other `using namespace <name>;`**              | ❌ **Forbidden** | Applies to any namespace, not just `std`.                                                                 |
| **Custom namespaces (created by you)**           | ✅ **Allowed**   | You may define your own namespaces, but must access with `MyNamespace::function()`.                       |
| **`using std::cout;` (importing single symbol)** | ⚠️ Risky         | Not explicitly forbidden, but evaluators often consider it same as `using namespace std;`. Best to avoid. |
| **Qualified calls (e.g., `std::vector<int>`)**   | ✅ **Allowed**   | Always safe. (Note: STL containers allowed only in CPP08–CPP09)                                           |



constructuros
https://cplusplus.com/doc/tutorial/classes/