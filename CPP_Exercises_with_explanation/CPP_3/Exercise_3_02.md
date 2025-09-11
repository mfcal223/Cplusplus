# CPP Module 3 - Exercise 02 - Repeat

## TASK
Similar to [ex01](/CPP_Exercises_with_explanation/CPP_3/Exercise_3_01.md) but this time yo will create FragTrap class with its own particularities.

1. Deliverables: Everything from earlier exercises plus FragTrap.hpp (or .h) and FragTrap.cpp.
2. Create a class FragTrap that publicly inherits from ClapTrap. It should resemble ScavTrap from the previous exercise, but with different construction/destruction messages and distinct default attributes. Your tests must clearly demonstrate proper constructor chaining (a ClapTrap is built before a FragTrap) and reverse-order destruction.
3. Initialize FragTrap with:
- Name: provided to the constructor.
- Hit points: 100
- Energy points: 100
- Attack damage: 30
4. Add a special action: `void highFivesGuys(void);`  
This member function prints a positive high-five request to standard output.  
5. Expand your tests to cover creation, destruction, and behavior differences.

---

