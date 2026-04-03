# C++ Module 09 - Containers & Algorithm - Ordered lookup and boundary cases

## TASK Description

Create a program called `btc` that receives a *filename* as argument.
That file contains lines describing a date and a bitcoin amount, written as:

**`YYYY-MM-DD | value`**

Your program must read a *CSV database of bitcoin exchange rates*, then for each valid line in the input file:
- validate the date format
- validate the numeric value
- find the exchange rate for that date
- if that exact date does not exist in the database, use the nearest previous available date
- print the result of: `value * exchange_rate`

If a line is invalid, the program must display an appropriate error instead of crashing.
At least one STL container must be used for this exercise that cannot be reused later in Module 09.

---

## Goal Explanation

Main question in this exercise is: `“How do I store historical keyed data and query it safely?”`

This exercise is about:  
1. reading a CSV database  
2. storing the data in a useful ordered structure  
3. validating another input file  
4. searching by date  
5. handling “exact match” and “closest lower match”  
6. printing either results or meaningful errors  

In this exercise, you ned to choose a container that **stores** 
- a `date` as *key*  
- an `exchange rate` as *value*  
AND that lets you **search** efficiently for an exact date (or the closest smaller one).  

You must reject bad input lines such as:
* missing separator  
* invalid date  
* negative value  
* value larger than 1000  
* malformed number  

You must handle edge cases, such as:
* no file provided / wrong filename / empty line
* malformed line  
* negative number  
* huge number  
* date not present in database  
* file cannot be opened  

---

## Building the program

### Step 0: Structure your class cleanly

Create BitcoinExchange class that includes
- Private data:
    - the container holding date/rate data
- Public interface:
    - OCF
    - method to load the database
    - method to process input file
    - Private helpers
        - trim string
        - parse database line
        - parse input line
        - validate date
        - validate value
        - leap year check
        - get rate for date
    - Method to print specific errors

----

### Step 1: Understand the two files

You have two inputs:

1. The provided CSV database

This is your historical reference database. Its job is to tell you the bitcoin rate for each stored date.

For example:
```csv
date,exchange_rate
2009-01-02,0
```

2. The user input file

This file contains lines to evaluate, like:

`2011-01-03 | 3`

That means:
**“Find the bitcoin rate for 2011-01-03, then multiply it by 3.”**

### Step 2: Choose your container

For this exercise, the most natural choice is:

`std::map<std::string, double>`

Why this is such a good fit:
- it stores key/value pairs
- keys are automatically sorted
- dates written as YYYY-MM-DD sort correctly as strings
- you can efficiently find exact matches and nearest lower dates

---

### Step 3: Implement database loading from data.csv

You need a function that:
- opens data.csv
- skips the header
- reads each line
- splits it by comma
- stores:
    * left side = date  
    * right side = exchange rate

Conceptually:

"2011-01-03,0.3"
becomes
db["2011-01-03"] = 0.3

This create the searchable historical database.

Consider using helper functions to trim spaces or any other parsing dependency.

---

### Step 4: Open the input file given as argument

The program name must be `btc`, and it must take a file as argument. 
If the file cannot be opened, it should print the appropriate error.

So your main() should first check:
1. correct number of arguments
2. whether the file can be opened

### Step 5: Read the input file line by line

Each line is expected to look like:
```
date | value
```

Usually the first line is a header such as that, and it can be skipped if it matches exactly.

For every other line:  
1. parse it  
2. validate it  
3. compute if valid  
4. print error if invalid  


### Step 6: Validate the line format

Before thinking about dates and numbers, first check the structure itself.  

You need to verify that the line contains:  
- a date part  
- the separator `|`  
- a value part  

Typical malformed examples:  
`2001-42-42`  
`2011-01-03|3` if your parser requires spaces strictly  
`2011-01-03 |`   
`| 42`   

For malformed input, the program should print an error: `Error: bad input => ...`  

#### 6.1 Validate the date (“does it look like a date?”)  
The subject says a valid date is in the format `Year-Month-Day`  
Make a helper that checks:     
* length is 10    
* positions 4 and 7 are `-`  
* year/month/day are numeric (all other required characters are digits)  
 

> 💡 the subject says a valid date is in format `Year-Month-Day`, but for robust evaluation it should validate the actual calendar too, not just the shape.  

