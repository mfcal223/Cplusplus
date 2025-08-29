// Example.cpp
#include "Example.hpp"
#include <iostream>

// Default ctor: put object in a valid state
Example::Example() : num(0), name("")
{
    std::cout << "Default constructor\n";
}

// Copy ctor: build *new* object as a copy of ex
Example::Example(const Example& ex) : num(ex.num), name(ex.name)
{
    std::cout << "Copy constructor\n";
}

// Copy assignment: overwrite an *existing* object from ex
Example& Example::operator=(const Example& ex)
{
    std::cout << "Copy assignment operator\n";
    if (this != &ex) {
        this->num = ex.num;
        this->name = ex.name;
    }
    return *this;
}

Example::~Example()
{
    std::cout << "Destructor\n";
}

// Simple accessors
void Example::setNum(int n)
{ 
    num = n; 
}

void Example::setName(const std::string& s) 
{ 
    name = s; 
}

int Example::getNum() const 
{ 
    return num; 
}

const std::string& Example::getName() const 
{ 
    return name; 
}