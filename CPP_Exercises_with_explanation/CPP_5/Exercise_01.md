# Module 05 - Exercise 01 - "Who is singning this mountain of papers?"

## TASK
In this exercise, we extend the previous bureaucrat system with a new class called Form.  

A Form has:  
* a constant name,  
* a boolean flag telling whether it is signed or not,  
* a constant grade required to sign it,  
* a constant grade required to execute it.  

The grade rules are the same as before: valid grades are between 1 and 150, where 1 is the best and 150 is the worst. If a form is created with an invalid grade requirement (too high or too low), it must throw an exception.  

The class must provide getters for all attributes and a method that allows a Bureaucrat to sign the form (Bureaucrat::signForm() that calls Form::beSigned() to try to sign the form), only if their grade is high enough. If the bureaucrat’s grade is too low, the method must throw an exception. 
If it's succesful it should print somethign like `<bureaucrat> signed <form>`.  Otherwise, it will print something like: ` <bureaucrat> couldn’t sign <form> because <reason>`.  

You must also:
* Overload operator<< to print out a form’s state (name, signed or not, grades).
* Update Bureaucrat so it can attempt to sign a form and display a message describing whether the action succeeded or failed and why.

---

## GOALS

1. Exercise class collaboration without a circular hell 🔥 .  
2. More excption usage>   
    * Throwing in constructors when invariants are violated (invalid grades).  
    * Throwing in regular methods (beSigned) when a precondition isn’t met.  
    * Catching exceptions in main() and in Bureaucrat::signForm() to print friendly messages.  

> “How do I make two classes talk to each other safely, using exceptions to enforce rules?”

## WORKFLOW

1. Create Form.cpp and Form.hpp, where you will:  
    * Include all necessary constructor following OCF. 
    * Include getters , exception handling functions and a function beSigned(). 
    ```cpp
    void beSigned(const Bureaucrat& bureaucrat);
    ```
    * Don't forget the overlad for `operator<<`.  


3. In Bureaucrat.hpp/cpp include signing funciont :  

```cpp
    void signForm(Form& form);
```

### Regarding Exception handling
In ex00, we only had `Bureaucrat::GradeTooHighException` and `Bureaucrat::GradeTooLowException`, to  be used when constructing a Bureaucrat with an invalid grade or incrementing/decrementing the grade out of range.  

NOW, we add `FORM`. There are 2 worlds now.   
1. The form’s own rules (sign/execute grade requirements).  
2. The bureaucrat interacting with the form (signing it or failing to).  

To keep things clean. I choose to  handle exceptions with separate functions.
| Exception | Case              | Explanation           | Meesage |
|-----------|-------------------|-----------------------|---------|
| Form::GradeTooHighException | Used when a form is built with a grade requirement < 1 | Invalid form definition: requirement too strict / “too high” in rank. | “Form: grade requirement too high (minimum grade is 1)” |
| Form::GradeTooLowException | Used when a form is built with a grade requirement > 150 | Invalid form definition: requirement too weak / “too low”. | “Form: grade requirement too low (maximum grade is 150)” |
| Form::BureaucratGradeTooLowException | Used when a bureaucrat tries to sign a form but
bureaucrat.getGrade() > form.getGradeToSign()| The bureaucrat doesn't have enough level for this form. | “This bureaucrat's grade is too low to sign the form” |

> A generic validator will no longer be used in ex01 as it was in ex00.