Examples:  
`valid: 2011-01-03`  
`invalid: 2001-42-42`  
`invalid: 2011-02-30`  

Because `YYYY-MM-DD` is lexicographically sortable, there is no need to convert dates into integers to use them as ordered keys. For this specific subject, storing dates as strings is often the cleanest solution.  

**Summary:** 
```
2011-01-03 → valid

2011/01/03 → invalid
11-01-03 → invalid
2011-1-03 → invalid
abcd-ef-gh → invalid
```

#### Step 6.2 Implement calendar validation (“is it a real date?”)
Confirm the date is a real calendar date.  
Make a helper that checks:  
* month is 1 to 12  
* day is valid for that month (>= 1 && <= days in that month)  
* February must respect leap years (29 only if leap year)   

**Summary:** 
```
2012-02-29 → valid
2011-12-31 → valid

2011-02-29 → invalid
2011-04-31 → invalid
2011-00-10 → invalid
```

### Step 6.3 Validate the value
The value must be:
* a float or positive integer between 0 and 1000 inclusive  

So the programm should reject:   
- negative values  
- values larger than 1000  
- malformed numbers like `12abc`  
- empty value  

Typical error policy from subject examples:  
* negative -> `Error: not a positive number.`  
* too large -> `Error: too large a number.`  

---

### Step 7 — Implement input line parsing
Parse one line from the user’s input file.
The subject says each line must follow this format: "date | value".  .

The program needs a helper that will find work similarly to the database parsing.
1. find the separator `|`
2. split into left and right parts  
3. trim both sides  
4. validate date format and calendar  
5. validate the parsed value (use a helper to check malformed number, negative or too large)

**Test cases**
```
2011-01-03 | 3
2011-01-03|3
2011-01-03 | -1
2001-42-42
abcd | 1
2011-01-03 | abc
```

---

### Step 8: Find the exchange rate

There are two cases:
* Case 1: exact date exists
Use that rate directly.
* Case 2: exact date does not exist
Use the closest lower date, never the upper one. The subject is very explicit about that.

Conceptually:
- ask the map for the first key that is not less than the input date  
- if it matches exactly, use it  
- otherwise move one step back to get the previous date  
- if there is no previous date, that means the input date is earlier than the whole database, so that should be treated as an error or handled safely

What should the algorithm check:
1. if map is empty → error  
2. try exact match with find()  
3. if not found, use lower_bound(date)  
4. if the input date is earlier than the first date in the DB, there is no valid lower date. (this should become an error)
5. cases:
* if iterator points to exact date, use it
* if iterator is begin() and key is greater than date, there is no earlier date
* otherwise decrement iterator and use previous entry

> This is the core reason `std::map` is so suitable here.

---


### Step 9 : Compute and print
Once the program has:  
- valid date
- valid numeric value
- matching exchange rate

It should do:
```
result = value * rate
```
and prints:
```
date => value = result
```
as in the subject examples.

So your process-input-file() should :
1. open file  
      1. if fail: print Error: could not open file.
2. skip first line if it is header  
3. loop on each line  
4. call parseInputLine()  
      1. if invalid: 
            1. if valueStatus == 2 → Error: not a positive number.
            2. if valueStatus == 3 → Error: too large a number.  
            3. otherwise → Error: bad input => <line>
      2. if valid:  
            1. rate = getRateForDate(date)
            2. result = value * rate
      3. print: `date << " => " << value << " = " << result`
---

### Step : Keep processing even if one line is bad

Very important behavior:
one bad line should not kill the whole program.

For each line:
either print the computed result
or print the relevant error
then continue to the next line.

That is exactly how the example output behaves.

---

### Suggested edge cases to test
1. File handling
      1. no argument
      2. wrong filename
      3. empty file

2. Header / format
      1. correct header  
      2. wrong header  
      3. missing |

3. Date validation
      1. valid exact date  
      2. valid date not in DB, but lower date exists  
      3. date earlier than first DB entry  
      4. invalid month  
      5. invalid day  
      6. leap year and non-leap year cases

4. Value validation  
      1. integer  
      2. float  
      3. 0  
      4. 1000  
      5. negative value  
      6. value > 1000  
      7. malformed numeric text

