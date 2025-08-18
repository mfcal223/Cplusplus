# Access Specifiers

An `access specifier` is one of the following three keywords: `private, public` or `protected`.  

These specifiers modify the access rights for the members that follow them.

## PRIVATE
- PRIVATE members of a class are accessible only from within other members of the same class (or from their "friends").  
  - They are not allowed to be accessed directly by any object or function outside the class.  
  
```cpp
#include<iostream>
using namespace std;

class Circle {  
    
// private members
private: 
    double radius;
    double  compute_area() {

        // member function can access private 
        // data member radius
        return 3.14*radius*radius;
    }
    
};

int main() {
    Circle obj;
    
    // trying to access private data member
    // directly outside the class
    obj.radius = 1.5;
    cout << "Area is:" << obj.compute_area();
    
    return 0;
}
```

Output:
```
main.cpp: In function ‘int main()’:
main.cpp:22:9: error: ‘double Circle::radius’ is private within this context
   22 |     obj.radius = 1.5;
      |         ^~~~~~
main.cpp:7:16: note: declared private here
    7 |         double radius;
      |                ^~~~~~
main.cpp:23:43: error: ‘double Circle::compute_area()’ is private within this context
   23 |     cout << "Area is:" << obj.compute_area();
      |                           ~~~~~~~~~~~~~~~~^~
main.cpp:8:17: note: declared private here
    8 |         double  compute_area() 
```

## PROTECTED
- PROTECTED members are accessible from other members of the same class (or from their "friends"), but also from members of their derived classes.  
- This access through inheritance can alter the access modifier of the elements of base class in derived class depending on the mode of Inheritance.

## PUBLIC
- PUBLIC members are accessible from anywhere where the object is visible. 
  - Public members of a class in C++ can be accessed from anywhere in the program. This means that both other classes and functions can directly use the data members and member functions marked as public. 
  - To access them, the dot (.) operator is used along with the object of the class

```cpp
#include<iostream>
using namespace std;

// Class definition
class Circle {
public: 
    double radius;
    double  compute_area() {
        return 3.14*radius*radius;
    }
    
};

int main() {
    Circle obj;
    
    // Accessing public members outside class
    obj.radius = 5.5;
    cout << "Radius is: " << obj.radius << "\n";
    cout << "Area is: " << obj.compute_area();
    
    return 0;
}
```

Output:
```yaml
Radius is: 5.5
Area is: 94.985
```

> Data member "radius" is declared as public so it could be accessed outside the class and thus was allowed access from inside main().

***By default, all members of a class declared with the class keyword have private access for all its members. Therefore, any member that is declared before any other access specifier has private access automatically.***

> unless you specify the public or protected AS, the members will be assume as private.

🔑 *How to Remember It*
Think of a castle analogy:
- private → Inside the castle’s secret vault (only the king/queen has access).
- protected → Inside the castle’s training grounds (only royal family + knights—i.e., derived classes—can access).
- public → In the open village (anyone can walk in).

---

## How to Access Private Members? Getters and Setters

Private variables are hidden to protect them from unintended changes.
Sometimes, you need to read or update these values from outside the class.

Instead of making the variable public (which breaks encapsulation), you create public functions that:

Getter → Returns the value of the private variable.

Setter → Updates the private variable (possibly with validation).

```cpp
#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance; // private for protection

public:
    BankAccount(double initial) : balance(initial) {}

    // Getter: lets you read balance
    double getBalance() const {
        return balance;
    }

    // Setter: lets you update balance (with rules)
    void setBalance(double newBalance) {
        if (newBalance >= 0) // simple validation
            balance = newBalance;
        else
            cout << "Invalid balance!" << endl;
    }
};

int main() {
    BankAccount account(100);

    // Access through getter
    cout << "Initial balance: " << account.getBalance() << endl;

    // Update through setter
    account.setBalance(200);
    cout << "Updated balance: " << account.getBalance() << endl;

    // Try invalid value
    account.setBalance(-50); // Will be rejected
}
```

Output
```yaml
Initial balance: 100
Updated balance: 200
Invalid balance!
```

> If balance were public:

```cpp
account.balance = -9999; // No protection
```
That could corrupt the state of the object.
By using a setter, you control what changes are allowed.

---
https://cplusplus.com/doc/tutorial/classes/  

https://www.geeksforgeeks.org/cpp/access-modifiers-in-c/

---

