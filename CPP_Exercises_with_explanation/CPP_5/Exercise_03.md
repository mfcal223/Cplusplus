# CPP Module 5 - Exercise 03 – Intern: Automatic Form Factory

## TASK

In this final exercise of Module 05, you must `implement a class called Intern`.
This class represents a beginner employee who has *no personal attributes—its* only purpose is to create forms on request.

The Intern exposes *a single important method*:

```cpp
AForm* makeForm(std::string const& formName, std::string const& target);
```

* formName = string identifying a known form type.
* target = name that will be assigned to the created form.
* returns a pointer to a newly allocated AForm, matching the requested type.

Whenever a form is successfully created, the intern should print:
```
Intern creates <formName>
```

If the form name does not match any recognized form, the function must:
- print a clear and explicit error message
- return NULL (or throw an exception if you choose to, but the subject only requires a message)

Example: 
```cpp
{
    Intern RandomIntern;
    AForm* someForm;

    someForm = RandomIntern.makeForm("robotomy request", "Bender");
}

// This should create a RobotomyRequestForm targeted at "Bender".
```

The main goal is to design this function without resorting to an unreadable chain of if/else-if statements.  
You are expected to use a cleaner structure (arrays, parallel lookup tables, function pointers, etc.) to map form names to their respective constructors.  

---

## GOAL

1. Factory design pattern: 
- The Intern acts as a simple factory: you give it a string, and it gives you back a concrete object derived from AForm.

2. Polymorphism & dynamic allocation: 
- makeForm() returns a pointer to an abstract base class (AForm*).
- The caller does not need to know which specific form is created.

3. Memory ownership
- The intern allocates forms using new.
- Whoever calls makeForm() must delete the returned pointer.  

4. Error handling: When the name does not exist, the intern should inform the user and not crash.  

5. Indirection instead of if/else chains: find an alternative way to called the correct constructor.

---

## Execution

There might be many ways to avoid a long if/else statements. 
The option I choose was using a lookup table. 
I define an array with pointer to functions that will call the correct constructor. 
To match which one, I also define an array of valid form names. 
The function will need to match form choice >>> valid form name >>> matching function pointer >>> correct constructor called.

Here is an brief explanation of the makeForm() I decided to build:

* Parameters: the function receives a string (formName) and the form's target.  
* Return type: t must create the correct AForm-derived object (*AForm).  
* Instead of if/else statements, it uses a `lookup table (mapping)` method:  
    * there is an array of strings "names[3]" = array of valid form names. 
        * each string corresponds to valid options of formName.
* There is an array of function pointers "creators[3]" for which a new type (typedef) is defined.
    * each helper function receives the form's target.
    * each helper function calls a the constructor that matches the functions name.
    * each helper function returns the correct AForm* object.

* Workflow:  form name → index → constructor
	* it uses a for loop to search through the known form names 
    	* try to match formName with names[i].  
	* When it finds a match, it uses the function pointer at the same index to create the correct form.  
    	* match names[i] to creators[i].  
	* If no match is found, it hits the error message.
