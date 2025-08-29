# Exercise 02 - The JOB

> The task is to recreate Account.cpp using the provided Account.hpp, tests.cpp, and a log file. 

- Account.hpp → contains the class declaration and function prototypes.
- tests.cpp → already written tests that will call your class functions.

> Goal is to create : Account.cpp  + makefile to compile everything.
> Compare the output between your program and the log file provided. They should match except for the timestamp.   


## Analyzing the given files

### Account.hpp

#### Header guard: 

```cpp
#pragma once
```
It tells the compiler: "Include this header file only once per compilation, even if it’s included multiple times in different files."  
This prevents redefinition errors and speeds up compilation.  
It works like #ifndef / #define / #endif 
It is not part of c++98 but this is a given file. 

####  declares the Account class  

```cpp
class Account {
```

### Declarations:  
- static (class-wide) members  
	- variables and functions shared by all accounts:  
    	- _nbAccounts, _totalAmount, _totalNbDeposits, _totalNbWithdrawals  
        	- update them whenever you create/destroy an account or make a deposit/withdrawal.  
        	- these are `PRIVATE`  
      	- getNbAccounts(), getTotalAmount(), …, displayAccountsInfos()  
        	- Read or print those global counters.  
        	- these getters are `PUBLIC`   
- Per-object members:    
    - _accountIndex (assigned when constructed; typically equals the current _nbAccounts before increment).    
    - _amount (its balance),  
    - _nbDeposits,   
    - _nbWithdrawals (its own counters).  
- Operations:  
	- makeDeposit(int) updates this account’s _amount and _nbDeposits, and also _totalAmount and _totalNbDeposits. It prints a line showing previous amount, deposit, new amount, and per-account deposit count.  
	- makeWithdrawal(int) either:  
    	- refuses (if withdrawal > _amount) and prints withdrawal:refused,  
    	 or  
    	- performs it (update per-account and global counters) and prints details.  

#### Why are there 2 constructors and 1 destructor?
In Account.hpp you have:

```cpp
public:
    Account( int initial_deposit ); // PUBLIC constructor
    ~Account( void );               // Destructor

private:
    Account( void );                 // PRIVATE constructor
```
> Public constructor (Account(int initial_deposit))  

Allows creation of an Account object with an initial deposit amount.  
Example:  
```cpp
Account acc(1000); // Creates an account with 1000 units
```
> Private constructor (Account(void))  

Declared but not accessible from outside the class.   
Purpose: Prevents creating an Account without specifying an initial deposit.   
This enforces that every account starts with a known balance.  
Only the class itself (or its friends) could use this constructor internally.  

> Destructor (~Account(void))  

Called automatically when the object goes out of scope or is deleted.  
Used here to print "index:<n>;amount:<balance>;closed" for logging purposes.  

#### What is typedef Account t;?
```cpp
typedef Account t;
```
This creates an alias for the type Account.  
After this, t can be used as a shorthand for Account:  
```cpp
Account acc1(100);
t acc2(200);  // Same as Account acc2(200);
```

In practice, this is rarely needed here — it’s just part of the original given code style. It might have been included to match a certain coding convention or for use in generic programming. 

---

### Tests.cpp

#### headers included

1) **<vector>**
Needed because the tests use `std::vector` containers:  
```cpp
std::vector<Account> accounts;
std::vector<int> deposits;
std::vector<int> withdrawals;
```

`std::vector` is a dynamic array that can grow/shrink automatically.  

Here, it’s used to store:  
- All the Account objects (so we can loop over them easily),  
- Parallel lists of deposits and withdrawals to apply to each account.  

Without <vector>, the compiler wouldn’t know the definition of `std::vector.`  

2) **<algorithm>**
Needed because the tests use `std::for_each:`  
**std::for_each** is similar to a loop. 

```cpp
std::for_each(acc_begin, acc_end,
              std::mem_fun_ref(&Account::displayStatus));
```
**std::for_each** is a standard algorithm that applies a function to each element in a range [first, last).

Here, it’s used to call **displayStatus()** on each account in the accounts vector.  
Without <algorithm>, the compiler wouldn’t know about std::for_each.

