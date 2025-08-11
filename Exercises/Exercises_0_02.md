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

$### $Declarations:  
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

1) <vector>
Needed because the tests use std::vector containers:

cpp
Copiar
Editar
std::vector<Account> accounts;
std::vector<int> deposits;
std::vector<int> withdrawals;
std::vector is a dynamic array that can grow/shrink automatically.

Here, it’s used to store:

All the Account objects (so we can loop over them easily),

Parallel lists of deposits and withdrawals to apply to each account.

Without <vector>, the compiler wouldn’t know the definition of std::vector.

2) <algorithm>
Needed because the tests use std::for_each:

cpp
Copiar
Editar
std::for_each(acc_begin, acc_end,
              std::mem_fun_ref(&Account::displayStatus));
std::for_each is a standard algorithm that applies a function to each element in a range [first, last).

Here, it’s used to call displayStatus() on each account in the accounts vector.

Without <algorithm>, the compiler wouldn’t know about std::for_each.

3) <functional>
Needed because the tests use std::mem_fun_ref:

cpp
Copiar
Editar
std::mem_fun_ref(&Account::displayStatus)
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

cpp
Copiar
Editar
    size_t const amounts_size     = sizeof(amounts)     / sizeof(amounts[0]);
    size_t const deposits_size    = sizeof(deposits)    / sizeof(deposits[0]);
    size_t const withdrawals_size = sizeof(withdrawals) / sizeof(withdrawals[0]);
Classic C++98 way to compute array lengths (no range helpers yet).

Typedefs (aliases)
cpp
Copiar
Editar
    typedef std::vector<Account> accounts_t;
    typedef std::vector<int>     ints_t;
Short names for vectors of accounts and ints (just readability).

Build vectors
cpp
Copiar
Editar
    accounts_t accounts(amounts, amounts + amounts_size);
Range constructor that builds a std::vector<Account> by calling
Account(int) on each value in amounts.
This works even though Account’s default constructor is private, because this constructor uses the int constructor, not the default one.

cpp
Copiar
Editar
    ints_t     deposits_v(deposits, deposits + deposits_size);
    ints_t     withdrawals_v(withdrawals, withdrawals + withdrawals_size);
Copies the integer arrays into std::vector<int> for easy iteration.

cpp
Copiar
Editar
    accounts_t::iterator acc_begin = accounts.begin();
    accounts_t::iterator acc_end   = accounts.end();
Store the account range iterators once; reused in displays below.

Initial snapshot
cpp
Copiar
Editar
    Account::displayAccountsInfos();
Calls the static function that prints global totals
(accounts count, total amount, total deposits, total withdrawals).

cpp
Copiar
Editar
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
Calls displayStatus() on each account:

std::for_each comes from <algorithm>.

std::mem_fun_ref comes from <functional> and adapts a pointer-to-member
&Account::displayStatus into a functor callable by for_each.

Output here shows each account’s index, amount, deposits, and withdrawals.

Deposits (zipping two ranges)
cpp
Copiar
Editar
    typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_zip;
C++98 doesn’t have zip iterators, so we roll our own: a pair of iterators that we advance together.

cpp
Copiar
Editar
    for (acc_int_zip it(accounts.begin(), deposits_v.begin());
         it.first != accounts.end(); ++(it.first), ++(it.second))
    {
        it.first->makeDeposit(*(it.second));
    }
it.first walks the accounts, it.second walks the deposits.

On each iteration, we call makeDeposit(deposit_value) on the current account.

Your Account.cpp must:

print a line with p_amount, deposit, new amount, and nb_deposits,

update both per-account and global counters.

cpp
Copiar
Editar
    Account::displayAccountsInfos();
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
Show the updated global totals and each account’s status after deposits.

Withdrawals (same zip trick)
cpp
Copiar
Editar
    for (acc_int_zip it(accounts.begin(), withdrawals_v.begin());
         it.first != accounts.end(); ++(it.first), ++(it.second))
    {
        it.first->makeWithdrawal(*(it.second));
    }
For each account, attempt a withdrawal with the corresponding value.

Your Account.cpp must either:

refuse (if withdrawal > amount) and print withdrawal:refused, or

perform the withdrawal (update per-account and global counters and print detailed line).

Final snapshot and exit
cpp
Copiar
Editar
    Account::displayAccountsInfos();
    std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));

    return 0;
}
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

