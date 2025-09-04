# Ad-hoc polymorphism & operator overloading  

Ad-hoc polymorphism in C++ means `overloading`: 
> you provide multiple functions (or operators) with the same name but different parameter types/signatures, and the compiler picks the right one at compile time.

For example:
If you had these 3 functions **in C**
```c
void print(int i);
void print(unsigned int j);
void print(int i, unsigned int j);
```
You would have a problem when trying to compile:  
`main.c:4:6: error: conflicting types for 'print'`

But that would not happen in **C++**.  
Function overloading is authorised in C++ to allow to define two or more function with the same name in the same scope.

You can also overload operators like `=, >=, <=, ==`, just to mentione some of them. 
![Operators](/Exercises_task_&_theory/images/operator_overloading.png)  
(image from [Laura & Simon Gitbook](https://42-cursus.gitbook.io/guide/4-rank-04/cpp-00-04-doing/cpp02))  
  
For more information about operator overloading  : [cppreference.com > operators](https://en.cppreference.com/w/cpp/language/operators.html)


In `CPP_2 / ex00`:
- You see function overloading with constructors: the default constructor and the copy constructor have the same name (Example) but different parameters. That’s ad-hoc polymorphism.  
- You also see operator overloading for operator= (assignment). You’re defining how “=” behaves for your custom type.  

In CPP_2 / ex01, you’ll also overload `operator<<` to stream your Fixed as text (ad-hoc polymorphism on the << operator).  

In CPP_2 / ex02 you’ll overload `comparison (<, >, ==, …) and arithmetic (+, -, *, /)` operators so Fixed “feels” like a number. That’s more ad-hoc polymorphism: the same operator symbol means different code depending on operand types.  