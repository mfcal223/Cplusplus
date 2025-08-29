# CPP Module 2

## General rules

The same as before. 
* Split files: Class declaration in *.hpp (with include guards), implementation in *.cpp.
* No function bodies in headers (except templates).
* Must compile with -Wall -Wextra -Werror and still compile with -std=c++98.
* No STL until Module 08/09 (containers/algorithms).
* No using namespace std; (forbidden unless subject says otherwise).
* Use of the Orthodox Canonical Form.

CPP Module 2 roadmap

ex00: structure + canonical form + raw storage only.

ex01: add int/float constructors, toInt(), toFloat(), and operator<< to print a floating representation.

ex02: add operator overloads (comparison, arithmetic, pre/post ++/--), and min/max static overloads.