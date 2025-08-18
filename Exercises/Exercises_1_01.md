# Exercise Level 01 - Nr 00 - Zombie Army

## Goals:
- create an army of zombies by including this function  
`Zombie* zombieHorde( int N, std::string name );`    
- it must allocate N zombie objects in a single alocation.   
- when initializing them, they must receive a name.   
- function returns the pointer to the 1st zombie.  
- each zombie should call announce()  
- delete each zombie to avoid memory leaks.  

**Files to turn in :** Makefile, main.cpp, Zombie.hpp, Zombie.cpp,
zombieHorde.cpp  

## Plan:

1. Re-use Zombie.hpp + Zombie.cpp from ex00 with some changes to match goals.  
- Zombie.hpp needs to include a setter function for the name of each zombie in the Zombie-army.    

2. Create ZombieHorde.cpp  
- this source file will include the zombieHorde() that will:  
  - create the array   
  - Use a loop to call the setter to name each new zombie.  
- See next section regarding `std::ostringstream`  

---

## std::ostringstream

`std::ostringstream` comes from <sstream>. It is a **string-builder stream**.   

> ostringstream = stream text into a string instead of to the console.  
> basename+"_"+number_i => if i = 2 =>  basename_2  

It’s like *std::cout*, but instead of printing to the screen, it writes into a string buffer. Later, you can extract the resulting string with `.str()`.   

```cpp
Zombie *horde = new Zombie[N]; // allocate N zombies
for (i = 0; i < N; i++)
{
    std::ostringstream oss;
    oss << baseName << "_" << i;
    horde[i].setName(oss.str()); // set unique name
}
```

* Line 1:  
new Zombie[N] allocates an array of N zombies (all default-constructed at this point).  
* Line 2–3:  
Inside the loop, we create a fresh ostringstream object **oss**.  
* Line 4:  
`oss << baseName << "_" << i;  `
works just like with *std::cout*: it “streams” the pieces into oss.  
- For i = 0, this builds the string:  `"HordeGuy_0"`  
* Line 5:  
**oss.str()** gets the final string from the stream.  
We call **horde[i].setName(...)** with that value, so the i-th zombie’s name becomes "HordeGuy_0", then "HordeGuy_1", etc.  


3. Create main.cpp
- receives the terminal input that includes the amount of zombies the array will have. Checks for errors in such input (amount of arguments).  
- Transforms char** into int. checks that ii is a (+) int.  
- Calls zombieHorde to create the array, passing amount of zombies and the basename as argument.  
- calls class member announce() for each zombie.  
- calls delete[] to delete (free) each zombie in the array, avoinding memory leaks. Check section "Array destruction" 

## **Array Destruction**

```cpp
Zombie* horde = new Zombie[N];
delete[] horde;
```

In this part of the code, `new Zombie[N]` calls the default constructor N times, from index 0 up to N-1.  
`delete[] horde` calls the destructor N times, but in reverse order: from N-1 down to 0.  

```
HordeGuy_0: BraiiiiiiinnnzzzZ...
HordeGuy_1: BraiiiiiiinnnzzzZ...
HordeGuy_2: BraiiiiiiinnnzzzZ...
HordeGuy_2 is destroyed
HordeGuy_1 is destroyed
HordeGuy_0 is destroyed
```
### **Why reverse order?**  
When you construct an array (or any sequence of objects), element 0 is built first, then 1, …, then N-1.  
To avoid problems with **dependencies** between objects, C++ ensures that destruction happens in the exact opposite order.  
