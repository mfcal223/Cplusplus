# C++ Module 08 - Containers and resizing

- [C++ Module 08 - Containers and resizing](#c-module-08---containers-and-resizing)
  - [TASK](#task)
  - [Goal Explanation : std::find()](#goal-explanation--stdfind)
  - [Creating Containers and adding elements](#creating-containers-and-adding-elements)
    - [std::vector](#stdvector)
    - [std::list](#stdlist)
    - [std::deque](#stddeque)

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


-----

## Creating Containers and adding elements

You could visualize containers as arrays but there is one major difference:  

❌ C array has a fixed size
```c
int arr[3];
arr[0] = 10;
```

Containers can dynamically grow or shrink. 
Depending on where they can add new elements they can use these functions:  

| Container     | Add at end    | Add at front            |
| ------------- | ------------- | ----------------------- |
| `std::vector` | `push_back()` | ❌ (slow / not provided) |
| `std::list`   | `push_back()` | `push_front()`          |
| `std::deque`  | `push_back()` | `push_front()`          |


It's the same function for the different containers, they just have a difference in performance.  

### std::vector
```c++
std::vector<int> v;
v.push_back(10);
v.push_back(20);
```

As Size is dynamic, What push_back() actually does is check if there is free space.  
* If yes → place element at the end  
* If no → reallocate (Increase size()), copywhat was already there, and then insert the new element.

Increase size()

So after:
```c++
v.push_back(10);
v.push_back(20);
v.push_back(30);
```

You have:
```c
[10][20][30]
```
Even though reallocation is triggered, the performance is ***constant amortized***(`amortized O(1)`).  
Everytime the reallocation happens, it usually double the size of the container.  
❌ No push_front() because shifting all elements would be too expensive. 

`Why not use v[0] = 10;?`  

Because initially:
```c++
std::vector<int> v;
v.size() == 0
```
There is no element at index 0.  
v[0] would be undefined behavior. 

You must either:
* push_back() elements  
or
* Create with a size:
```c++
std::vector<int> v(3);
v[0] = 10;
```

> The term ***amortized O(1)*** is a way of saying that while a single operation might occasionally be very slow, the average time per operation over a long sequence of events is constant.
> To understand the "amortization," we have to look at the two scenarios that occur when you add an element:
> 1. **The Happy Path (O(1))**: If the vector has spare capacity (allocated memory that isn't being used yet), it simply places the new element in the next slot and increments the size. This is extremely fast.
> 2. **The Reallocation Path (O(n))**: If the vector is full, it must find a larger chunk of memory elsewhere. It typically doubles its capacity, copies all existing elements to the new location, and then deletes the old memory. Because it has to move **n** elements, this specific push_back() takes **O(n)** time.
> Because the vector doubles its size each time it grows, reallocations happen less and less frequently as the vector gets larger. When you sum up all the work done across $n$ operations and divide by $n$, the result is a small constant number. Mathematically, the expensive $O(n)$ moves are "spread out" over many cheap $O(1)$ moves, so they don't dominate the total time. 

---

### std::list
```c++
std::list<int> l;
l.push_back(10);
l.push_front(5);
```
* push_back() → add node at tail
* push_front() → add node at head
* Both are O(1)

### std::deque

```c++
std::deque<int> d;
d.push_back(10);
d.push_front(5);

```

* Supports both ends efficiently
* Internally uses blocks, not shifting