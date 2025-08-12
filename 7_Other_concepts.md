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

---

## Vectors

std::vector is a container from the C++ Standard Template Library (STL) that acts like a dynamic array — meaning it stores elements in a contiguous block of memory (like a C array) but can grow or shrink in size automatically as you add or remove elements.

> std::vector is like a resizable array — it behaves like a C array that can grow and shrink.

Here’s the breakdown:

1. What it is
Type: Template class (std::vector<T>) — you specify the element type.

Namespace: std (you must #include <vector>).

Memory: Stores elements contiguously for fast random access (like T arr[]).

Resizing: Can automatically allocate more memory when needed.

2. Key features
Dynamic resizing: Unlike a fixed-size array, std::vector grows when you push_back() new elements.

Random access: You can access elements in O(1) time using the [] operator or .at().

Iterator support: Works with STL algorithms (std::sort, std::find, etc.).

Automatic memory management: Frees its memory when destroyed (no need to delete[]).

Type safety: No need for manual casting or size tracking.

3. Common operations
cpp
Copiar
Editar
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers;        // Empty vector of ints

    numbers.push_back(10);           // Add elements
    numbers.push_back(20);
    numbers.push_back(30);

    std::cout << numbers[1] << "\n"; // Access element at index 1 (20)

    numbers.pop_back();              // Remove last element (30)

    std::cout << "Size: " << numbers.size() << "\n"; // Current size
    return 0;
}
4. Complexity
Access by index: O(1)

Add/remove at end (push_back, pop_back): Amortized O(1)

Insert/erase in middle: O(n) (elements after the position must shift)

5. When to use
You need a dynamic list of elements that allows fast random access.

You expect frequent additions/removals at the end rather than in the middle.

You want something safer and easier than raw arrays.  

Compared to the other dynamic sequence containers (deques, lists and forward_lists), vectors are very efficient accessing its elements (just like arrays) and relatively efficient adding or removing elements from its end. For operations that involve inserting or removing elements at positions other than the end, they perform worse than the others, and have less consistent iterators and references than lists and forward_lists.  

https://cplusplus.com/reference/vector/vector/

---
