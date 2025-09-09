# CPP Module 3 - Exercise 01 - ScavTrap

## TASK
Extend your previous work on ClapTrap by creating a new robot through `inheritance`. 

The new class will be called ScavTrap. It must be derived from ClapTrap and will therefore inherit its constructors and destructor. However, the messages printed by the constructors, destructor, and the attack() method must be different from ClapTrap’s, showing that every ClapTrap has its own personality.  

#### What needs to be implemented
A ScavTrap class:
- Inherits from ClapTrap.
- Must re-define the constructors, destructor, and attack() with their own output messages.
- Proper constructor/destructor chaining must be visible in the tests:
* When you create a ScavTrap, first the ClapTrap part is built, then the ScavTrap part.
* When the object is destroyed, the reverse order happens (ScavTrap first, then ClapTrap).
- Make sure your test program clearly shows this order.

> You must provide all the files from the previous exercise, plus ScavTrap.hpp + 
ScavTrap.cpp

#### ⚙️ Initialization values

When a ScavTrap is created, it should set its attributes (inherited from ClapTrap) to:  
1. Name → given as a parameter to the constructor.
2. Hit points → 100
3. Energy points → 50
4. Attack damage → 20

#### ⭐ Special ability

ScavTrap has one unique member function:   
```cpp
void guardGate();
```
This function should display a message saying that the ScavTrap has entered Gate Keeper mode.

---

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

---

🔑 Evaluation Key Concepts – CPP03/ex01 (ScavTrap)
1. Inheritance basics
Q: How does ScavTrap relate to ClapTrap?
A: ScavTrap inherits from ClapTrap using public inheritance. This means a ScavTrap is-a ClapTrap and reuses its attributes and methods.

Q: Why use inheritance instead of copying code?
A: Inheritance avoids duplication, keeps base logic centralized, and allows extension/overriding of behavior.

2. Access specifiers (private vs protected)
Q: Why make _hitPoints, _energyPoints, _attackDamage, and _name protected?
A: protected lets derived classes like ScavTrap directly access and modify them. If they were private, we’d need setters/getters in ClapTrap.

3. Constructor/Destructor chaining
Q: What is constructor chaining?
A: When creating a derived object, the base class constructor runs first, then the derived constructor.

Q: And destructor chaining?
A: Destruction is in reverse: derived destructor runs first, then base destructor. This prevents using destroyed parts.

4. Overriding attack

Q: How is ScavTrap::attack different from ClapTrap::attack?
A: It prints a different message, but the logic is the same: consumes 1 energy point and only works if HP > 0 and EP > 0.

Q: Why keep the same function signature?
A: To override the base version properly and allow polymorphism if needed later.