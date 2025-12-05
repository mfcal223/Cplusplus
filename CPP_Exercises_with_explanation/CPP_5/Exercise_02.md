# Module 05 - Exercise 02 – “Abstract Forms & Execution Authority”

## TASK

In this exercise, the concept of a Form is extended.  
The `base class is now called AForm`, and it becomes an **abstract class**, because **forms without an action are not meaningful**.  

It will contain:   
- its usual private attributes (name, signed flag, grade to sign, grade to execute),    
- an abstract method that derived forms must implement,   
- and logic to verify whether execution is allowed:   

```cpp
execute(Bureaucrat const & executor)
```

This will check that form can be executed, but only when:   
- it is *already signed*, and   
- the Bureaucrat attempting the execution has a *high enough grade* (i.e., grade <= required execution grade).   
If either is false, the method must throw an exception.  

You will implement `three new form types`, each of which performs a specific action on a given target, supplied through their constructors. Each of these will take one constructor argument: the form’s target.  
The concrete form classes should implement their own internal method that performs the action once validation succeeds.  

1. ShrubberyCreationForm :   
   1. Required grades: signing requires grade 145, execution requires grade 137.
   2. When executed, it creates a file named <target>_shrubbery in the current directory and writes ASCII trees into it.
2. RobotomyRequestForm: 
   1. Required grades: signing requires grade 72, execution requires grade 45.
   2. When executed, it prints drilling sounds and then — with a 50% probability — reports that the target was robotomized. The other 50% prints a failure.
3. PresidentialPardonForm:
   1. Required grades: signing requires grade 25, execution requires grade 5. 
   2. When executed, it announces that the target has been pardoned by Zaphod Beeblebrox.

The `Bureaucrat class` must also be updated so it can attempt to execute forms and report success or failure.
```cpp
void executeForm(AForm const & form) const;
```
* It should attempt to execute the form and display:
  * A success message if the execution worked.
  * An explicit error message if something went wrong.


---

## GOALS

This exercise combines inheritance, polymorphism, and exception handling into a cohesive system.  

### 🎯 1 — Understanding Abstract Classes / Pure Virtual Methods

AForm must be abstract because a form without an “action” makes no sense.  
You add a pure virtual function, which forces subclasses to implement their custom behavior.  

This means:  
- You cannot instantiate AForm.  
- All derived forms must implement their own execution behavior.   

> REMEMBER: "A class becomes abstract because it has at least one pure virtual functioN"

### 🎯 2 — Separation of concerns
- The base class checks validity (signed? grade OK?).  
- The derived classes implement the action.  

This demonstrates clean, maintainable OOP design.  

### 🎯 3 — Introducing Execution Permissions

Unlike ex01, signing is no longer enough. Execution requires:
- The form is signed,  
- The executor’s grade meets the form’s required execution grade.  

If either fails, you catch exceptions in `Bureaucrat::executeForm()` and print readable messages.  
This teaches to design `multi-stage permissions` using exceptions.  

### 🎯 4 — Overriding Behavior in Derived Classes

Each concrete form will implement a different “action” when executed.  
Example:  
```cpp
virtual void execute(Bureaucrat const& executor) const {
    // do something specific to this form  
}
```
This is `polymorphism` in action.  
The base class enforces the interface, and subclasses implement the behavior.  

### 🎯 5 —  File handling (ShrubberyCreationForm)

You learn basic file output using <fstream>.

### 🎯 6 —  Randomness (RobotomyRequestForm)

You implement a 50% success rate with rand() (C++98 safe).  

---

## What to do?

### 1️⃣ - Rename Form → AForm and make it abstract
- Add a pure virtual function:
```cpp
virtual void executeAction() const = 0;
```
- Add method `execute()`:

```cpp
void execute(Bureaucrat const & executor) const;
```

Inside this method:  
- Check if the form is signed.  
- Check if executor grade ≤ execGrade.  
- Throw exceptions if not.  
- Otherwise call executeAction() (the derived class implementation).  

### 2️⃣ Implement the three concrete form classes
* Implement OCF everywhere.  
* All take a single constructor parameter: `std::string target`.   ----->>>> **MEANING THIS IS A PRIVATE ATTRIBUTE OF EACH CLASS**  

In next section there is a more detailed explanation of each class.

### 3️⃣ Update Bureaucrat with executeForm()

```cpp
void Bureaucrat::executeForm(AForm const & form) const {
    try {
        form.execute(*this);
        std::cout << name << " executed " << form.getName() << std::endl;
    } catch (std::exception &e) {
        std::cout << name << " couldn’t execute "
                  << form.getName() << " because " << e.what() << std::endl;
    }
}
```

### 4️⃣ Write your own tests

Example:
```cpp
int main() {
    Bureaucrat bob("Bob", 1);
    Bureaucrat jim("Jim", 150);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm robot("Bender");
    PresidentialPardonForm pardon("Arthur Dent");

    bob.signForm(shrub);
    bob.executeForm(shrub);

    bob.signForm(robot);
    bob.executeForm(robot);

    bob.signForm(pardon);
    bob.executeForm(pardon);

    return 0;
}

```

---

## Form's Subclass

### ShrubberyCreationForm  

> **executeAction() =**   
>  Creates a file named <target>_shrubbery
>  Writes ASCII trees into <target>_shrubbery.

This is the first time in these serie of exercises that we produce output not in the terminal, but in the filesystem.


https://cplusplus.com/reference/string/string/c_str/

const char* c_str() const;
Get C string equivalent
Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.

This array includes the same sequence of characters that make up the value of the string object plus an additional terminating null-character ('\0') at the end.

### RobotomyRequestForm
  * Print “drilling noises…”
  * Use rand() % 2 for 50% success.

### PresidentialPardonForm
  * Prints: "target has been pardoned by Zaphod Beeblebrox"