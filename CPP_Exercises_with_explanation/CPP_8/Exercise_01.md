# C++ Module 08 - Exercise 01 - Distance

## TASK

You must design a class named `Span` whose purpose is to **store a fixed amount of integers** and **compute distances between them**.  

The class is initialized with a `maximum capacity N` (an unsigned int) passed to its constructor. Once created, *the object cannot hold more than N numbers*.   

A public member function `addNumber()` allows inserting a single integer into the container. If the container already holds N elements, attempting to insert another value must result in an exception.  

The class must also expose two query functions:  
* `shortestSpan()` – returns the smallest difference between any two stored numbers  
* `longestSpan()` – returns the largest difference between any two stored numbers  

If the container contains fewer than two elements, no distance can be computed and an exception must be thrown.  

You are expected to thoroughly test your implementation, including scenarios with very large data sets (at least 10,000 values).

To improve usability, your class should also `support inserting many values at once using a range of iterators` ⚠️ , rather than calling addNumber() repeatedly.

> Hint: Standard containers already provide mechanisms for inserting ranges of elements using iterators. Studying them will help you design this feature efficiently.  

Running this code:
```c++
int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    return 0;
}
```
Shoudl output similar to this:
```c++
$> ./ex01
2
14
$>
```
---

## What is this exercise teaching ?

This exercise is not primarily about computing distances between numbers.   
Its real purpose is to introduce how modern C++ code is designed around the Standard Template Library (STL), and more specifically around `iterators` and generic `algorithms`.  

1️⃣ **Containers are implementation details, not contracts**
Internally, `Span` stores numbers using a specific STL container (typically `std::vector`).
However, *the public interface of the class must not depend on that choice*.  

This is why the exercise encourages inserting elements using iterator ranges instead of container-specific functions.  

The key idea is:
- A well-designed class should not care where data comes from, only how it is accessed.  
- By accepting iterators, `Span` can receive values coming from any STL container, without knowing or caring whether those values were stored in a vector, list, or deque.  

2️⃣ **Iterators are abstractions over access, not pointers**
* Iterators provide a uniform way to traverse data, regardless of how that data is stored internally.  
* This allows your class to operate on contiguous memory (std::vector), node-based structures (std::list), segmented storage (std::deque) using the same interface.  
* Algorithms should depend on iterator capabilities, not on concrete container types.  

3️⃣ **Algorithms operate on ranges, not containers**
STL algorithms operate exclusively on iterator pairs (begin, end).   
`Span` pushes things toward this realization by *making sorting and searching unavoidable*.

At this point, manually writing loops becomes less natural than simply expressing intent through algorithms like std::sort, std::min_element, or std::max_element.  

4️⃣ **Algorithmic thinking replaces manual iteration**
By guiding the student toward sorting and range-based algorithms, the exercise teaches about:
- reasoning about complexity.  
- choosing appropriate STL tools.  
- writing clearer and more expressive code.  


---

## Workflow

1. Create Span.hpp and Span.cpp
2. Create OCF for Span, including 1 constructor that receives an uint as parameter.
3. Internally, the object tracks:
* _maxSize (capacity limit) --> type uint
* _numbers (stored integers)  --> `vector`
4. Fill the Span
* Single insertion with addNumber(int)
      * Pushes one value into _numbers
      * If _numbers.size() == _maxSize, throws an exception (overflow protection)
* Bulk insertion with addRange(begin, end)
    * Accepts any iterator range (vector/list/deque/etc.)  
    * Internally calls addNumber() repeatedly, so the same capacity rules apply    
    * If the range exceeds capacity, it throws at the first overflow attempt  
5. Compute shortest span (create shortest_span())  
* Makes a sorted copy of _numbers  
* Compare adjacent elements  
* Track the minimum difference  
6. Compute the longest span (create longest_span())  
* Requires at least 2 elements  
* Sort the stored numbers  
* Find min and max  
* Return max - min  
7. Stress validation  
* Fill a Span with at least 10,000 values  
* “Not enough elements” (span computation invalid)  
    * Empty container: shortestSpan() throws   
    * One element: longestSpan() throws   
* Capacity enforcement: adding more than N with addNumber() throws
* Duplicates / zero span: inserting repeated numbers verifies that shortestSpan() can return 0
* Negative values: verify the sorting logic is correct and that distance results remain valid.
* Iterator-range insertion (addRange()):  
    * Insert from std::list<int> (proves iterator-based design works)  
    * Insert from std::deque<int> (optional additional proof)
    * Range overflow: inserting a range larger than capacity throws (current behavior: partial insert may have happened before the throw)
* Large dataset / performance sanity: insert 10,000 random values (compute both spans without printing all elements)

---

### Some interesting points about this design

1️⃣ **Why vector is the best internal choice for SPAN class?**  
Because the algorithm requires sorting and random access.  
There is a performance reason, as `std::vector` provides contiguous storage and better cache locality, making sorting more efficient than with a linked list (list requires its own method: list.sort()). So for numerical data processing it is usually the best choice.

So, your program starts with any container... But the SPAN object works with a `vector`.
```
external container (vector/list/deque)
            ↓
        iterators
            ↓
        addRange()
            ↓
     stored in Span::_numbers (vector)
```

2️⃣ **Why do you need sorting a copy of the span to compute the shortest span?**  
The shortest difference between any two numbers must occur between two adjacent values once the numbers are sorted. Elements need to be adjacent.  
Sorting reduces the problem from comparing every pair O(n²) to sorting once and scanning O(n log n).
The `copy` is sort for the simple reason that the function is `const` and should not modify the internal container. Sorting the original vector would change the stored order and violate the expected behavior of a read-only method.  

3️⃣ **Why does addRange() use iterators instead of accepting a vector?**  
As discussed above, using a "normal" function would limit the container you should use.
```
void addRange(std::vector<int> &v);
```
This only accepts vectors.

But with iterators, it can work with any container (vector, list, deque, set, array,..) 
```
std::sort(begin, end)
std::find(begin, end, value)
std::copy(begin, end, dest)
```
They operate on `ranges`, not containers.

`Using iterator ranges makes the function generic and container-independent.`

---

## Summary

The goal of this exercise is to practice working with STL containers, iterators, and algorithms.  
The `Span` class stores up to `N` integers using a `std::vector`.  
Numbers can be added individually with `addNumber()` or in bulk using an `iterator range with addRange()`, which allows inserting values from any STL container like list or deque.  
To compute the spans, `shortestSpan()` sorts a copy of the stored values and checks adjacent differences, while `longestSpan()` computes the difference between the minimum and maximum values.  
The class throws `exceptions` when trying to insert more than the capacity or when computing spans with fewer than two elements.
Some `tested edge cases` have been added to main.cpp, such as duplicates, negative numbers, overflow attempts, iterator insertion, and a stress test with 10,000 numbers.