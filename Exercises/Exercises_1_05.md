 Exercise : 05 -  Karen
 
Every person knows a Karen. She complains **A LOT**.
This are the level of intensity of her complains: 

• "DEBUG" level: Debugmessages contain contextual information. They are mostly  used for problem diagnosis.

• "INFO" level: These messages contain extensive information. They are helpful for  tracing program execution in a production environment.

• "WARNING" level: Warning messages indicate a potential issue in the system.  However, it can be handled or ignored.

• "ERROR" level: These messages indicate an unrecoverable error has occurred.  This is usually a critical issue that requires manual intervention.

---

You are going to automate Karen. It won’t be difficult since it always says the same  things.
You have to create a Karen class with the following private member functions:
 • void debug( void );
 • void info( void );
 • void warning( void );
 • void error( void );

Karen also has a public member function that calls the four member functions above  depending on the level passed as parameter:
 ```
 void  complain( std::string level );
 ```
---
The goal of this exercise is to use pointers to member functions. 
This is not a  suggestion. Harl has to complain without using a forest of if/else if/else. It doesn’t think  twice!
Create and turn in tests to show that Harl complains a lot. You can use the examples  of comments listed above in the subject or choose to use comments of your own.

--- 

## Summary 
- Karen has four private functions (debug, info, warning, error) that just print fixed strings.
- The public function complain(std::string level) must call the right private function.
- BUT: you cannot write a giant if/else if/else chain like:
```
if (level == "DEBUG") debug();
else if (level == "INFO") info();
...
```

Instead, you must use pointers to member functions — this is the “twist” of the exercise.
Why pointers to member functions?
Because the exercise is designed to:
- Show you that functions in C++ can be stored in a table (like a lookup map).
- Train you to avoid repetitive code (big if/else trees).
- Teach you a more elegant dispatching technique.

So complain() doesn’t decide by conditions, it simply looks up the function by string and calls it.

### What this means in practice

You’ll create an array of:
strings: "DEBUG", "INFO", "WARNING", "ERROR"
function pointers: addresses of &Harl::debug, &Harl::info, etc.

Then loop through the array:

for (int i = 0; i < 4; i++) {
    if (levels[i] == level) {
        (this->*funcs[i])();   // call correct function
        break;
    }
}

---

## Tools and methods that might be uselful.

### Using a type.

typedef (or using in modern C++) locks down a specific function signature.
return type and arguments have to be the same in order for several functions to be included in the same type.

So:
```
typedef void (Harl::*Action)();
```

means Action can only point to:  
* A member function of Harl  
* That returns void  
* That takes no arguments  

Example 1: Different return type  
```
int someFunc();   // returns int, no args
```

This cannot fit into Action, because Action expects void.  
You would need:  
```
typedef int (Harl::*IntAction)();
```

Example 2: Function with parameters  
```
void say(std::string msg);  // takes one argument  
```

This also doesn’t match Action, because Action expects zero arguments.  
You’d need:  
```
typedef void (Harl::*SayAction)(std::string);
```

Since all four Karen functions (debug, info, warning, error) have the same signature (void f(void)), they can all be stored in one Action[] array.  

If one of them had a different signature (say, returned int or took an argument), it would not be compatible with Action. You’d need a different typedef (and separate array) for those.  

👉 This is why the subject told you to make them all void func(void) — so you can store them together and use this neat lookup trick.  

--- 

### Use arrays for names and functions

They can be use as parallel lookup tables:  

* names[i] = the string ("DEBUG", "INFO", etc.)  
* funcs[i] = the corresponding pointer to the function (&Harl::debug, &Harl::info, etc.)  

So:  
```
names[0] = "DEBUG"    funcs[0] = &Harl::debug
names[1] = "INFO"     funcs[1] = &Harl::info
```
---

### Use "this" method
```
(this->*funcs[i])();
```
This is the syntax for calling a pointer-to-member function.  

