#include <iostream>

class Animal {
public:
    void makeSound1() const { std::cout << "generic sounds from Animals\n"; }
    virtual void makeSound2() const { std::cout << "generic sounds from Animals\n"; }
};

class Dog : public Animal {
public:
    void makeSound1() const { std::cout << "woof woof woof woof woof\n"; }
    void makeSound2() const { std::cout << "woof woof woof woof woof woof \n"; }
};

int main() {
    Animal* a = new Dog();
    std::cout << "Animal* a = new Dog();" << std::endl;
    std::cout << "------------------------------------------------------------- " << std::endl;
    std::cout << "- calling makeSound1() / WITHOUT VIRTUAL" << std::endl;
    a->makeSound1();
    std::cout << "- chooses Animal's function ❌ (base wins, no polymorphism)" << std::endl;
    std::cout << "------------------------------------------------------------- " << std::endl;
    std::cout << "- calling makeSound2() / WITH VIRTUAL" << std::endl;
    a->makeSound2();
    std::cout << "- chooses Dog's function ✅ (derived wins, polymorphism!)" << std::endl;
    delete a;
}

/*
to compile>
c++ polymorphism_example.cpp -o example

to execute>
./example
*/