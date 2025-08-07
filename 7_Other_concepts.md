# Additional Concepts 

## std::cout

In C++, cout is an object of the ostream class that is used to display output to the standard output device, usually the monitor. It is associated with the standard C output stream stdout. The insertion operator (<<) is used with cout to insert data into the output stream.  

>  "std::cout" identifies the **st**andar**d** **c**haracter **out**put device.  

**Syntax of cout**
```cpp
cout << var_name;
```
- `<<`: It is the insertion operator used to insert data into cout.
- `var_name`: It represents the variable or literal whose value you want to display.

The `endl` manipulator produces a newline character, exactly as the insertion of '\n' does; but it also has an additional behavior: the stream's buffer (if any) is flushed, which means that the output is requested to be physically written to the device, if it wasn't already.  
This affects mainly fully buffered streams, and cout is (generally) not a fully buffered stream. Still, it is generally a good idea to use endl only when flushing the stream would be a feature and '\n' when it would not. Bear in mind that a flushing operation incurs a certain overhead, and on some devices it may produce a delay.

If needed, `std::cout << std::endl;` can be added at the end of the output messages to insert a newline (\n) and flush the output buffer.

🛠️ **Below is a list of some commonly used member functions of `cout` in C++:**

| Member Function            | Description                                                       |
| -------------------------- | ----------------------------------------------------------------- |
| `cout.put(char)`           | Writes a single character to the output stream.                   |
| `cout.write(char*, int)`   | Writes a block of characters from the array to the output stream. |
| `cout.precision(int)`      | Sets the decimal precision for displaying floating-point numbers. |
| `cout.setf(ios::fmtflags)` | Sets the format flags for the stream.                             |
| `cout.width(int)`          | Sets the minimum field width for the next output.                 |
| `cout.fill(char)`          | Sets the fill character for padding the field.                    |


🧪 ***Examples:***
#1
```cpp
#include <iostream>
using namespace std;

int main() {
    char s[] = "Welcome at GFG";
    char c = '3';

    // Print first 6 characters
    cout.write(s, 6);

    // Print the character c
    cout.put(c);
  
    return 0;
}
```
Output:  
`Welcom3`

#2
```cpp
#include <iostream>
using namespace std;

int main() {
    double pi = 3.14159783;

    // Set precision to 5
    cout.precision(5);

    cout << pi << endl;

    // Set precision to 7
    cout.precision(7);

    cout << pi << endl;

    return 0;
}
```
Output  
`3.1416`  
`3.141598`

---

SourcE:  
https://cplusplus.com/doc/tutorial/basic_io/  
https://www.geeksforgeeks.org/cpp/cout-in-c/  
https://en.cppreference.com/w/cpp/io/cout.html  

---

## static_cast

This is the simplest type of cast that can be used. It is a compile-time cast. It does things like implicit conversions between types (such as int to float, or pointer to void*), and it can also call explicit conversion functions.  

Syntax of static_cast  
static_cast <dest_type> (source);  

The return value of static_cast will be of dest_type.  

### Interaction with other functions

consider the builtin function std::toupper().  
std::toupper() returns an int, not a char. 

std::toupper(int ch)
- This function is defined in <cctype>.
- It takes an int, not a char, because it needs to support the full range of unsigned char and EOF (-1).
- It returns an int, again for compatibility with EOF.
- Example: std::toupper('a') returns the int value of 'A' → 65, not 'A' itself.

If you want to print the char after converting it to Uppercase:

`std::cout << std::toupper(av[i][j]);` will output the int value, not the char itself.  
So 'a' would print 65, 'b' would print 66, etc.

To fix this, it is necessary to use static_char()  
`std::cout << static_cast<char>(std::toupper(av[i][j]));`  
- toupper('a') = 65 becomes 'A'
- 'A' is what is printed


Source:
https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/  
https://www.ibm.com/docs/en/i/7.4.0?topic=expressions-static-cast-operator-c-only