Using `std::for_each` is equivalent to:
```c
for (int i = 0; i < size; ++i) {
    accounts[i].displayStatus();
}
```
So yes — it's looping over the array accounts[] and calling the displayStatus() method for each Account object.

It’s just a more functional-style way of writing a loop. But behind the scenes, it iterates like a regular loop.


3) **<functional>**
Needed because the tests use std::mem_fun_ref:

```
std::mem_fun_ref(&Account::displayStatus)
```

std::mem_fun_ref is a C++98 utility that converts a pointer to a member function into a callable object that can be passed to algorithms like std::for_each.

In this case, it adapts &Account::displayStatus so for_each can call it on each Account in the vector.

Without <functional>, the compiler wouldn’t know about std::mem_fun_ref.

💡 In short:
| Header         | Needed for...                                                 |
| -------------- | ------------------------------------------------------------- |
| `<vector>`     | `std::vector<Account>` and `std::vector<int>`                 |
| `<algorithm>`  | `std::for_each()` loop over accounts                          |
| `<functional>` | `std::mem_fun_ref()` to adapt member functions for `for_each` |


#### Main()

> seed data  

```cpp
    int const amounts[]     = { 42, 54, 957, 432, 1234, 0, 754, 16576 };
    int const deposits[]    = { 5, 765, 564, 2, 87, 23, 9, 20 };
    int const withdrawals[] = { 321, 34, 657, 4, 76, 87, 23, 21 };
```
Three parallel arrays:
- amounts → initial balances (8 accounts),
- deposits → one deposit per account,
- withdrawals → one withdrawal per account.

```cpp
    size_t const amounts_size     = sizeof(amounts)     / sizeof(amounts[0]);
    size_t const deposits_size    = sizeof(deposits)    / sizeof(deposits[0]);
    size_t const withdrawals_size = sizeof(withdrawals) / sizeof(withdrawals[0]);
```
Classic C++98 way to compute array lengths (no range helpers yet).

#### Typedefs (aliases)
```cpp
    typedef std::vector<Account> accounts_t;
    typedef std::vector<int>     ints_t;
```
Short names for vectors of accounts and ints (just readability).

#### Build vectors
```cpp
    accounts_t accounts(amounts, amounts + amounts_size);
```  

Range constructor that builds a std::vector<Account> by calling
Account(int) on each value in amounts.
This works even though Account’s default constructor is private, because this constructor uses the int constructor, not the default one.

```cpp
    ints_t     deposits_v(deposits, deposits + deposits_size);
    ints_t     withdrawals_v(withdrawals, withdrawals + withdrawals_size);
```
Copies the integer arrays into std::vector<int> for easy iteration.

```cpp
    accounts_t::iterator acc_begin = accounts.begin();
    accounts_t::iterator acc_end   = accounts.end();
```
Store the account range iterators once; reused in displays below.

#### Initial snapshot
```cpp
    Account::displayAccountsInfos();
```
Calls the static function that prints global totals
(accounts count, total amount, total deposits, total withdrawals).

```cpp
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
```
Calls displayStatus() on each account:

std::for_each comes from <algorithm>.

std::mem_fun_ref comes from <functional> and adapts a pointer-to-member
&Account::displayStatus into a functor callable by for_each.

Output here shows each account’s index, amount, deposits, and withdrawals.

#### Deposits (zipping two ranges)
```cpp
    typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_zip;
```
C++98 doesn’t have zip iterators, so we roll our own: a pair of iterators that we advance together.

```cpp
    for (acc_int_zip it(accounts.begin(), deposits_v.begin());
         it.first != accounts.end(); ++(it.first), ++(it.second))
    {
        it.first->makeDeposit(*(it.second));
    }
```
it.first walks the accounts, it.second walks the deposits.

On each iteration, we call makeDeposit(deposit_value) on the current account.

Your Account.cpp must:

print a line with p_amount, deposit, new amount, and nb_deposits,

update both per-account and global counters.

```cpp
    Account::displayAccountsInfos();
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
```
Show the updated global totals and each account’s status after deposits.

