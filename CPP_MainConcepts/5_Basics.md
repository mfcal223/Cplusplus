# C++ BASIC CONCEPTS AND SYNTAX

## 🧠 ***Fundamental Concepts to Understand***

| Concept                     | What It Is                                                                                       | In C++ Terms                                                |
| --------------------------- | ------------------------------------------------------------------------------------------------ | ----------------------------------------------------------- |
| **Class**                   | A blueprint for creating objects. Like a struct, but with functions and access control.          | `class ClapTrap { ... };` defines behavior and data.        |
| **Object**                  | An instance of a class. Like creating a struct variable in C.                                    | `ClapTrap robot;` creates an object with its own state.     |
| **Constructor**             | Function that runs when an object is created.                                                    | `ClapTrap::ClapTrap(std::string name) { ... }`              |
| **Destructor**              | Function that runs when an object is destroyed.                                                  | Used to clean up memory: `~ClapTrap() { ... }`              |
| **Encapsulation**           | Keeping internal state private, accessed only via public methods.                                | Use `private:` and `public:` sections in your class.        |
| **Inheritance**             | A class can derive from another, reusing or overriding behavior.                                 | `class ScavTrap : public ClapTrap { ... }`                  |
| **Polymorphism**            | You can treat derived classes as base classes and still get the right behavior.                  | Achieved via virtual functions. Used in Module 04.          |
| **References**              | Like pointers in C, but safer. Cannot be null and always refer to something.                     | `std::string &ref = original;`                              |
| **Operator Overloading**    | You can redefine operators for your classes.                                                     | Example: `Fixed operator+(const Fixed &other);` (Module 02) |
| **Orthodox Canonical Form** | A class with 4 key functions: default constructor, copy constructor, copy assignment, destructor | Enforced from Module 02 onward                              |

## ***Basic syntax***

### Header file

Usually at the beginning of the file, one can find a preprocessor statement that starts with `#`

`#include <name_of_library>` 

The `#`  are directives read and interpreted by what is known as the preprocessor. In this case, the directive #include <name_of_library>, instructs the preprocessor to include a section of standard C++ code, known as header.  
The header files contain the definition of the functions and macros we are using in our program. 

#include <iostream> // TO USE std::cout (similar to printf in C)
#include <string>  // TO USE strings
---

### Lineal structure
The program can been structured in different lines and properly indented, in order to make it easier to understand for the humans reading it. Usually the initial line is the function declaration where it has the name of the function and the arguments it receives. 

C++ does not have strict rules on indentation or on how to split instructions in different lines. For example, instead of writting:

```
int main ()
{
  std::cout << " Hello World!";
}
```

I could have written:
```
int main () { std::cout << "Hello World!"; }
```

>  "std::cout" identifies the **st**andar**d** **c**haracter **out**put device.  
---

### Semicolons 
To separate statements, the program needs a `;`

> `;` = end of a statement.  

Many statements can be written in a single line, or each statement can be in its own line. The division of code in different lines serves only to make it more legible and schematic for the humans that may read it, but has no effect on the actual behavior of the program.  

---

### Adding comments
Same as in C, to add comments C++ supports two ways of commenting code:
```
// line comment
/* block comment */
```

---

### Namespace

A namespace in C++ is used to provide a scope or a region where we define identifiers.

It is useful to avoid naming conflicts.
Example:
```cpp
namespace MySpace {
    void hello() { std::cout << "Hi!\n"; }
}

MySpace::hello(); // call it
```
In order to refer to the elements in the std namespace a program shall either qualify each and every use of elements of the library (as we have done by prefixing cout with std::), or introduce visibility of its components. The most typical way to introduce visibility of these components is by means of using declarations:
`using namespace std;`  
The above declaration allows all elements in the std namespace to be accessed in an unqualified manner (without the std:: prefix).

As explicit qualification is the only way to guarantee that name collisions never happen, I will not use declaration in my projects.
This habit of explicitly writing std:: will actually make the later modules (inheritance, polymorphism) much easier to debug because I'll always know where each symbol comes from.

---

