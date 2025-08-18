
"Exercise : 03
Unnecessary violence
Turn-in directory : ex03/
Files to turn in : Makefile, main.cpp, Weapon.{h, hpp}, Weapon.cpp, HumanA.{h,
hpp}, HumanA.cpp, HumanB.{h, hpp}, HumanB.cpp
Forbidden functions : None
Implement a Weapon class that has:
• A private attribute type, which is a string.
• A getType() member function that returns a const reference to type.
• A setType() member function that sets type using the new one passed as param-
eter.
Now, create two classes: HumanA and HumanB. They both have a Weapon and a
name. They also have a member function attack() that displays (of course, without the angle brackets):
<name> attacks with their <weapon type>
HumanA and HumanB are almost the same except for these two tiny details:
• While HumanA takes the Weapon in its constructor, HumanB doesn’t.
• HumanB may not always have a Weapon, whereas HumanA will always be armed.

If your implementation is correct, executing the following code will print an attack with "crude spiked club" then a second attack with "some other type of club" for both test cases:

```cpp
int main()
{
    {
        Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return 0;
}
```

Don’t forget to check for memory leaks.

Question: In which case do you think it would be best to use a pointer to
Weapon? And a reference to Weapon? Why? Think about it before
starting this exercise."