5. Behavior
      1. several valid lines  
      2. one bad line in the middle of good lines  
      3. spaces around date/value

---

## Libraries and utilities used in MY code

### ifstream
`input file stream` --> object used to read from files.

> `std::cin` reads from keyboard input. `std::ifstream` reads from a file

ifstream commonly expects `const char *` string. Therefore, it becomes mandatory to use `c_str()` to provide the correct argument (considering we need to use C++98). 

For example:
```
std::string name = "data.csv";
name.c_str();
```
Returns :
```
"data.csv"
```

### stringstream

This is used to convert text into numeric values.  

`string rateStr = "0.3";` >>>> `double rate = 0.3;`
```
ss.str(rateStr);
ss >> rate;
```
load the string "0.3" into the stream, then extract a double from it  

When doing a check for only digits, this is an option: 
```
if (ss >> c)
    return 1;
```
This looks for anything else left after reading the number.

```
valueStr = "12abc" --> ss >> value ---> value = 12 BUT! "abc" is still inside the stream
```

### std::string::size_type  
This is used to be able to use `find()` with a string.  
`find()` does NOT return an `int`, but a special type used by `std::string` for position and sizes. This is an unsigned integer type appropriate for string indexes. 



---

# chatgpt guide


Step 5 — Implement calendar validation
Goal

Now confirm the date is a real calendar date.

This is beyond raw format and is the robust behavior evaluators usually expect.

What to code now

Add helpers:

bool isLeapYear(int year) const;
bool isCalendarDateValid(const std::string &date) const;

Inside isCalendarDateValid():

first call isDateFormatValid()
extract year, month, day
check:
month in 1..12
day >= 1
day <= days in that month
for February:
29 only if leap year
Good rule

Have a local array of month lengths:

int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

Then if leap year and month is 2, set February to 29.

What to test now
2012-02-29 → valid
2011-02-29 → invalid
2011-04-31 → invalid
2011-12-31 → valid
2011-00-10 → invalid
<details> <summary><strong>Step 5 code — calendar validation</strong></summary>
BitcoinExchange.hpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;

    std::string trim(const std::string &str) const;
    bool isDateFormatValid(const std::string &date) const;
    bool isLeapYear(int year) const;
    bool isCalendarDateValid(const std::string &date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &filename);
    void processInputFile(const std::string &filename);
};

#endif
Add to BitcoinExchange.cpp
bool BitcoinExchange::isLeapYear(int year) const
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}

bool BitcoinExchange::isCalendarDateValid(const std::string &date) const
{
    int year;
    int month;
    int day;
    int daysInMonth[12];
    std::stringstream ss;

    if (!isDateFormatValid(date))
        return false;

    ss.clear();
    ss.str(date.substr(0, 4));
    ss >> year;

    ss.clear();
    ss.str(date.substr(5, 2));
    ss >> month;

    ss.clear();
    ss.str(date.substr(8, 2));
    ss >> day;

    if (month < 1 || month > 12)
        return false;

    daysInMonth[0] = 31;
    daysInMonth[1] = 28;
    daysInMonth[2] = 31;
    daysInMonth[3] = 30;
    daysInMonth[4] = 31;
    daysInMonth[5] = 30;
    daysInMonth[6] = 31;
    daysInMonth[7] = 31;
    daysInMonth[8] = 30;
    daysInMonth[9] = 31;
    daysInMonth[10] = 30;
    daysInMonth[11] = 31;

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}
</details>
Step 6 — Implement value parsing and validation
Goal

Validate the right side of date | value.

The subject requires the value to be a float or positive integer between 0 and 1000.

What to code now

Add a helper like:

bool parseValue(const std::string &valueStr, double &value) const;

This helper should:

reject empty strings
use std::stringstream
reject malformed leftovers like 12abc
reject negative values
reject values greater than 1000

You may either:

return false and let the caller print a generic message
or throw specific exceptions
or return an enum

For a 42 project, a very clean choice is:

helper returns bool
caller prints the proper subject-style message

But because the subject uses different error messages for negative and too-large values, I prefer two checks:

parse first
then classify the error in the caller

Even better: use

int validateValue(...)

with statuses.

Recommended approach

Use:

int parseValue(const std::string &valueStr, double &value) const;

