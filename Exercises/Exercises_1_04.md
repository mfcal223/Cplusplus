# Exercise Level 01 - Nr 04 - 

## Goal
- Create a program that takes 3 parameters in this order: filename, string1 (s1), string2 (s2).  
- It will open the file, and copies the content into a new file (file.replace), replacing every match of s1 with s2.  
- Forbidden functions : std::string::replace, C file manipulation functions. 
- All the member functions of the class std::string are allowed, except replace.
- Handle unexpected inputs and errors.
- Files to turn in : Makefile, main.cpp, *.cpp, *.{h, hpp}

---

## Tools to use
1. File I/O (C++ style):
- std::ifstream infile(filename.c_str()); → input file stream.  
- std::ofstream outfile((filename + ".replace").c_str()); → output file stream.  
2. String search and manipulation:
- std::string::find → locate s1 in the line.  
- std::string::substr → extract pieces.  
- Manual concatenation (since std::string::replace is forbidden!).  

---

## Input/output with files

C++ provides the following classes to perform output and input of characters to/from files:

1. `ofstream`: Stream class to write on files.
2. `ifstream`: Stream class to read from files.
3. `fstream`: Stream class to both read and write from/to files.

These classes are derived directly or indirectly from the classes `istream` and `ostream`. If you have made previous exercises listed in this repository, you have already used objects whose types were these classes: `cin` is an object of class istream and `cout` is an object of class ostream. 

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}
```

This code creates a file called example.txt and inserts a sentence into it in the same way we are used to do with cout, but using the file stream myfile instead.  

## Headers to include

```cpp
#include <iostream> // for std::cout/std::cerr (messages & errors).
#include <fstream> //for std::ifstream (read) and std::ofstream (write).
#include <string> //for std::string, find, substr, etc.
```

## Handle filenames

std::string needs to convert to const char* for the constructor. 
To achive that, it is possible to use c_str()

`const char* c_str() const;`
- Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.
- This array includes the same sequence of characters that make up the value of the string object plus an additional terminating null-character ('\0') at the end.
- Source: https://cplusplus.com/reference/string/string/c_str/

> **c_str()** is just conversion to const char*. The open/creation success is indicated by the stream state (!infile / !outfile).

## Input checks
- checks correct number or arguments.
- checks s1 is not empty.

> C++ way to write to STDERR is using `std::cerr` 

## Open filename given
- Use c_str()
- If it fails, that means open failed because the file was not found, no perms, etc 

## Create the output file
- Also uses c_str() (because of limitations about using C++98).  
- Check it was created successfully.  

## Reads input file
This is done line by line with **std::getline**.  
  
`std::getline()`.
```html
- This preserves memory; good for large files.  
- It is similar to a “get next line”: reads until the delimiter (default '\n') or EOF.  
- It removes the delimiter from the returned string (so your line doesn’t end with \n). It needs to be added later.   
- It has `No fixed buffer size`: it grows the destination std::string as needed.  
```


pos: where we are in the line; start at 0.
line.find(s1, pos): search for next occurrence of s1 starting at pos.
Returns an index (type size_t), or std::string::npos if not found.
- On each match:
* Append the unchanged segment before the match: substr(pos, found - pos).
* Append the replacement s2.
* Advance pos past the matched s1 (found + s1.length()).
- When no more matches: append the remaining tail from pos to end.
- Write the rebuilt line and add a newline via std::endl (also flushes; you could use '\n' if you don’t care about flushing).  

###  Example:
s1 = "my collegue" 
s2 = "the Lizard" 
content in filename text1.txt  "Today I found my collegue at work in the bakery. He was all wet. My collegue forgot his umbrella at home. I feel sorry for my collegue, he was soaking."

#### Input Analysis 
s1 = "my collegue" → len(s1) = 11  
s2 = "the Lizard"  
line = "Today I found my collegue at work in the bakery. He was all wet. My collegue forgot his umbrella at home. I feel sorry for my collegue, he was soaking."  

#### The loop:
```cpp
size_t pos = 0, found;
while ((found = line.find(s1, pos)) != std::string::npos) {
    result += line.substr(pos, found - pos);
    result += s2;
    pos = found + s1.length();
}
result += line.substr(pos);
```

#### Iteration log (zero‑based)

Before start  
- pos = 0, result = ""

Iteration 1  
- found = line.find("my collegue", 0) = 14
- Append unchanged chunk: line.substr(0, 14) → "Today I found "
- Append replacement: "the Lizard"
- Update pos = 14 + 11 = 25
> result so far: 
> "Today I found the Lizard"

Iteration 2
- found = line.find("my collegue", 25) = 123
- (Note: "My collegue" at index ~66 has capital M, so it doesn’t match. We skip it; find is case‑sensitive.)
- Append unchanged chunk: line.substr(25, 123 - 25) →
" at work in the bakery. He was all wet. My collegue forgot his umbrella at home. I feel sorry for "
- Append replacement: "the Lizard"
- Update pos = 123 + 11 = 134

> result so far: 
> "Today I found the Lizard at work in the bakery. He was all wet. My collegue forgot his umbrella at home. I feel sorry for the Lizard"

Iteration 3 (termination)
- found = line.find("my collegue", 134) = npos (no more matches)
- Append tail: line.substr(134) → ", he was soaking."
- Exit loop

> Final output line
> Today I found the Lizard at work in the bakery. He was all wet. My collegue forgot his umbrella at home. I feel sorry for the Lizard, he was soaking.  

--- 

For much more information:
- https://cplusplus.com/doc/tutorial/files/

---

# "Sed is for losers"

The name "Sed is for losers" is a little joke/reference.

sed is a Unix command-line tool (“stream editor”) used for text transformations — especially things like find and replace inside files:  

```c++
sed 's/s1/s2/g' filename
```

This replaces every occurrence of s1 with s2 in filename.  

In this exercise, instead of using the already-existing sed tool (which would solve the problem instantly), you are asked to reimplement a simplified version of sed in C++.
That’s why the subject jokingly calls it “for losers” — as in: if you don’t know C++ you’d just use sed, but since you’re learning, you need to build your own logic from scratch.  

In other words:  

The exercise is about practicing file I/O and string search/replace.  

The name is a tongue-in-cheek way of saying: “Don’t be lazy and use sed, write it yourself in C++ to learn.”  