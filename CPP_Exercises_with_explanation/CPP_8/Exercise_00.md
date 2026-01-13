# C++ Module 08 - Containers

- [C++ Module 08 - Containers](#c-module-08---containers)
  - [TASK](#task)
  - [Goal Explanation : std::find()](#goal-explanation--stdfind)

## TASK

Create a generic `function template` called `easyfind` that works with any container holding integers.  

The function receives (parameters):  
- A `container` (templated type T),   
- An `integer` value to search for.  

It must `look for the first occurrence of the given integer inside the container`.  

If the integer is found, return the corresponding position (iterator).  
If it is not found, signal the error either by throwing an exception or returning an invalid result, similarly to how standard containers behave.  

The function should rely on STL tools and algorithms where appropriate.  

**Important clarifications:**

❌ You do not have to handle associative containers
(e.g. std::map, std::set)

✅ You are expected to use <algorithm> (e.g. std::find)

✅ You are expected to work with iterators, even if indirectly

---

## Goal Explanation : std::find()

So conceptually, `easyfind` is a generic wrapper around `std::find`.   
   
> “Don’t reinvent the wheel — use the STL”  

`std::find()` is a C++ STL function defined inside <algorithm> header file.
std::find() works with `any container that supports iterators`, such as arrays, vectors, lists, and more.

The behaviour of this function template is like this:  
```c++
template<class InputIterator, class T>
  InputIterator find (InputIterator first, InputIterator last, const T& val)
{
  while (first!=last) {
    if (*first==val) return first;
    ++first;
  }
  return last;
}
```
Where `first` and `last` are the initial and final positions in a sequence. The range searched is *[first,last)*, which contains all the elements between first and last, including the element pointed by first but not the element pointed by last.  
`val` = Value to search for in the range.  
T shall be a type supporting comparisons with the elements pointed by InputIterator using operator==.  

**Return value**: An iterator to the first element in the range that compares equal to val. `If no elements match, the function returns last`.  

```
❌ It does NOT: ❌
- Print errors
- Return -1
- Exit the program
```

***Sources:***
[Cplusplus - Algorithm - Find](https://cplusplus.com/reference/algorithm/find/)  
[CppReference - Algorithm - Find](https://en.cppreference.com/w/cpp/algorithm/find.html)  
[GfG - std::find in cpp](https://www.geeksforgeeks.org/cpp/std-find-in-cpp/)  

---