* `this` is the current Harl object.  
* `*funcs[i]` dereferences the pointer-to-member.  
* `(this->*funcs[i])()` calls the method on this.  

So if `funcs[i] = &Harl::warning`, then:
```cpp
(this->*funcs[i])();   // is equivalent to: this->warning();
```
---

## Checklist for evaluation

### What the exercise requires (essentials)

1. A Karen class with four private methods: debug, info, warning, error.
2. A public complain(std::string level) that dispatches without an if/else forest, using pointers to member functions.
3. It must provide Proof showing Karen “complains a lot” (the exact sample texts in the PDF are examples, not strict golden outputs).
4. Karen.hpp declares the four private methods and complain.
5. Karen.cpp implements complain using a lookup table of strings and a parallel table of pointers-to-member (typedef void (Karen::*Action)(); and (this->*funcs[i])();). This meets the “no if/else forest; use member function pointers” rule.
6. main.cpp is a test driver. It parses a sentence, maps it to a level string with simple keyword search, and then calls h.complain(level). Tests are allowed/expected. The keyword layer is extra (fine), and the actual dispatch still goes through complain() as required.
7. No forbidden functions or libraries; only <iostream> and <string>. 
8. Nothing implemented inside headers (only declarations in .hpp, definitions in .cpp). 
9. C++98‑friendly (no C++11+ features). 

---

## EXAMPLES

1) Input: I want a better offer! → should trigger WARNING
main
ac == 2 → ok.
msg = "I want a better offer!".
Keyword scan (case‑sensitive):
Look for "calm" → msg.find("calm") == npos → not found.
Look for "offer" → msg.find("offer") == 18 (found at index 18).
⇒ decide level = "WARNING".

Call h.complain("WARNING").
Harl::complain("WARNING")
Setup:
names[0]="DEBUG", names[1]="INFO", names[2]="WARNING", names[3]="ERROR".
funcs[0]=&Harl::debug, funcs[1]=&Harl::info, funcs[2]=&Harl::warning, funcs[3]=&Harl::error.

Loop:
i=0: compare "WARNING" vs "DEBUG" → no match.
i=1: "WARNING" vs "INFO" → no match.
i=2: "WARNING" vs "WARNING" → match!
Call (this->*funcs[2])(); → calls this->warning();
warning() prints its message.
return; exits complain.
Program ends.

Printed line:
I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.

2) Input: Please stay calm, sir. → should trigger ERROR
main
ac == 2 → ok.
msg = "Please stay calm, sir."
Keyword scan:
"calm" → msg.find("calm") == 12 (found).
⇒ decide level = "ERROR" (ERROR has highest priority in our mapping).
Call h.complain("ERROR").
Harl::complain("ERROR")
Same arrays as above.

Loop:
i=0: "ERROR" vs "DEBUG" → no.
i=1: "ERROR" vs "INFO" → no.
i=2: "ERROR" vs "WARNING" → no.
i=3: "ERROR" vs "ERROR" → match!

Call (this->*funcs[3])(); → calls this->error();
error() prints its message.
return;.
Program ends.
Printed line:
This is unacceptable! I want to speak to the manager now.

3) Input: Nothing to see here. → no keyword match (fallback)
main
ac == 2 → ok.
msg = "Nothing to see here."
Keyword scan:
"calm" → not found.
"offer" / "else" → not found.
(Optionally check info/debug words if you added any; assume none.)
⇒ level = "UNKNOWN".
If you chose to fallback:
Either print a neutral message and do nothing,
Or route to a default level, e.g. h.complain("INFO").
If default is INFO: Harl::complain("INFO")
Arrays as above.
Loop:
i=0: "INFO" vs "DEBUG" → no.
i=1: "INFO" vs "INFO" → match!
Call (this->*funcs[1])(); → calls this->info();
Prints INFO message.
return;.
Program ends.
Printed line (if default to INFO):
I cannot believe adding extra bacon costs more money...