# C++ Module 09 - Containers & Algorithm - Reversed Polish Notation

## TASK

* **FILES TO SUBMIT** Makefile - main.cpp - RPN.hpp - RPN.cpp
* Create a program called `RPN` that receives a mathematical expression written in `Reverse Polish Notation` as a single command-line argument.
* The operands provided in the expression are always smaller than 10. This restriction applies to the input digits, not to intermediate values or the final result.  
* The program must evaluate the expression correctly and print the final result on standard output.  
* When the expression is invalid or execution fails, an error message must be sent to standard error.  
* The supported operators are only: `+`, `-`, `*`, `/`.   
* You must use at least one STL container for this exercise (different than **ex00**).  
* You do not need to manage: parentheses or floating-point numbers.  

Examples of valid behavior:
```c
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   //prints 42
./RPN "7 7 * 7 -"                   //prints 42
./RPN "1 2 * 2 / 2 * 2 4 - +"       //prints 0
./RPN "(1 + 1)"                     // prints an error
```

## GOAL EXPLANATION

Unlike normal math notation, `Reverse Polish Notation` places operators after operands.

Example:
```c
infix: 3 + 4
postfix/RPN: 3 4 +
```

This problem is forcing the user to think how a `stack-like workflow`:  
```
[read token] ---> [if number: store it]
             ---> [if operator: take the last two numbers, compute, store the result back]
```

A key pilar in this exercise will be a strict parsing & validation process.
The program should reject:  
1. bad characters  
2. malformed expressions  
3. missing operands  
4. too many remaining operands  
5. division by zero  

### Key Concepts

1. **why is a stack-like structure the right choice?**
This problems clearly shows manual stack behavior. It needs easy `push_back`, easy `pop_back`, and easy access to the last element with `back()`.  

A very good choice here is `std::list<int>`.

2. why order matters for `-` and `/`?
3. how is invalid input detected?
4. what happens if there are too many/few operands?
5. why must the final container size be exactly 1?

## Program Workflow

1. Validate argument count (needs `argc == 2` ) & pass argv[1] to RPN class.  
2. Split the expression into tokens: use `std::istringstream` to read space-separated tokens.
3. Validate Tokens: each token must be either a single digit `0` to `9` or one of the 4 operators: `+ - * /`. 
4. Numeral token: convert to INT and push into the container.
5. Operator token: 
      1. Sanity checks: 
            1. Check there are at least 2 values already IN the container.  
            2. Reject: unknown toke, <2 operands, division by `0`.
      2. pop right operand
      3. pop left operand
      4. compute `left op- operator - right op` ----> ALWAYS in THIS order
      5. push result back
6. If final container size is != 0, this should be rejected.
7. If any check fails, the program should print an error.
