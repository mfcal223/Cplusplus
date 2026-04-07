# C++ Module 09 - Containers & Algorithm - 

## TASK

* Create a program named `PmergeMe` inside `ex02/`.
* Files to turn in: Makefile - main.cpp - PmergeMe.hpp - PmergeMe.cpp

Your program must:
1. receive a list of positive integers from the command line,
2. sort that list with the merge-insert sorting strategy, specifically the Ford–Johnson algorithm,
3. print an error message to standard error if the input is invalid,
4. use two different STL containers,
5. support a sequence of at least 3000 integers.

The output must show:

1. a line containing the original sequence,
2. a line containing the sorted sequence,
3. a line with the execution time for the first container,
4. a line with the execution time for the second container.

* The exact time-display format is flexible, but it must be precise enough to make differences visible.  

* It is recommended to code the algorithm separately for each container instead of writing one generic implementation.  

* Containers used in earlier exercises of this module cannot be reused here.   
* Duplicate handling is your choice.  

## GOAL EXPLANATION
This project is not about sorting, but to make you understand
- how to parse and validate command-line input safely,  
- how to work with STL containers directly,  
- how to compare behavior/performance between two containers,  
- how the Ford–Johnson idea works,  
- how to separate algorithmic steps clearly enough to explain them during evaluation.  


## PROGRAM'S WORKFLOW

### 1. Parse the arguments

Receive all numbers from argv[1] onward.

The program must reject:
* no arguments,
* empty strings,
* negative values,
* zero if you interpret “positive” strictly,
* non-digit input,
* values larger than INT_MAX,
* duplicates (I choose to reject them).

### 2. Store the same input in two containers

Store the exact same validated numbers in:
```cpp
std::vector<int>
std::deque<int>
```
These are the two containers that will be timed.

### 3. Print the original sequence

Print the input once, before sorting.

### 4. Understand the `Ford–Johnson idea`

A practical way to implement it is:
* group elements into pairs,
* inside each pair, order them so:  
      * small <= large  
* sort the pairs according to their large values,  
* build the main chain using:  
    * the first pair’s small  
    * then all sorted large values
* keep the remaining small values as pending  
* insert pending values into the main chain using:
    * binary search
    * Jacobsthal-guided insertion order
* if there is an odd leftover value, insert it at the end with binary search.

#### Why Jacobsthal order matters

Ford–Johnson is not just “insert the pending values left to right”.

The algorithm chooses a smarter insertion order to reduce comparisons.
A common practical implementation uses Jacobsthal-number groups to decide the insertion order of pending elements.

That is why in the code below you will see the insertion order generated from Jacobsthal progression.

### 5. Sort std::vector

Implement the whole process for std::vector<int>.

The subject strongly advises implementing separately for each container instead of hiding everything behind one generic function.

### 6. Sort std::deque

Repeat the same logic for std::deque<int>.

### 7. Measure time

Use clock() from <ctime>.

The subject explicitly says the measured time should include the full work, not only the bare sort step.

### 8. Print the sorted sequence

Print the sorted result once.

### 9. Print both timings

Show something like:

time with std::vector
time with std::deque

---

## Summary
The program uses std::vector and std::deque because exercise 02 requires two containers, and previous exercise containers cannot be reused. It parses only positive integers, rejects duplicates by choice, then applies a Ford–Johnson-style merge-insert process: makes ordered pairs, sorts pairs by their larger elements, builds the main chain from the largest elements, then inserts the smaller pending elements using binary insertion in Jacobsthal order. Finally, it times the full process for both containers.

---
## Test cases
./PmergeMe 3 5 9 7 4
./PmergeMe 8 3 2 9 7 1 6 5 4
./PmergeMe 42
./PmergeMe 10 20 30 40 50 60 70
./PmergeMe -1 2
./PmergeMe 1 a 3
./PmergeMe 2 2 3
./PmergeMe 2147483648
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`