- Constructors / destructor
	- Account(int initial_deposit) must:
		- assign _accountIndex,
		- set _amount = initial_deposit,
		- zero _nbDeposits/_nbWithdrawals,
		- update global counters (_nbAccounts++, _totalAmount += initial_deposit),
		- print a “created” line with timestamp.
	- ~Account() prints a “closed” line with timestamp (don’t change globals in the stock version).

Printing format
All output is very strictly formatted (exact separators, order, and words). Timestamps are printed by _displayTimestamp().

---

GPT explanation (needs reviwe)

tests.cpp — the driver that exercises your class
This file builds a small scenario to validate the class. It uses some pre‑STL11 idioms (because we compile with -std=c++98), so a couple of constructs may look old‑school.

Here’s what it does, step by step:

1) Includes and typedefs
cpp
Copiar
Editar
#include <vector>
#include <algorithm>
#include <functional>
#include "Account.hpp"
<vector>: stores accounts and integer sequences (amounts, deposits, withdrawals).

<algorithm>: uses std::for_each to call functions over ranges.

<functional>: uses adaptors like std::mem_fun_ref (C++98) to call member functions in algorithms.

Often you’ll see these typedefs (names can vary slightly):

cpp
Copiar
Editar
typedef std::vector<Account>       accounts_t;
typedef std::vector<int>           ints_t;
// a zipped iterator pair: one for accounts, one for ints
typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_t;
2) Seed data (arrays of ints)
It defines three arrays:

cpp
Copiar
Editar
int const amounts[]     = { 42, 54, 957, 432, 1234, 0, 754, 16576 };
int const deposits[]    = { 5, 765, 564, 2, 87, 23, 9, 20 };
int const withdrawals[] = { 321, 34, 657, 4, 76, 87, 23, 21 };
amounts → initial balance for each account (8 accounts).

deposits → one deposit per account.

withdrawals → one withdrawal per account.

These arrays are usually copied into std::vector<int> for convenience:

cpp
Copiar
Editar
accounts_t accounts(amounts, amounts + amounts_size); // constructs N accounts
ints_t     deposits_v(deposits, deposits + deposits_size);
ints_t     withdrawals_v(withdrawals, withdrawals + withdrawals_size);
Note: that constructor of std::vector<Account> uses the range (amounts, amounts + amounts_size) to build Account objects by calling Account(int) for each value — that’s why your Account(int) constructor must exist and work.

3) Display global info and per-account status
cpp
Copiar
Editar
Account::displayAccountsInfos();
std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
displayAccountsInfos() prints global totals (number of accounts, total money, total deposits/withdrawals so far).

Then we call displayStatus() on each account using std::for_each + std::mem_fun_ref (the C++98 way to say “call this member function on each element”).

4) Apply one deposit per account
Because C++98 didn’t have std::zip or range‑for, the code often “zips” two iterators manually:

cpp
Copiar
Editar
for (acc_int_t it(accounts.begin(), deposits_v.begin());
     it.first != accounts.end(); ++(it.first), ++(it.second))
{
    it.first->makeDeposit(*(it.second));
}
it.first walks the accounts vector.

it.second walks the deposits_v vector.

Each iteration calls makeDeposit(deposit_for_this_account).

After that, tests usually print the updated global info and per-account status again:

cpp
Copiar
Editar
Account::displayAccountsInfos();
std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
5) Apply one withdrawal per account
Same “zipped” technique:

cpp
Copiar
Editar
for (acc_int_t it(accounts.begin(), withdrawals_v.begin());
     it.first != accounts.end(); ++(it.first), ++(it.second))
{
    it.first->makeWithdrawal(*(it.second));
}
Then finalize with one last global display and per-account display:

cpp
Copiar
Editar
Account::displayAccountsInfos();
std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
6) Program exit
When main() returns, each Account in the std::vector is destroyed.
Your destructor runs for each object, printing the closing line for that account.

Why the output must match exactly
The subject gives you a log file with expected lines (except timestamps). The peer test compares your program’s output to that log. That’s why all prints must follow the exact format (order, separators ;, keys like index:, amount:, nb_deposits:…).

Quick mental model
Think of static members as the “bank dashboard”: totals across all accounts.

Think of per-object members as “this one account’s statement”.

The tests:

Create 8 accounts with initial balances,

Show totals and each account,

Make one deposit per account, show again,

Make one withdrawal per account, show again,

End (destructors print “closed”).

If you want, I can annotate a sample run line-by-line so you can map each printed number back to the exact code path (constructor, deposit, withdrawal, status, or destructor).