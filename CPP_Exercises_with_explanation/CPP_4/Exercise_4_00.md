# C++ Module 4 - ex00 - Polimorphism - Likes Cats & Dogs

## TASK
Introduce runtime polymorphism by working with a base class and derived classes that redefine behavior.  

### Requirements
1. Create a base class Animal.
- It must contain one protected attribute:
```cpp
std::string type (default can be empty or any value you choose).
```
2. Create two derived classes:
- Dog
- Cat
- Each must initialize their type attribute with the class name (i.e., "Dog" for Dog, "Cat" for Cat).
3. All classes must implement the method:
```cpp
void makeSound() const;
```
- Each class should output the sound appropriate to that animal (e.g., cats meow, dogs bark).
- The correct specific sounds of Dog and Cat must be printed (not just the base Animal sound).
4. Provide a member function getType() to retrieve the type string.
5. Constructors and destructors of every class must print a distinct message so it’s clear which constructor/destructor is being executed.

6. Files to submit: Makefile, main.cpp, all .hpp/.h and .cpp files.

7. EXTRA --> Additional task (WrongAnimal/WrongCat):
- Implement a base class WrongAnimal and a derived class WrongCat.
- Replace Animal/Cat in the sample test with WrongAnimal/WrongCat.
- In this version, calling makeSound() on a WrongCat through a pointer to WrongAnimal will not produce the cat sound, but rather the WrongAnimal sound.  


> Teaching Trick! This is meant to demonstrate what happens if the base class method is not declared virtual.  


<details><summary> Click here for explanation of this trick </summary>

In `Animal`, `makeSound()` must be declared as *virtual*, so the correct function is chosen at runtime.  
In `WrongAnimal`, makeSound() is **not** *virtual*.  

This means if you do:
```cpp
const WrongAnimal* w = new WrongCat();
w->makeSound(); 
```
You’ll get the WrongAnimal sound, not the WrongCat sound.  
So the "Wrong" versions exist only to show what happens if you forget to use virtual in your base class.
</details>  


<details><summary> Suggested main()</summary>

```cpp
int main() {
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    i->makeSound(); // should produce the cat sound
    j->makeSound(); // should produce the dog sound
    meta->makeSound(); // should produce the generic animal sound

    delete meta;
    delete j;
    delete i;
    return 0;
}
```
</details>

---

## Runtime Polymorphism

In module 2, we work on `Compile-time polymorphism`, where the compiler decides which function to call, before running the program.

In contrast, there is `Runtime Polymorphism` where the function that actually runs is chosen while the program is running, depending on the real object type, not just the pointer type.

Let's work with an example:  

```cpp
Animal* a = new Dog();  //polymorphism at runtime (base pointer → derived object),
a->makeSound();
```

- There are 2 classes: Animal & Dog. 
- It exist `virtual Animal::makeSound()` and `Dog::makeSound()`.   
- Even though a is of type Animal*, the program will run **Dog’s implementation** of makeSound() because of `virtual dispatch`.  

```cpp
class Animal {
public:
    void makeSound1() const { std::cout << "generic sounds type 1\n"; }
    virtual void makeSound2() const { std::cout << "generic sounds type 2\n"; }
};

class Dog : public Animal {
public:
    void makeSound1() const { std::cout << "woof\n"; }
    void makeSound2() const { std::cout << "woof woof\n"; }

};

int main() {
    Animal* a = new Dog();
    a->makeSound1();    // prints "generic sound" ❌ (base wins, no polymorphism)
    a->makeSound2();    // prints "woof woof" ✅ (derived wins, polymorphism!)

    delete a;
}
```
---

### Why is "virtual" important?

`Without virtual`, the compiler will look at the type of the pointer and decide which function to call.  
`With virtual`, the compiler generates a mechanism (a “vtable”) that makes the decision at runtime depending on the actual object behind the pointer.

```yaml
Animal* a = new Dog();

WITHOUT virtual:            WITH virtual:
 ------------------          ------------------
 [ Animal* ]                [ Animal* ]
      |                           |
      v                           v
   Animal part of Dog         Dog object
   (static binding)           (dynamic binding)
   --> Animal::makeSound      --> Dog::makeSound

```

Here is a bit more detailed code of the same [EXAMPLE](/Cplusplus/CPP_Exercises_with_explanation/CPP_4/polymorphism_example.cpp) as above and you will obtain an output that should look like this:  

![Polymorphism example Output](/images/cpp4_polymorphism.png)

---

### Object creation and Polymorphism

In previous modules, the exercise always created object like this `Dog d`. This creates a Dog directly: stack, exact type known, no polymorphism.  

Another key difference in this module, is the change to this other way: `Animal* a = new Dog();`.  This creates a Dog on the heap but seen through an Animal pointer (base-to-derived relation). This setup is what allows virtual functions to dispatch dynamically (true polymorphism).

|			Dog d;				|			Animal* a = new Dog();				|
|-------------------------------|-----------------------------------------------|
| Stack allocation. 			| Heap allocation. Keeps pointer "a" to Dog.	|
| Automatically destroyed		|	Must be manually released with delete a;	|
|Variable type is Dog. The compiler knows it is a Dog from the start. | Variable type is Animal* (pointer to base). The real object is a Dog, but the compiler only knows it’s “some kind of Animal.” |
| Calling d.makeSound(); always calls Dog::makeSound().	| makeSound() function that is called wil vary depending if Animal's is virtual or not. |
| No polymorphism involved.		| Runtime polymorphism	|