Return:

0 = ok
1 = malformed
2 = negative
3 = too large
What to test now
3
1.2
0
1000
-1
1000.01
abc
12abc
<details> <summary><strong>Step 6 code — value parsing and validation</strong></summary>
BitcoinExchange.hpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;

    std::string trim(const std::string &str) const;
    bool isDateFormatValid(const std::string &date) const;
    bool isLeapYear(int year) const;
    bool isCalendarDateValid(const std::string &date) const;
    int parseValue(const std::string &valueStr, double &value) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &filename);
    void processInputFile(const std::string &filename);
};

#endif
Add to BitcoinExchange.cpp
int BitcoinExchange::parseValue(const std::string &valueStr, double &value) const
{
    std::stringstream ss;
    char c;

    if (valueStr.empty())
        return 1;

    ss.str(valueStr);
    ss >> value;
    if (ss.fail())
        return 1;
    if (ss >> c)
        return 1;
    if (value < 0)
        return 2;
    if (value > 1000)
        return 3;
    return 0;
}
</details>
Step 7 — Implement input line parsing
Goal

Parse one line from the user’s input file.

The subject says each line must follow this format: "date | value".

What to code now

Add a helper like:

bool parseInputLine(const std::string &line, std::string &date, double &value, int &valueStatus) const;

It should:

find the separator |
split into left and right parts
trim both sides
validate date format and calendar
parse value

It can return:

true if everything is valid
false otherwise

And valueStatus helps distinguish:

malformed number
negative
too large
Important note

The line date | value header should be skipped in processInputFile(), not treated like a normal record.

Good behavior for bad input

If the separator is missing, or date is invalid:

Error: bad input => <whole line>

That matches the subject examples.

What to test now
2011-01-03 | 3
2011-01-03|3
2011-01-03 | -1
2001-42-42
abcd | 1
2011-01-03 | abc
<details> <summary><strong>Step 7 code — input line parsing</strong></summary>
BitcoinExchange.hpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;

    std::string trim(const std::string &str) const;
    bool isDateFormatValid(const std::string &date) const;
    bool isLeapYear(int year) const;
    bool isCalendarDateValid(const std::string &date) const;
    int parseValue(const std::string &valueStr, double &value) const;
    bool parseInputLine(const std::string &line, std::string &date,
        double &value, int &valueStatus) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &filename);
    void processInputFile(const std::string &filename);
};

#endif
Add to BitcoinExchange.cpp
bool BitcoinExchange::parseInputLine(const std::string &line,
    std::string &date, double &value, int &valueStatus) const
{
    std::string::size_type pipePos;
    std::string valueStr;

    pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return false;

    date = trim(line.substr(0, pipePos));
    valueStr = trim(line.substr(pipePos + 1));

    if (!isCalendarDateValid(date))
        return false;

    valueStatus = parseValue(valueStr, value);
    if (valueStatus != 0)
        return false;
    return true;
}
</details>
Step 8 — Implement nearest-lower-date lookup
Goal

Given a valid date, find:

exact date if it exists
otherwise the nearest earlier date

The subject explicitly says: use the closest lower date, not the upper one.

What to code now

Add:

double getRateForDate(const std::string &date) const;

Algorithm using std::map:

if map is empty → error
try exact match with find()
if not found, use lower_bound(date)
cases:
if iterator points to exact date, use it
if iterator is begin() and key is greater than date, there is no earlier date
otherwise decrement iterator and use previous entry
Important behavior

If the input date is earlier than the first date in the DB, there is no valid lower date.
That should become an error.

What to test now

Assuming DB has:

2011-01-03
2011-01-09

Then:

lookup 2011-01-03 → exact
lookup 2011-01-05 → use 2011-01-03
lookup a date earlier than first DB entry → error
<details> <summary><strong>Step 8 code — nearest-lower-date lookup</strong></summary>
BitcoinExchange.hpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;

    std::string trim(const std::string &str) const;
    bool isDateFormatValid(const std::string &date) const;
    bool isLeapYear(int year) const;
    bool isCalendarDateValid(const std::string &date) const;
    int parseValue(const std::string &valueStr, double &value) const;
    bool parseInputLine(const std::string &line, std::string &date,
        double &value, int &valueStatus) const;
    double getRateForDate(const std::string &date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &filename);
    void processInputFile(const std::string &filename);
};

