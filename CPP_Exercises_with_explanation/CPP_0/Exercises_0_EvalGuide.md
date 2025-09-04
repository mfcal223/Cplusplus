# List of sensible topics to review before evaluation.

## 🧠 GENERAL QUESTIONS

These apply to all exercises:

### 🧩 Syntax & Rules

1. **What are the compilation flags used and why?** (`-Wall -Wextra -Werror -std=c++98`)
2. **Why can’t we use `printf()` or `malloc()` in this module?**
3. **Why is `using namespace std;` forbidden in the projects?**
4. **What happens if you implement a function in a header file?**
5. **Why are class names written in UpperCamelCase format?**
6. **What are include guards and why are they necessary?**

<details>
<summary>Click to expand answers </summary>  

1. To ensure warnings are treated as errors and the code follows C++98 standard.  
2. This is C++. You're expected to use std::cout, new, and delete instead.  
3. It can lead to namespace pollution and error due to ambiguous symbol resolution in larger projects. The standard requires qualified names like std::cout.  
4. If you do that, the function is copied into every translation unit that includes the header. This can lead to multiple definition errors at link time.
5. UpperCamelCase (also known as PascalCase) is a common C++ convention. It improves readability, helps differentiate classes from variables or functions.
6. To prevent multiple inclusion of the same header file. They avoid duplicate definition errors during compilation.  
</details>

---

## CPP 0

### 🔊 EX00 — Megaphone

Simple CLI program that prints arguments in uppercase.

#### Core Questions

1. What does `std::toupper()` do and what does it return? What is `static_cast<char>` doing in your code?
2. What’s the difference between `std::endl` and `"\n"`?
3. Why do we check `ac == 1` in `main()`?

<details>
<summary>Click to expand answers </summary>  

1. It returns the uppercase version of a character if it's alphabetic, else returns the character unchanged. Because toupper takes and returns an int (ascii representation of a char), and you must cast it to char for proper output.
2. \n inserts a newline. std::endl inserts a newline and flushes the output buffer. \n is faster unless you need flushing.
3. Because if no message is included, the program prints * LOUD AND UNBEARABLE FEEDBACK NOISE *.
</details>
---

### ☎️ EX01 — PhoneBook

Basic contact manager using classes (no dynamic allocation).

#### Class Structure

1. What are the two classes used? What is each one responsible for?
2. Why are Contact fields private?  
3. What does the constructor of `Contact` or `PhoneBook` do? 
4. How do you track where to insert the next contact? 
5. What happens when you add the 9th contact?

<details>
<summary>Click to expand answers </summary>  

1. **Contact** stores individual contact info. **PhoneBook** manages a fixed array of 8 Contacts.
2. To follow **encapsulation** principles. Fields can only be accessed via getters/setters.
3. The constructor of Contact sets up the object so it's ready to store data. The PhoneBook constructor initializes contactCount and nextIndex to 0.
4. Using nextIndex, which is incremented each time a contact is added and wraps around using % 8.
5. The oldest contact (index 0) is overwritten using circular indexing (nextIndex = (nextIndex + 1) % 8).

</details>

#### Input/Output & Formatting

1. How do you validate that fields are not empty?
2. How does your program ensure only digits are accepted in phone numbers?
3. What is `std::setw(10)` and how is it used to format output?
4. What happens if the user enters a wrong index in SEARCH?
5. What happens when 9th contact is added?

<details>
<summary>Click to expand answers </summary>  

1. Added a function to the class: *getNonEmptyInput* that will check that.
2. Added a function to the class: *getPhoneNumberInput* that will check that. It loops through each character and check if all are digits using isdigit().
3. It sets the field width to 10 characters for right-aligned display formatting.
4. An error message will appear, and loop goes back to expecting a "command".
5. The oldest contact (index 0) is overwritten using circular indexing (nextIndex = (nextIndex + 1) % 8).
</details>

#### C++ Specifics

1. What is the role of `const` in a getter function?
2. How is truncation handled in SEARCH display?
3. Why is `truncate()` marked as `static`? 
4. How did you avoid dynamic memory? (e.g., no `new` in PhoneBook)

<details>
<summary>Click to expand answers </summary>  

1. It's a "promise" to avoid changing the value of the variable it is "getting".
2. A helper function truncate() cuts strings longer than 10 characters to 9 and adds a dot .
3. Because it doesn't use any class instance variables. It's a utility function local to the .cpp file.
4. All contacts are stored in a statically-sized array.
</details>
---

### 💼 EX02 — Account.cpp Reconstruction

Reverse engineering: rebuild implementation from a header, tests, and logs.

#### Static Concepts

1. What’s a static member? Give an example.
2. What’s the difference between static and non-static members?

<details>
<summary>Click to expand answers </summary>  

1. Static members are shared across all instances of a class. Used here to track global statistics like total accounts and total amount.

</details>

#### Constructors and Initialization

1. Why is the default constructor private?
2. What’s the purpose of the member initializer list?
3. How is `_accountIndex` determined?

<details>
<summary>Click to expand answers </summary>  

1. To prevent creation of accounts without an initial deposit.
2. It is feature to initialize member variables before the constructor body runs, to improve performance and supports const/reference members.  
3. It is set to the current value of _nbAccounts before _nbAccounts is incremented. This gives each account a unique index.

</details>

#### Behavior Logic

1. What must `makeDeposit()` and `makeWithdrawal()` update?
2. What do you print if a withdrawal fails? 
3. What’s the expected output format for the logs? 
4. Why do we use `_displayTimestamp()` in every log line?

<details>
<summary>Click to expand answers </summary>  

1. The account's own balance and deposit/withdraw count, as well as the global _totalAmount, _totalNbDeposits, _totalNbWithdrawals.
2. You print: index:<n>;p_amount:<amt>;withdrawal:refused
3. Log lines must follow strict patterns like: [timestamp] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1 Each action has its own format, shown in the test log file.
4. To timestamp every action for clear chronological tracking, just like a real banking log. It prints the current time in [YYYYMMDD_HHMMSS] format before logging any account activity.

</details>

---