### Identifiers

A valid identifier is a sequence of one or more letters, digits, or underscore characters (_). Spaces, punctuation marks, and symbols cannot be part of an identifier. In addition, identifiers shall always begin with a letter. They can also begin with an underline character (_), but such identifiers are -on most cases- considered reserved for compiler-specific keywords or external identifiers, as well as identifiers containing two successive underscore characters anywhere. In no case can they begin with a digit.

C++ uses a number of keywords to identify operations and data descriptions; therefore, identifiers created by a programmer cannot match these keywords. 

For more information about the different fundamental data types go to:
https://cplusplus.com/doc/tutorial/variables/

#### Why use _ for member variables?
The use of a leading underscore (_) in variable names, especially for member variables in C++, is a widely used style convention.   
- Distinguish member variables from parameters/local variables:
In functions (especially constructors), you often have parameters with the same name as class members. The underscore helps tell them apart.  

```cpp
class Example {
    int _value;
    Example(int value) : _value(value) { /* ... */ }
};
```
Here, _value is the member variable, and value is the parameter.  

- Convention for readability:  
Many coding standards (including those used at 42 School and in professional C++ environments) use a leading underscore for private members. It immediately signals: "this is a member variable, not a local variable or parameter."  

- Not required by C++ syntax:  
It's just a convention, not a language rule. Some teams use other styles (m_value, value_, just value), but _ is common.  

#### Is there any restriction?
Leading double underscores (__) or underscore followed by a capital letter (_X) are reserved for the compiler/standard library.  
So, _value is fine, but __value or _Value should be avoided.  

---  

### Declaration of variables

C++ is a strongly-typed language, and requires every variable to be declared with its type before its first use. This informs the compiler the size to reserve in memory for the variable and how to interpret its value.  

```
1 int a;  
2 float mynumber;  
```  

If declaring more than one variable of the same type, they can all be declared in a single statement by separating their identifiers with commas. 

```
1 int a;  
2 int b;  
3 int c;  
```
---

### Initialization of variables 
When the variables in the example above are declared, they have an undetermined value until they are assigned a value for the first time. But it is possible for a variable to have a specific value from the moment it is declared. This is called the initialization of the variable.  

In C++, there are three ways to initialize variables. They are all equivalent and are reminiscent of the evolution of the language over the years:

(1) **C-like initialization**
This consists of appending an equal sign followed by the value to which the variable is initialized:

`type identifier = initial_value;`

`int x = 0;`

(2) **Constructor initialization** 
This encloses the initial value between parentheses (()):

`type identifier (initial_value);`
For example:
`int x (0);`

(3) **Uniform initialization**
It is similar to the above, but using curly braces ({}) instead of parentheses (this was introduced by the revision of the C++ standard, in 2011):

`type identifier {initial_value};`

` int x {0};`

---
### Strings 

The header <string> HAS TO be included.

The declaration/initialization is like any other data type.

```cpp
1 string mystring = "This is a string";
2 string mystring ("This is a string");
3 string mystring {"This is a string"};
```

Example:
```cpp
#include <iostream>
#include <string>
using namespace std;

int main ()
{
  string mystring;
  mystring = "This is the initial string content";
  cout << mystring << endl;
  mystring = "This is a different string content";
  cout << mystring << endl;
  return 0;
}
```

#### Basic std::string usage
Much easier than C strings. Provides built-in methods like .length(), .substr(), etc.

Examples:

```cpp

std::string str = "Hello";
str.length(); // 5
str[1];       // 'e'
```
---

### Streams (std::cout, std::cin, std::endl)
C++ version of printf and scanf.

Example:

```cpp
std::cout << "Enter your name: ";
std::string name;
std::cin >> name;
```
---



### Const keyword
Similar to C but used even more often:
```cpp
const std::string& //→ read-only reference (avoid copies).

int getValue() const; //→ promise not to modify the object.
```
---

### Static class members
Belong to the class, not to any instance.

Useful for shared counters, constants, etc.

```cpp
class Counter {
private:
    static int count; // shared across all instances
};
```


---
