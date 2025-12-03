# Module 05 - Exercise 02 – “Abstract Forms & Execution Authority”

## TASK

In this exercise, the concept of a Form is extended. Instead of a simple signable document, a form can now also be executed, but only when:  
- it is already signed, and  
- the Bureaucrat attempting the execution has a high enough grade (i.e., grade <= required execution grade).  

To support multiple kinds of executable forms, the base Form class becomes an `abstract class`, containing:
- its usual attributes (name, signed flag, grade to sign, grade to execute),  
- an abstract method that derived forms must implement,  
- and logic to verify whether execution is allowed.

Each concrete form created in later exercises will implement its own action when executed.

The Bureaucrat class must also be updated so it can attempt to execute forms and report success or failure.

---

## GOAL

This exercise trains three major C++ skills:

### 🎯 1 — Understanding Abstract Classes / Pure Virtual Methods

You convert Form → AForm (name in subject) into an abstract base class:
```cpp
virtual void execute(Bureaucrat const& executor) const = 0;
```

This means:
- You cannot instantiate AForm.  
- All derived forms must implement their own execution behavior.  

> This sets up ex03, where the goal is to create real executable forms like.

### 🎯 2 — Introducing Execution Permissions

Unlike ex01, signing is no longer enough. Execution requires:
- The form is signed,  
- The executor’s grade meets the form’s required execution grade.  

If either fails → throw an exception.  

This teaches to design `multi-stage permissions` using exceptions.  

### 🎯 3 — Overriding Behavior in Derived Classes

Each concrete form will implement a different “action” when executed.  

Example:
```cpp
virtual void execute(Bureaucrat const& executor) const {
    // do something specific to this form  
}
```

This is polymorphism in action.
The base class enforces the interface, and subclasses implement the behavior.

---

## What to do?

1) Rename Form → AForm (The subject requires this name.)  

2) Add the pure virtual method 
```cpp
virtual void execute(Bureaucrat const& executor) const = 0;
```

3) Add a new exception type
```
AForm::FormNotSignedException
```
Used when someone tries to execute a form that has not been signed.  

4) Add `canExecute()` logic in base class  
A base helper that checks:  
- form is signed
- executor has grade <= gradeToExecute

5) Add `executeForm()` in Bureaucrat
This mirrors signForm() from ex01.

---

📘 AForm.hpp — Example (clean, 42-compliant)
#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat;

class AForm {
public:
    // Orthodox Canonical Form
    AForm();
    AForm(const std::string& name, int gradeToSign, int gradeToExecute);
    AForm(const AForm& other);
    AForm& operator=(const AForm& rhs);
    virtual ~AForm();

    // Getters
    const std::string& getName() const;
    bool               isSigned() const;
    int                getGradeToSign() const;
    int                getGradeToExecute() const;

    // Sign
    void beSigned(const Bureaucrat& bureaucrat);

    // Execute interface
    virtual void execute(Bureaucrat const& executor) const = 0;

    // Exceptions
    class GradeTooHighException      : public std::exception { 
    public: const char* what() const throw(); };

    class GradeTooLowException       : public std::exception {
    public: const char* what() const throw(); };

    class BureaucratGradeTooLowException : public std::exception {
    public: const char* what() const throw(); };

    class FormNotSignedException     : public std::exception {
    public: const char* what() const throw(); };

protected:
    void checkExecutable(Bureaucrat const& executor) const;

private:
    const std::string _name;
    bool              _signed;
    const int         _gradeToSign;
    const int         _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif

📗 AForm.cpp — Example logic
#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
: _name("default form"),
  _signed(false),
  _gradeToSign(150),
  _gradeToExecute(150) {}

AForm::AForm(const std::string& name, int gSign, int gExec)
: _name(name), _signed(false),
  _gradeToSign(gSign), _gradeToExecute(gExec) {

    if (gSign < 1 || gExec < 1)
        throw GradeTooHighException();
    if (gSign > 150 || gExec > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
: _name(other._name),
  _signed(other._signed),
  _gradeToSign(other._gradeToSign),
  _gradeToExecute(other._gradeToExecute) {}

AForm& AForm::operator=(const AForm& rhs) {
    if (this != &rhs)
        _signed = rhs._signed;
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const { return _name; }
bool AForm::isSigned() const { return _signed; }
int AForm::getGradeToSign() const { return _gradeToSign; }
int AForm::getGradeToExecute() const { return _gradeToExecute; }

/*----------------------------------------------------*/
// Signing
void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign)
        throw BureaucratGradeTooLowException();
    _signed = true;
}

/*----------------------------------------------------*/
// Execution checks
void AForm::checkExecutable(Bureaucrat const& executor) const {
    if (!_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw BureaucratGradeTooLowException();
}

/*----------------------------------------------------*/
// Exception messages
const char* AForm::GradeTooHighException::what() const throw() {
    return "Form: grade requirement too high (min 1)";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form: grade requirement too low (max 150)";
}

const char* AForm::BureaucratGradeTooLowException::what() const throw() {
    return "This bureaucrat's grade is too low for this form";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Cannot execute form: the form is not signed";
}

📙 What gets added in Bureaucrat
void Bureaucrat::executeForm(AForm const& form) {
    try {
        form.execute(*this);
        std::cout << _name << " executed " << form.getName() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << _name << " couldn’t execute "
                  << form.getName() << " because "
                  << e.what() << std::endl;
    }
}

🎉 Summary

Ex02 introduces 3 major new concepts:

Feature	Description
Abstract class	AForm is now abstract with a pure virtual execute()
Execution rules	Form must be signed AND bureaucrat must have sufficient grade
New exceptions	FormNotSignedException + reuse of previous exceptions
Polymorphism	Each specific form implements its own action in execute()
New Bureaucrat ability	executeForm() method mirroring signForm()