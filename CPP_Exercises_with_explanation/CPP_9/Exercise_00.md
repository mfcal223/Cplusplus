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

### Step 3: Load the CSV database first

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

#### Step 7: Validate the date  
Check:    
* length is 10    
* positions 4 and 7 are `-`  
* year/month/day are numeric  
* month is 1 to 12  
* day is valid for that month  
* February must respect leap years  

> 💡 the subject says a valid date is in format `Year-Month-Day`, but for robust evaluation it should validate the actual calendar too, not just the shape.  

Examples:  
`valid: 2011-01-03`  
`invalid: 2001-42-42`  
`invalid: 2011-02-30`  

Because `YYYY-MM-DD` is lexicographically sortable, there is no need to convert dates into integers to use them as ordered keys. For this specific subject, storing dates as strings is often the cleanest solution.  

### Step 8: Validate the value

The value must be:
* a float or positive integer  
* between 0 and 1000 inclusive  

So the programm should reject:   
- negative values  
- values larger than 1000  
- malformed numbers  
- empty value  

Typical error policy from subject examples:  
* negative -> `Error: not a positive number.`  
* too large -> `Error: too large a number.`  

### Step 9: Find the exchange rate

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

This is the core reason std::map is so suitable here.

### Step 10: Compute and print
Once you have:  
- valid date
- valid numeric value
- matching exchange rate

you do:
```
result = value * rate
```
and print:
```
date => value = result
```
as in the subject examples.

### Step 11: Keep processing even if one line is bad

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

### std::string::size_type  
