# SERIALIZATION

Let's build a mental monderl to understand the concept of Serialization.  

Imagine you have an object:  

```cpp
Data d;
```

This object lives in RAM at some memory address. It only exists while the program is running.  

If  you want to save this object (pointer) to a file, or send it over the network/other process you cannot sent the pointer `0x7ffeefbff5a0`.
The pointer only makes sense inside its current process, while the program is running. That memory address means nothing elsewhere.

To achieve that is why you need to use serialization.

`Serialization = converting an object into a format that can be stored or transmitted and later reconstructed.`

```yaml
Object in memory
	↓
sequence of bytes (numbers)
	↓
file / network / buffer
	↓
bytes
	↓
object in memory
```

If I were to explain it with an analogy, think of an `object` like a **house** 🏠.  
The house exists at a physical **address**. That address only makes sense in that **city**.  

If I want to describe the house 🏠 to someone else, I don’t send: *“Go to GPS coordinates X and look.”*

Instead, I send:
* number of rooms
* size
* color
* year built

***That description is the serialized form.***

> 📦 Serialization is describing the object, not pointing to it.

If you have this data structure:
```c++
struct Data {
    int id;
    double value;
};
```
In memory this is `[ id ][ value ]`.  
Via serialization you could take those bytes, send them somewhere (file, buffer, network), then they would be rebuild in a new Data object with the same values. 
A new object is created, with a different memory address but SAME CONTENT.

