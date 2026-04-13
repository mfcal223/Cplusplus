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

---

## 👾👾 PROGRAM'S WORKFLOW 👾👾

### 1. 📐 Parse the arguments

Receive all numbers from argv[1] onward.

The program must reject:
* no arguments,
* empty strings,
* negative values,
* zero if you interpret “positive” strictly,
* non-digit input,
* values larger than INT_MAX,
* duplicates (I choose to reject them).

### 2. 📨 Store the same input in two containers

Store the exact same validated numbers in:
```cpp
std::vector<int>
std::deque<int>
```
These are the two containers that will be timed.

### 3. 📨 Print the original sequence

Print the input once, before sorting.

### 4. 🩰 Understand the `Ford–Johnson idea`

Ford–Johnson works by pairing elements, recursively sorting the larger member of each pair, then inserting the smaller members into carefully limited positions in a special order to minimize comparisons.  

A practical way to implement it is:
Given this example:
```
8 3 7 4 9 2 6 5
```

* *group elements into pairs*,
```
(8,3) (7,4) (9,2) (6,5)
```

* *inside each pair, order them* so:  
      * small <= large  
      * where always b[i] <= a[i]
```
(b,a) (b,a) (b,a) (b,a)
(3,8) (4,7) (2,9) (5,6)
```

* *sort the pairs according to their large values*,  
```
(5,6) (4,7) (3,8) (2,9)
```

Now the "a"s are sorted: `6 > 7 > 8 > 9`  

* *build the main chain* using:  
    * the first pair’s small  
    * then all sorted large values
```
5 6 7 8 9
```
This is already sorted.  

* keep the remaining small values as pending  

The remaining bs are: `4 3 2`  
They will not be inserted blindly. `4` belongs to the pair whose `a = 7`...so `4` only needs to be searched before `7` and **not** after (we know 4 < 7 as they are in the same pair).  
Same thing happens with `3` and `2`: `3` needs to be before `8`, and `2` before `9`

> Since we know b[i] < a[i], them we know that b[i] MUST be placed before a[i] in the chain.  
> Instead of searching the whole chain, it only searches `[0 ... position_of(a_i)]`.  
 

* *insert pending values* into the main chain using:
    * binary search
    * Jacobsthal-guided insertion order

* if there is an odd leftover value, insert it at the end with binary search.

---

### 🗃️ Why Jacobsthal order matters

Ford–Johnson is not just “insert the pending values left to right”.

The algorithm chooses a smarter insertion order to reduce comparisons.  
A common practical implementation uses Jacobsthal-number groups to decide the insertion order of pending elements.  

Just to recap: after pairing and sorting by `a`, there is a `main` chain (already sorted) + a list of `pending` elements (bs)

```
Pairs sorted by a:
(5,6) (4,7) (3,8) (2,9)

Main chain:
5 6 7 8 9

Pending:
4 3 2
```

As mentioned before, every b[i] has a partner a[i].  
We know that b[i] < a[i], so it needs to be placed before a[i] in the chain. The program only searches `[0 ... position_of(a_i)]`.  

Using `binary search`, considering the main chain is already sorted, makes a **log(n)** comparisons instead of a linear one. 

#### 💡 The Jacobsthal idea (the tricky part)
Values from the pending chain is going to be made in a special order derived from Jacobsthal numbers.
```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)
```
> Jacobsthal sequence: 0, 1, 1, 3, 5, 11, 21, ...

The numbers in this sequence will be used to define groups of indices to insert in a specific order. 

```
Insert indices:
1
3, 2
5, 4
11,10,9,8,7,6
...
```
The insertion is backwards in each group.
👉 `Insert elements that give the largest possible uncertainty reduction first`.  
This minimizes the worst-case comparisons.  

###### *Example*
🪜 **Considering this new array of ints**
```
# Original set  
22, 13, 75, 88, 92, 101, 77, 15, 9

# Make pairs and sort by a
(13,22)     → (b1, a1)
(15,77)     → (b2, a2)
(75,88)     → (b3, a3)
(92,101)    → (b4, a4)
9           → lefover
```

