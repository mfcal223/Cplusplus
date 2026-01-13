# Standard Template Library (STL) in C++

STL is a collection of pre-built classes and functions that make it easy to manage data using common data structures like vectors, stacks, and maps. It saves time and effort by providing ready-to-use, efficient algorithms and containers.

There are 3 features provided by STL:

![STL components](/CPP_Exercises_with_explanation/images/STL_components.png)


---

## Standard Containers

Standard containers are data structures provided by the C++ Standard Library.  

Each container is implemented as a template class that also contains the methods to perform basic operations on it.  
Every STL container is defined inside its own header file.

```c
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>

```

The properties they share are:
* They store elements.  
* They provide:
    * begin()  
    * end()  
* They expose iterators, not raw memory.  

This shared interface is what makes templates + algorithms possible.

| Type of Container |   Examples    |
|-------------------|---------------|
| Sequence Containers | Vector, Deque, List, Forward List, Array |
| Container Adaptors | Stack, Queue, Priority Queue |
| Associative Containers | Set, Multiset, Map, Multimap |
| Unordered Associated Containers | Unordered Set, Unordered Multiset, Unordered Map, Unordered Multimap |

---

### Vector
`std::vector` stores elements in a **contiguous memory block**, which allows for `fast random access` and efficient use of CPU cache. 

> std::vector = dynamic array

It stores elements one after another, like a C array.  
Accessing an element by index is a constant-time operation. However, inserting or deleting elements in the middle or at the beginning requires shifting all subsequent elements, making these operations potentially costly.  
It can grow automatically when needed. Appending elements at the end is generally fast, except when the internal array needs to be resized;

```c++
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v = {1, 2, 3};
    v.push_back(4);  // Fast append
    v.insert(v.begin() + 1, 10);  // Slower insert (shift elements)
    std::cout << v[1];  // Fast random access
}
```

When it runs out of space, it has to allocate a bigger block, copy elements there and free the old block.  

---

### Deque
`std::deque (double-ended queue)` also provides `fast random access`, but its internal structure is a sequence of multiple fixed-size memory blocks rather than a single contiguous block.     

> std::deque = segmented dynamic array  

This design allows efficient `insertion and deletion at both the front and back`.   

```c++
#include <deque>
#include <iostream>
int main()
{
    std::deque<int> d = {1, 2, 3};
    d.push_front(0);  // Fast front insertion
    d.push_back(4);   // Fast back insertion
    std::cout << d[2];  // Random access (slightly slower)
}
```

Random access is slightly slower than std::vector due to the segmented memory layout. Insertions or deletions in the middle are still relatively expensive.  

---

### List
`std::list` is a `doubly-linked list`, where each element is stored in a separate node with pointers to the previous and next elements.  
This structure allows `constant-time insertion and deletion anywhere in the list`, provided you already have an iterator to the position.  

```c++
#include <list>
#include <iostream>

int main()
{
    std::list<int> l = {1, 2, 3};
    auto it = ++l.begin();
    l.insert(it, 10);  // Fast insert at known position
    l.erase(--l.end());  // Fast erase at known position
    for (int x : l) std::cout << x << ' ';  // Linear traversal
}
```

❌ The disadvantages are: 
- it might me slower.  
- There is NO random acces (list[3] ❌), you must traverse the list from the beginning or end, which is a linear-time operation.
- Poor cache performance and memory overhead is also higher due to the storage of pointers.

Choosing the right sequence container depends on your application's performance needs and typical access patterns. 

---

### Comparison between different containers

| Feature          | `vector`       | `list`           | `deque`      |
| ---------------- | -------------- | ---------------- | ------------ |
| Memory layout    | Contiguous     | Linked nodes     | Blocked      |
| Random access    | ✅              | ❌                | ✅            |
| `push_back()`    | ✅ fast         | ✅ fast           | ✅ fast       |
| `push_front()`   | ❌ slow         | ✅ fast           | ✅ fast       |
| Insert in middle | ❌ slow         | ✅ fast           | ❌ slow       |
| Cache friendly   | ✅              | ❌                | ⚠️           |
| Typical use      | Default choice | Frequent inserts | Double-ended |


`deque` and `vector` provide random access, `list` provides only linear accesses. So if you need to be able to do container[i], that rules out `list`.  
On the other hand, you can insert and remove items anywhere in a `list` efficiently, and operations in the middle of `vector` and `deque` are slow.  

`deque` and `vector` are very similar, and are basically interchangeable for most purposes. There are only two differences worth mentioning. **First**, `vector` can only efficiently add new items at the end, while `deque` can add items at either end efficiently. *So why would you ever use a vector then?* Unlike `deque`, `vector` guarantee that all items will be stored in contiguous memory locations, which makes iterating through them faster in some situations.

> Rule of thumb:  
> If no strong reason → use std::vector

---

## Algorithms
STL algorithms offer a wide range of functions to perform common operations on data (mainly containers). These functions implement the most efficient version of the algorithm for tasks such as sorting, searching, modifying and manipulating data in containers, etc. All STL algorithms are defined inside the <algorithm> and <numeric> header file. Some of the most frequently used algorithms are:

Sort : Arranges elements in ascending order (default).
Binary Search : Checks whether a value exists in a sorted range.
Find : Searches for the first occurrence of a given value.
Count : Counts how many times a value appears in the given range.
Reverse : Reverses the order of elements in the given range.
Accumulate : Computes the sum of all elements in the range.
Unique : Removes consecutive duplicate elements.
Lower bound : Returns iterator to the first element ≥ value in a sorted range.
Upper bound : Returns iterator to the first element > value in a sorted range.
Replace : Replaces all occurrences of old value with new value in the given range.

---

## Iterators
Iterators are the pointer like objects that are used to point to the memory addresses of STL containers. They are one of the most important components that contributes the most in connecting the STL algorithms with the containers. Iterators are defined inside the <iterator> header file.

---
## Sources
**STL**  
https://www.geeksforgeeks.org/cpp/the-c-standard-template-library-stl/  

**Containers**  
https://codefinity.com/courses/v2/a291a2e5-7b39-4949-a817-ee8a26704755/d66a5209-fd0b-4cac-b084-18e58b02df2c/b4d0f355-f810-42fa-9072-3eab5fdfcfcc  

**Algorithms**  

**Iterators**   

