# C++ Module 09 - Containers & Algorithm - Ordered lookup and boundary cases

- [C++ Module 09 - Containers \& Algorithm - Ordered lookup and boundary cases](#c-module-09---containers--algorithm---ordered-lookup-and-boundary-cases)
  - [TASK Description](#task-description)
  - [Goal Explanation](#goal-explanation)
  - [Building the program](#building-the-program)
    - [Step 0: Structure your class cleanly](#step-0-structure-your-class-cleanly)
    - [Step 1: Understand the two files](#step-1-understand-the-two-files)
    - [Step 2: Choose your container](#step-2-choose-your-container)
    - [Step 3: Implement database loading from data.csv](#step-3-implement-database-loading-from-datacsv)
    - [Step 4: Open the input file given as argument](#step-4-open-the-input-file-given-as-argument)
    - [Step 5: Read the input file line by line](#step-5-read-the-input-file-line-by-line)
    - [Step 6: Validate the line format](#step-6-validate-the-line-format)
      - [6.1 Validate the date (“does it look like a date?”)](#61-validate-the-date-does-it-look-like-a-date)
      - [Step 6.2 Implement calendar validation (“is it a real date?”)](#step-62-implement-calendar-validation-is-it-a-real-date)
    - [Step 6.3 Validate the value](#step-63-validate-the-value)
    - [Step 7 — Implement input line parsing](#step-7--implement-input-line-parsing)
    - [Step 8: Find the exchange rate](#step-8-find-the-exchange-rate)
    - [Step 9 : Compute and print](#step-9--compute-and-print)
    - [Step : Keep processing even if one line is bad](#step--keep-processing-even-if-one-line-is-bad)
    - [Suggested edge cases to test](#suggested-edge-cases-to-test)
  - [Libraries and utilities used in MY code](#libraries-and-utilities-used-in-my-code)
    - [ifstream](#ifstream)
    - [stringstream](#stringstream)
    - [std::string::size\_type](#stdstringsize_type)

---

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
