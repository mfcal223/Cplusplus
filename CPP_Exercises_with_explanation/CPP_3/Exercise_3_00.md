# CPP Module 3 - Exercise 00 - ClapTrap Basics

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


