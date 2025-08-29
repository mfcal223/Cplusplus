#include "Example.hpp"
#include <iostream>

int main()
{
    std::cout << "-----Create a & b ------" << std::endl;
    Example a;          // Default constructor
    Example b;          // Default constructor

    std::cout << "-----Set a------" << std::endl;
    a.setNum(10);
    a.setName("Simon");
    std::cout << a.getName() << " " << a.getNum() << std::endl;

    std::cout << "-----Set b------" << std::endl;
    b.setNum(22);
    b.setName("Ana");
    std::cout << b.getName() << " " << b.getNum() << std::endl;

    std::cout << "----Assign {b} to be like {a} (b = a) -----" << std::endl;
    b = a;              // *** Copy assignment operator ***
    std::cout << "-- Get a ------" << std::endl;
    std::cout << a.getName() << " " << a.getNum() << std::endl;
    std::cout << "-- Get b (now = to a) ------" << std::endl;
    std::cout << b.getName() << " " << b.getNum() << std::endl;

    std::cout << "-----New object {c} created as a copy of {a} [c(a)] ----" << std::endl;
    Example c(a);       // *** Copy constructor ***

    std::cout << "----- Final result: Get a / b / c ------" << std::endl;
    std::cout << "-- Get a ------" << std::endl;
    std::cout << a.getName() << " " << a.getNum() << std::endl;
    std::cout << "-- Get b ------" << std::endl;
    std::cout << b.getName() << " " << b.getNum() << std::endl;
    std::cout << "-- Get c ------" << std::endl;
    std::cout << c.getName() << " " << c.getNum() << std::endl;

    std::cout << "----- End of Function - Variables go out of scope ------" << std::endl;
}

// TO COMPILE: c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o example