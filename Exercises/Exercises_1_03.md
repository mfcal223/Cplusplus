# Exercise Level 01 - Nr 03 - What is your weapon of choce?

## Goals
- Implement a tiny model of **people** and **weapons** to practice object composition and the difference between holding an object by reference vs by pointer.  
- Class Weapon stores a (private) type string and lets you read (getType()) and change it (setType()).
- Class HumanA always has a weapon: it receives a reference to a Weapon in its constructor and uses it in attack().
- Class HumanB may or may not be armed: it stores a pointer to a Weapon, can be set later with setWeapon(), and uses it in attack() if present.
- No memory leaks.  
- attack() displays "<name> attacks with their <weapon type>".  
  
You need to choose if HumanA and HumanB should "hold" a weapon by pointer or reference.

Here is main() : 

```cpp
int main()
{
    {
        Weapon club = Weapon("crude spiked club");
		HumanA brain("Brain", club);
		brain.attack();
		club.setType("some other type of club");
		brain.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB pinky("Pinky");
		pinky.setWeapon(club);
		pinky.attack();
		club.setType("some other type of club");
		pinky.attack();
	}
	return 0;
}
```

Your implementation should print an attack with "crude spiked club" then a second attack with "some other type of club" for both test cases.  

---
> BEFORE STARTING: In which case do you think it would be best to use a pointer to
Weapon? And a reference to Weapon? 

A reference is a synonym for a variable's name. It is always "existent", never NULL. It cannot be reseated.  
On the contrary, a pointer can be reseated, can be NULL.  

As project's states that HumanA must always be armed, but HumanB may stay unarmed, it follows that references should be used with HumanA, and pointers with HumanB.   

* HumanA (reference): Always armed; weapon must exist at construction and never be null. A reference guarantees that: it must be bound at construction and can’t be reseated or be null.  
* HumanB (pointer): May start unarmed; can optionally receive a weapon later via setWeapon(). A pointer naturally models “maybe has one” (can be NULL), and can be reseated.  

---

## What the expected output demonstrates?

Both test blocks mutate the same Weapon object after an initial attack.
Because HumanA and HumanB both refer to the same weapon instance (A via reference, B via pointer), their second attack() must reflect the updated type.  

So you should see (labels added for clarity; your program prints only the attack lines):  

<details>
<summary> Click to expand terminal output </summary>

```yaml
Bob attacks with their crude spiked club  
Bob attacks with their some other type of club   
Jim is unarmed.   
Jim attacks with their crude spiked club   
Jim attacks with their some other type of club   
```

</details>