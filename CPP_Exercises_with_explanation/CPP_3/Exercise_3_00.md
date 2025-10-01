# CPP Module 3 - Exercise 00 - ClapTrap Basics

- [CPP Module 3 - Exercise 00 - ClapTrap Basics](#cpp-module-3---exercise-00---claptrap-basics)
  - [TASK](#task)
  - [Header file](#header-file)
  - [CPP file](#cpp-file)
    - [Constructors](#constructors)
    - [attack()](#attack)
    - [takeDamage()](#takedamage)
    - [beRapaired()](#berapaired)
    - [Other considerations](#other-considerations)
  - [Evaluation TIPS](#evaluation-tips)

---

## TASK
Create a class called ClapTrap.  
1. It should model a simple robot with health, energy, and attack power.  

2. *Private attributes*:
- std::string name → provided when creating the object.
- int hit_points → starts at 10.
- int energy_points → starts at 10.
- int attack_damage → starts at 0.  

3. *Public interface*:
- Constructor (takes a name as argument) and destructor.
- void attack(const std::string& target);
- void takeDamage(unsigned int amount);
- void beRepaired(unsigned int amount);

4. *Behavior rules*:
- Attack: prints a message, consumes 1 energy point, and causes the target to lose hit points (damage = attack_damage).
- Repair: prints a message, consumes 1 energy point, and restores hit points.
- Limits: no action can be performed if hit_points == 0 or energy_points == 0.

6. *Interaction rule:*
- ClapTrap instances should not interact directly with one another.
- The parameters will not refer to another instance of ClapTrap.

> Translation: When you call attack("target"), target is just a string — not another ClapTrap object.  
You are not supposed to implement combat logic between two ClapTrap objects (e.g., clap1.attack(clap2); clap2.takeDamage(...)).
Instead, you simulate the action by printing messages and updating the calling ClapTrap’s own energy/hit points.

7. *Additional requirements*:
- Each constructor and destructor must also print a message, so it’s easy to see when objects are created or destroyed.
- You must write your own main.cpp with tests to validate all these behaviors.

---

## Header file
- Remember the class declaration needs to be in Orthodoxal Canonical Form (OCF).
- Make the name constructor `explicit`: avoid accidental implicit conversions from std::string (and from string literals via temporary std::string).

**Check** : [6_Constructors](CPP_Theory/6_Constructors.md)

## CPP file

### Constructors
* Prefer initializer lists over assigning inside the body.  
* Initialize hit points = 10, energy points = 10, attack damage = 0.  
* Prints a short “constructed” message (subject asks messages for lifecycle + actions).  

### attack()
* Simulate an attack: cost 1 EP, report <attack damage> to <target>.  
* Remember conditions: if HP == 0 or EP == 0, do nothing except print a “cannot act” message (subject rule).  
* Update variables on success: EP decreases by 1, print a clear message.  
* Keep in mind that there is *No real object-to-object interaction in ex00*: target is just text, not another ClapTrap.
* Print resulting HP/EP after action to make tests crystal-clear.

### takeDamage()
* Reduce this ClapTrap’s HP by amount (no EP cost).
* If already at 0 HP, print that further damage has no effect (defensive clarity).  
* Clamp HP at 0 (no negative HP).  
* Print a concise message: how much damage taken and the before → after HP. 

### beRapaired()
* Restore amount HP and spend 1 EP.  
* Remember conditions: if HP == 0 or EP == 0, do nothing except print a “cannot act” message (same rule as attack).  
* Update variables on success: EP decreases by 1, HP increases by amount.  
* Print a message: how much was repaired and resulting HP/EP.

### Other considerations
- Consider adding a getter to print the object name.
- Add extra messages if you think it will make output clearer.

---

## Evaluation TIPS
1. Be ready to explain that attack damage is 0 in ex00 by design; later exercises change it.
2. Be ready to explain OCF and the different constructors.
3. Be ready to explain that no cross-instance damage is applied in ex00 (design choice of the module intro).
