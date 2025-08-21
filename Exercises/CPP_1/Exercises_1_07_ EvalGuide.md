# 📘  Exercises CPP 1 - Evaluation Guide

## **Exercise 00 – BraiiiiiiinnnzzzZ**

**Description**
Create a `Zombie` class. Zombies have a name and announce themselves with `"BraiiiiiiinnnzzzZ..."`. Two functions:

* `newZombie(name)` → allocates zombie on heap, returns pointer.
* `randomChump(name)` → creates zombie on stack, announces immediately.

**Goals**

* Understand **stack vs heap allocation**.
* Manage object lifetime and destructor calls.
* Practice constructor, destructor, and member function basics.

**Key Questions**

* **Stack vs heap difference?**  
  * *Stack objects are destroyed automatically at end of scope; heap objects survive until manually deleted.*  

* **Why destructor message?**  
  * *To check lifetime and avoid leaks.*  

* **Why does `newZombie` return a pointer?**
  * *Because heap objects can outlive the function scope.*

---

## **Exercise 01 – Moar brainz!**

**Description**
Implement `zombieHorde(N, name)` → creates an array of `N` zombies with unique names and calls `announce()` for each.

**Goals**

* Practice **dynamic allocation of arrays** (`new[]`).
* Use **loops** with objects.
* Use `delete[]` correctly to free all zombies.

**Key Questions**

* **Why `delete[]` instead of `delete`?**  

  * *Because `new[]` constructs multiple objects; `delete[]` ensures destructors are called for all.*  

* **Why do destructors run in reverse order?**

  * *C++ destroys arrays in opposite order of construction to avoid dependency issues.*   

* **How did you give each zombie a unique name?**

  * *Using `std::ostringstream` to append index numbers to the base name.*

---

## **Exercise 02 – HI THIS IS BRAIN**

**Description**
Create a string, then a pointer (`stringPTR`) and a reference (`stringREF`) to it. Print addresses and values.

**Goals**

* Understand **pointers vs references**.
* Show both hold the same underlying address/value differently.

**Key Questions**

* **Pointer vs reference difference?**

  * *Pointer can be reseated or NULL; reference is always bound and cannot be reseated.*  

* **When use a reference instead of a pointer?**
  * *When the object must always exist (cannot be null).*

---

## **Exercise 03 – Unnecessary violence**

**Description**
Implement `Weapon`, `HumanA`, `HumanB`.

* `HumanA`: always armed → holds `Weapon&`.
* `HumanB`: may be unarmed → holds `Weapon*`.

**Goals**

* Practice **composition of classes**.
* Learn when to use **reference vs pointer**.

**Key Questions**

* **Why does HumanA use reference?**

  * *Because it’s always armed: reference guarantees a weapon is always bound.*  
* **Why does HumanB use pointer?**  

  * *Because it can be null → models “maybe armed.”*
* **What happens if weapon type changes after assignment?**  

  * *Both Humans reflect it, because they both reference the same `Weapon` object.*

---

## **Exercise 04 – Sed is for losers**

**Description**  
Program takes 3 args: `filename`, `s1`, `s2`. Creates `<filename>.replace` replacing all `s1` with `s2`.  

**Goals**  

* Learn **file I/O** with `<fstream>`.  
* Practice **string find/replace manually** (since `std::string::replace` is forbidden).   
* Handle **input validation** and errors.  

**Key Questions**

* **Why not use `std::string::replace`?**  

  * *Forbidden by subject: we must practice manual string building.*  
* **How do you open files in C++?**  

  * *Use `std::ifstream` for input, `std::ofstream` for output.*  
* **What is `c_str()` used for?**  

  * *Converts `std::string` to C-style string (`const char*`) needed by stream constructors.*  

---

## **Exercise 05 – Harl 2.0**

**Description**  
Create class `Harl` with private methods `debug()`, `info()`, `warning()`, `error()`.  
Public `complain(level)` dispatches to the correct method using **pointers to member functions** (no big if/else chain).  

**Goals**

* Learn **pointers to member functions**.  
* Practice **dispatch tables** (string → function).  

**Key Questions**  

* **Why not use if/else?**  

  * *Exercise explicitly forbids it; we must show we can use function pointers.*  
* **How do you call a pointer to member function?**  

  * \*(this->*funcs\[i])();*  
* **Why typedef Action = void (Harl::\*)()?**  

  * *To simplify declaration and ensure all functions share the same signature.*  

---