`a-chain`=  22, 77, 88, 101  
`b-values` =  13, 15, 75, 92  
`Straggler` = 9

⛓️ **Build the chains:**  ⛓️
🔗 `Main chain`    = `b1` + all `a`s
```
13, 22, 77, 88, 101
```

🔗`Pending chain` = b2 = 15, b3 = 75, b4 = 92, 9

➿ **Insertion order**
> Jacobsthal numbers: (0, 1), 1, 3, 5, 11...

Leaving aside the first 0 and 1 of the sequence, we can group the pending indexes according to the Jacobsthal numbers.
- from 1 → 3
- from 3 → 5
- etc.

J[1-3] = indices 2,3 ==> backwards: b3,b2  
J[3-5] = index 4    ==> b4 (only one)

Final insertion order = `3,2,4` => `b3,b2,b4` => `75, 15, 92`

📥 **Actually insert**
Remember 2 things: 
- Main chain: `13, 22, 77, 88, 101`
- Always `b[i] < a[i]`

1. Insert b3 = 75
* b3's partner is a3    = 88
* look from 0 to 88     = [13, 22, 77]
* Insert: [13, 22, `75`, 77, 88, 101]

2. Insert b2 = 15
* b2's partner is a2    = 77
* search before 77      = [13, 22, 75]
* Insert: [13, `15`, 22, 75, 77, 88, 101]

3. Insert b4 = 92
* b4's partner is a4    = 101
* look from 0 to 101    = [13, 15, 22, 75, 77, 88]
* Insert: [13, 15, 22, 75, 77, 88, `92`, 101]  

4. Insert straggler
Serach the entire chain 
[`9`, 13, 15, 22, 75, 77, 88, 92, 101]

 👉 *Jacobsthal order tries to insert elements where the search range is best balanced*.



---

## 🔍 How is the correct position found? (Binary Search) 🔍

The key idea is `Instead of checking elements one by one (like linear search), binary search takes the current range → split it into TWO halves → discard one half`

> "Binary" = 2 parts

At this point in the algorithm you have:
* a sorted main chain
* a value b[i] that you must insert
* a restriction: only search before its partner a[i]

1. At which index should I insert b[i] so the array stays sorted?
Consider this example:
```
Main Chain:
[13, 22, 77, 88, 101]

Insert:
b3 = 75

Partner:
a3 = 88 ---> 88 is [3] in the main chain
```

You only search in  [13, 22, 77] == from [0] to [3] (exclusive)(*)
```
[13, 22, 77]
---------------
 [0] [1] [2]
```

(*) exclusive because we already know that b[i] < a[i]. There is no need to compare again to a[i] or to compare beyond it.

2. Compare to the middle value of your range
```
left = [0]
right = [3] (exclusive)

mid = (0 + 3) / 2 = 1
value at mid = [1] = 22

Compare: 75 > 22 → go right
---
```

3. Compare again
```
left = [2]
right = [3] (exclusive)
mid = (2 + 3) / 2 = [2]
value at [2] = 77
Compare: 75 < 77 → go left
```

👉 FIND the position where all elements before are <= value

4. Compare again
```
left = 2
right = 2 → stop ==> INSERTION INDEX = 2
Insert: [13, 22, *75*, 77, 88, 101]
```
---

### 5. Sort std::vector 🤖

Implement the whole process for std::vector<int>.

The subject strongly advises implementing separately for each container instead of hiding everything behind one generic function.

Use clock() from <ctime> to measure the time..

### 6. Sort std::deque 🤖

Repeat the same logic for std::deque<int>.

Use `clock()` from <ctime> to measure the time.

### 7. Print the sorted sequence 🤖

Print the sorted result once.

### 8. Print both timings 🤖

Measuring the time the deque/vector starts sorting and measuring the time when that process endes, gives you the duration of the process itself. 

`vector` often performs better because (particularly from > 20 elements):
* its elements are stored contiguously in memory
* binary-search access is very cache-friendly
* many operations benefit from better locality

> To read about `clock()` click [here](https://www.w3schools.com/cpp/ref_ctime_clock.asp)

---

## 👾👾👾Summary 👾👾👾
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