#endif
Add to BitcoinExchange.cpp
double BitcoinExchange::getRateForDate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it;

    if (_rates.empty())
        throw std::runtime_error("Error: database is empty.");

    it = _rates.find(date);
    if (it != _rates.end())
        return it->second;

    it = _rates.lower_bound(date);
    if (it == _rates.begin())
        throw std::runtime_error("Error: no earlier date in database.");
    --it;
    return it->second;
}
</details>
Step 9 — Implement final result printing
Goal

Now connect everything:

open input file
skip header
read each line
parse
validate
lookup rate
print result
print errors but continue to next line

That matches the subject examples exactly.

What to code now

In processInputFile():

open file
if fail:
print Error: could not open file.
skip first line if it is header
loop on each line
call parseInputLine()
if invalid:
if valueStatus == 2 → Error: not a positive number.
if valueStatus == 3 → Error: too large a number.
otherwise → Error: bad input => <line>
if valid:
rate = getRateForDate(date)
result = value * rate

print:

date << " => " << value << " = " << result
Formatting note

Using default std::cout formatting is usually enough unless you want fixed precision.

What to test now

Use the exact sample from the subject.

<details> <summary><strong>Step 9 code — full processing and printing</strong></summary>
Full BitcoinExchange.cpp
#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _rates = other._rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trim(const std::string &str) const
{
    std::string::size_type start;
    std::string::size_type end;

    start = 0;
    while (start < str.size() && std::isspace(str[start]))
        start++;
    end = str.size();
    while (end > start && std::isspace(str[end - 1]))
        end--;
    return str.substr(start, end - start);
}

bool BitcoinExchange::isDateFormatValid(const std::string &date) const
{
    int i;

    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    i = 0;
    while (i < 10)
    {
        if (i != 4 && i != 7 && !std::isdigit(date[i]))
            return false;
        i++;
    }
    return true;
}

bool BitcoinExchange::isLeapYear(int year) const
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}

bool BitcoinExchange::isCalendarDateValid(const std::string &date) const
{
    int year;
    int month;
    int day;
    int daysInMonth[12];
    std::stringstream ss;

    if (!isDateFormatValid(date))
        return false;

    ss.clear();
    ss.str(date.substr(0, 4));
    ss >> year;

    ss.clear();
    ss.str(date.substr(5, 2));
    ss >> month;

    ss.clear();
    ss.str(date.substr(8, 2));
    ss >> day;

    if (month < 1 || month > 12)
        return false;

    daysInMonth[0] = 31;
    daysInMonth[1] = 28;
    daysInMonth[2] = 31;
    daysInMonth[3] = 30;
    daysInMonth[4] = 31;
    daysInMonth[5] = 30;
    daysInMonth[6] = 31;
    daysInMonth[7] = 31;
    daysInMonth[8] = 30;
    daysInMonth[9] = 31;
    daysInMonth[10] = 30;
    daysInMonth[11] = 31;

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}

int BitcoinExchange::parseValue(const std::string &valueStr, double &value) const
{
    std::stringstream ss;
    char c;

    if (valueStr.empty())
        return 1;
    ss.str(valueStr);
    ss >> value;
    if (ss.fail())
        return 1;
    if (ss >> c)
        return 1;
    if (value < 0)
        return 2;
    if (value > 1000)
        return 3;
    return 0;
}

bool BitcoinExchange::parseInputLine(const std::string &line,
    std::string &date, double &value, int &valueStatus) const
{
    std::string::size_type pipePos;
    std::string valueStr;

    pipePos = line.find('|');
    if (pipePos == std::string::npos)
        return false;
    date = trim(line.substr(0, pipePos));
    valueStr = trim(line.substr(pipePos + 1));
    if (!isCalendarDateValid(date))
        return false;
    valueStatus = parseValue(valueStr, value);
    if (valueStatus != 0)
        return false;
    return true;
}

