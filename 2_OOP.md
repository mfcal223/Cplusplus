# Object Oriented Programming in C++

Object Oriented Programming (OOP) is a programming paradigm where you organize your code around objects rather than just functions and data.  

- In C (procedural): You write functions that manipulate data structures.
- In C++ (OOP): You group data and the functions that operate on that data together in a single unit called a class. You then create objects (instances) from those classes.

The main goal of OOP is to group data and the functions that work on it together, so that the data is protected and can only be changed in controlled ways.

The big goals are:
1) Encapsulation → Grouping related data and behavior
2) Abstraction → Hiding unnecessary complexity
3) Inheritance → Reusing and extending code
4) Polymorphism → Using one interface for multiple behaviors

Let's use an analogy to emphasise the differences.

*Imagine you are building a house*.

- **Procedural (C) Approach**

C is like having instructions to build anything but keeping all the materials and tools in one giant warehouse.

You have separate blueprints for every aspect:
- buildWalls()
- paintHouse()
- installWindows()

The data (wall thickness, paint color, number of windows) is stored in structs, and you pass them to every function.  
You must manually make sure every function uses the right struct and updates it correctly.  

✅ Good for small projects, but as the house grows more complex, managing all the functions and data separately becomes messy.  

📌  Functions are the stars, data is passed around.

- **Object-Oriented (C++) Approach**

C++ (OOP) is like having prefabricated kits (classes) where each kit (object) has its own tools and materials, making construction faster and more organized.

You create a *House class*.
The House has:
- Data (attributes): color, numRooms, numWindows
- Functions (methods): build(), paint(), addWindow()

You can create multiple house objects:
```cpp
House villa("red", 5);
House apartment("white", 2);
```

Each house manages its own data.
You don’t need to pass the house’s details to every function—the object knows its own properties.

✅ Perfect for big projects, because the data and functions are tied together, making it easier to maintain and extend.  

📌  Objects are the stars, data and functions live together.

## Objects
An object is a real, usable instance of a class that has specific properties and behaviors. In C++, an object is created from a class.  
When you define a class, no memory is used. But when you create an object from that class, memory is allocated for it and that has an associated address.   


https://www.geeksforgeeks.org/cpp/object-oriented-programming-in-cpp/  

---

## Classes

Classes are an expanded concept of data structures except that they can include not only data but also include functions and have these new things called `access specifiers`.  