#### Withdrawals (same zip trick)
```cpp
    for (acc_int_zip it(accounts.begin(), withdrawals_v.begin());
         it.first != accounts.end(); ++(it.first), ++(it.second))
    {
        it.first->makeWithdrawal(*(it.second));
    }
```
For each account, attempt a withdrawal with the corresponding value.

Your Account.cpp must either:

refuse (if withdrawal > amount) and print withdrawal:refused, or

perform the withdrawal (update per-account and global counters and print detailed line).

#### Final snapshot and exit
```cpp
    Account::displayAccountsInfos();
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));

    return 0;
}
```
One last global + per-account display.
When main() returns, the std::vector<Account> goes out of scope and destroys all accounts; your destructor prints a closing line for each one.

Why those headers are necessary
<vector> → std::vector<Account>, std::vector<int>.

<algorithm> → std::for_each.

<functional> → std::mem_fun_ref.

<iostream> → sometimes used for spacing/blank lines; harmless to include.

"Account.hpp" → the class API used everywhere above.

---

## in the Account.cpp file to be created

### Headers
- #include "Account.hpp": Includes the header file with the class definition.
- #include <iostream>: Brings in C++'s standard input/output stream library for std::cout.
- #include <ctime>: Used for time functions (std::time, std::localtime, std::strftime).

### Static members 
```cpp
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```
These variables are static members of the class.  
Shared by all instances (like global variables for the class).  
In C, you’d use global variables; in C++ you attach them to classes for organization.  

### Utility Function: Display Timestamp
```cpp
void Account::_displayTimestamp(void)
{
    std::time_t now = std::time(NULL);
    std::tm *tm = std::localtime(&now);
    char buf[20];

    if (tm && std::strftime(buf, sizeof(buf), "[%Y%m%d_%H%M%S]", tm))
        std::cout << buf << " ";
    else
        std::cout << "[00000000_000000] ";
}
```
This is a static member function (does not depend on any instance).  
It prints a timestamp in a specific format.  
Uses C-style time functions, but prints with C++'s std::cout.  

### Constructors / destructor  
(1) Public Constructor  
- Member initializer list (: ...) sets member variables before entering the body.  
- The constructor updates static counters and prints creation info.  
- In C, you’d write a function to initialize a struct; in C++ the constructor automates this.  
(2) Destructor  
This is called automatically when an object goes out of scope. Prints account closure info.  
(3) Default (Private) Constructor
Private, so you can't accidentally construct an Account with no deposit.  

✅ 1) What is the ":" after the constructor declaration?
```cpp
Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts),
      _amount(initial_deposit),
      _nbDeposits(0),
      _nbWithdrawals(0)
```
This is called an initializer list.

It is used to initialize member variables before the constructor body runs.

It's more efficient than assigning values inside the constructor body (especially for const or reference members).

In C++, all members are initialized before the constructor body is executed — even if you don’t use the initializer list. Using : allows explicit and optimized control.

Example use:

```cpp
: _amount(initial_deposit)
```
This initializes _amount directly with initial_deposit, avoiding default construction followed by reassignment.

✅ 2) What is the list of variables in the initializer list?

```cpp
: _accountIndex(_nbAccounts),
  _amount(initial_deposit),
  _nbDeposits(0),
  _nbWithdrawals(0)
```
These are the member variables of the Account class being initialized:

_accountIndex(_nbAccounts)
→ _accountIndex is set to the current value of the static variable _nbAccounts.
This gives each account a unique index.

_amount(initial_deposit)
→ sets the starting amount of money in the account.

_nbDeposits(0) and _nbWithdrawals(0)
→ both start at zero for a new account.

✅ 3) Is _nbAccounts += 1; similar to i++?
Yes — but with a specific purpose:

```cpp
_nbAccounts += 1;
```

This is incrementing the total number of accounts created, using a static class variable. Each time a new Account is constructed:

_accountIndex is set to the current _nbAccounts value.

Then _nbAccounts is increased by one.

This means:
Account 0 → index 0
Account 1 → index 1
etc.

You can think of it as:

```c
i = 0;
array[i] = something;
i++; // prepare for next element
```
But in C++, it's used to assign a unique ID to each account.