double BitcoinExchange::getRateForDate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it;

    if (_rates.empty())
        throw std::runtime_error("Error: database is empty.");
    it = _rates.find(date);
    if (it != _rates.end())
        return it->second;
    it = _rates.lower_bound(date);
    if (it == _rates.begin())
        throw std::runtime_error("Error: no earlier date in database.");
    --it;
    return it->second;
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream       file(filename.c_str());
    std::string         line;
    std::string         date;
    std::string         rateStr;
    std::stringstream   ss;
    double              rate;
    std::string::size_type commaPos;

    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::getline(file, line);
    while (std::getline(file, line))
    {
        commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;
        date = trim(line.substr(0, commaPos));
        rateStr = trim(line.substr(commaPos + 1));
        ss.clear();
        ss.str(rateStr);
        ss >> rate;
        if (!ss.fail())
            _rates[date] = rate;
    }
}

void BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    std::string date;
    double value;
    double rate;
    double result;
    int valueStatus;

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    if (std::getline(file, line))
    {
        if (trim(line) != "date | value")
        {
            valueStatus = 0;
            if (!parseInputLine(line, date, value, valueStatus))
            {
                if (valueStatus == 2)
                    std::cout << "Error: not a positive number." << std::endl;
                else if (valueStatus == 3)
                    std::cout << "Error: too large a number." << std::endl;
                else
                    std::cout << "Error: bad input => " << line << std::endl;
            }
            else
            {
                try
                {
                    rate = getRateForDate(date);
                    result = value * rate;
                    std::cout << date << " => " << value
                              << " = " << result << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error: bad input => " << line << std::endl;
                }
            }
        }
    }

    while (std::getline(file, line))
    {
        valueStatus = 0;
        if (!parseInputLine(line, date, value, valueStatus))
        {
            if (valueStatus == 2)
                std::cout << "Error: not a positive number." << std::endl;
            else if (valueStatus == 3)
                std::cout << "Error: too large a number." << std::endl;
            else
                std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        try
        {
            rate = getRateForDate(date);
            result = value * rate;
            std::cout << date << " => " << value
                      << " = " << result << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
}
</details>
Step 10 — Add tests for bad inputs and boundary cases
Goal

Now stop coding and start evaluating behavior like an evaluator would.

The subject examples already tell you several important error cases.

What to test

I would organize the tests like this.

A. File handling
Test 1 — no argument
./btc

Expected:

Error: could not open file.
Test 2 — bad filename
./btc does_not_exist.txt

Expected:

Error: could not open file.
B. Valid input lines
Test 3 — exact date exists
date | value
2011-01-03 | 3
Test 4 — float value
date | value
2011-01-03 | 1.2
Test 5 — repeated same date
date | value
2011-01-03 | 1
2011-01-03 | 2
C. Closest lower date logic
Test 6 — exact date missing, lower exists
date | value
2011-01-08 | 2

Expected:

use the most recent earlier date in data.csv
Test 7 — date earlier than entire DB

Use a very old date like:

date | value
1900-01-01 | 2

You need to decide your exact error message.
Your current code prints bad input for lookup failure before earliest DB date, which is acceptable if you explain it during evaluation.

D. Invalid dates
Test 8 — invalid month
date | value
2011-13-01 | 1
Test 9 — invalid day
date | value
2011-04-31 | 1
Test 10 — non leap year Feb 29
date | value
2011-02-29 | 1
Test 11 — leap year Feb 29
date | value
2012-02-29 | 1
E. Invalid formatting
Test 12 — missing separator
date | value
2001-42-42
Test 13 — missing value
date | value
2011-01-03 |
Test 14 — missing date
date | value
| 3
Test 15 — extra garbage
date | value
2011-01-03 | 3abc
F. Invalid values
Test 16 — negative number
date | value
2012-01-11 | -1

Expected:

Error: not a positive number.
Test 17 — too large
date | value
2012-01-11 | 1000.01

Expected:

Error: too large a number.
Test 18 — huge integer
date | value
2012-01-11 | 2147483648

Expected:

Error: too large a number.
Test 19 — zero
date | value
2012-01-11 | 0

This should be accepted because the range is between 0 and 1000.

G. Mixed subject-style test

Use exactly the example style from the subject:

date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648

That should give behavior close to the example output shown in the PDF.

Very important practical notes
1. Why std::map<std::string, double> is the right choice here

Because the exercise is really “ordered lookup by key with fallback to nearest lower key.”
That is exactly what std::map is good at.