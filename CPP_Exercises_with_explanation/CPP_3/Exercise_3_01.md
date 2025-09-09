# CPP Module 3 - Exercise 00 - ScavTrap

## TASK


## INHERITANCE

### Access Specifiers private vs protected
- To allow inheritance, ClapTrap{} will need some modifications.   
- Consider how its header should be change after reading this:  

`private`: the attributes are accessible only inside the class itself.  
→ Neither other classes nor derived classes can access these members directly.
Example:
```cpp
class Base {
private:
    int a;
};
class Derived : public Base {
    void foo() { a = 1; } // ❌ error: 'a' is private in 'Base'
};
```

`protected`: accessible inside the class and its derived classes.  
→ External code can’t touch it, but subclasses can.
Example:
```cpp
class Base {
protected:
    int a;
};
class Derived : public Base {
    void foo() { a = 1; } // ✅ works
};
```

<details> <summary> HINT </summary>
If you keep ClapTrap’s attributes private, **ScavTrap** won’t be able to set `_hitPoints = 100;` directly. Instead, you’d need getters/setters in ClapTrap (e.g., setHitPoints(int)), or you’d have to initialize via the ClapTrap constructor only.

Those attributes need a change in the access specifier so ScavTrap can modify them.
</details>

### Public inheritance
This means the sub-class "is-a" child of the original one. 

```yaml
class Orange : public Fruit 
```
This means *"Orannge is a Fruit"*.

That gives Orange all the attributes and behavious of Fruit so it is NOT necessary to re-declare them.
Afterwards, you can extend or override some parts:
- Override `attack()` with different behavious
- Add new behaviour (p.e. guardGate())
- Change messages in the constructors.
It is possible to add new private attributes too (which is not part of this exercise).

### Constructor/Destructor chaining

When you create a ScavTrap, C++ first builds its base class (ClapTrap), then the derived class (ScavTrap).  
On the terminal, there should be a print similar to this:  
```bash
ClapTrap constructor message
ScavTrap constructor message
```

When the object goes out of scope (or is deleted), destruction happens in reverse order --> First the derived part (ScavTrap), then the base (ClapTrap).  
```bash
ScavTrap destructor message
ClapTrap destructor message
```

`This order guarantees safety:`
- **Construction**: The base must exist before the derived part (because the derived might depend on base members). `Constructors run base → derived`
- **Destruction**: The derived must vanish first (so it can still use the base safely), then the base is destroyed last. No dependency issues. `Destructors run derived → base`