### Static Getter Functions
Return the values of static members.  
Called as Account::getNbAccounts() (no need for an object).  
```cpp
int Account::getNbAccounts(void)   { return _nbAccounts; }
int Account::getTotalAmount(void)  { return _totalAmount; }
int Account::getNbDeposits(void)   { return _totalNbDeposits; }
int Account::getNbWithdrawals(void){ return _totalNbWithdrawals; }
```

### Displaying Account Information
Static method for printing overall stats.  

### Per-Account Operations
#### Make Deposit
```cpp
void Account::makeDeposit(int deposit)
```
Updates the account and global stats.  
Prints info for the log.  

#### Make Withdrawal
```cpp
bool Account::makeWithdrawal(int withdrawal)
```
If withdrawal > balance: print "refused" and return false.  
Else: update stats and print info.  

#### Balance & Status

```cpp
int Account::checkAmount(void) const
void Account::displayStatus(void) const
```
- Const functions (can’t modify object).  
- Prints balance and current status of the account.

---

## Deduction process

### How Each File is Used
| File          |	Role in Deduction |
|---------------|---------------------|
| Account.hpp	| Specifies required functions and variables; defines the interface. |
| tests.cpp     |	Shows how the functions are used and in what order; indicates what should be printed and when. |
| log file      |	Shows the required output format and sequence. Used to match your implementation’s behavior. |


### Typical Deduction Path
1. Read Account.hpp: List all required methods and variables.
2. Read tests.cpp: See how methods are called, what is expected to happen.
3. Read the log: Note the output format for each operation.
4. Implement Account.cpp: Ensure every function prints/logs what’s needed using correct variable updates.


**Step 1: Analyze the Interface (Account.hpp)**
This header defines all the functions, variables, and signatures your implementation must provide.
It tells you which data members exist (static and per-account), which methods need to be implemented (constructors, destructors, makeDeposit, makeWithdrawal, etc.), and their parameters.
Example:
```cpp
void makeDeposit(int deposit);
bool makeWithdrawal(int withdrawal);
void displayStatus(void) const;
static void displayAccountsInfos(void);
```

It also tells you about static members (shared among all accounts) and non-static members (per account).

**Step 2: Examine the Test Code (tests.cpp)**
The test code shows exactly how the Account class is used.
It creates accounts, performs deposits and withdrawals, and calls display functions.
Key deductions:
How accounts are constructed: accounts_t accounts( amounts, amounts + amounts_size );
→ Calls Account(int initial_deposit) for each amount.
How deposits/withdrawals are performed:
makeDeposit and makeWithdrawal are called in order for each account.
Which display functions are called, and when:
displayAccountsInfos() (static, for summary)
displayStatus() (per-account, for details)  

**Step 3: Match Output to the Log File**
The log file shows the exact output format and the order in which information is printed.
You must ensure that your implementation prints lines that match the log—except for the timestamp, which is dynamically generated.
Every operation (creation, deposit, withdrawal, closure, status display, summary info) corresponds to a log line.
Examples:
Account Creation:
[timestamp] index:0;amount:42;created

This means the constructor must print this line.
Account Closure:
[timestamp] index:0;amount:47;closed

The destructor prints this when the account is destroyed.
Deposit/Withdrawal:
[timestamp] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1

The deposit function must print this line. [timestamp] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
The withdrawal function must print this line, but only if successful. [timestamp] index:0;p_amount:47;withdrawal:refused
If the withdrawal is refused, print as above.
Status Display:
[timestamp] index:0;amount:47;deposits:1;withdrawals:0

The displayStatus() method must print this format.
Summary Display:
[timestamp] accounts:8;total:12442;deposits:8;withdrawals:6

The displayAccountsInfos() static method prints this.

**Step 4: Implement to Match Interface and Log**
You implement each function from Account.hpp, using the data members and static variables as needed.
Ensure every function that causes output prints lines in the format and sequence the log file shows.
Step 5: Validate with the Test Code
Run the tests (tests.cpp). If your output matches the log file (minus timestamp), your implementation is correct.
