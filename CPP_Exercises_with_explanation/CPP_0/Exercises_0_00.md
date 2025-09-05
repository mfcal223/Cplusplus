# C++ Module 0 - Exercise 00 - Fixate OOP core concepts 

## TASK
Create a program called megaphone, along with a corresponding Makefile to compile it.  
The program must print the uppercase version of all input arguments received.  
If no arguments are provided, it must instead display a default warning message.  

⚠️ Requirements
- The Makefile must include the rules: all, clean, fclean, and re. It must not relink if no source files changed.  
- End every output with a newline character.
- Use C++98-compatible syntax and standard libraries only.  

💡 Guiding questions  
- What standard C++ headers should be included to access output streams and character manipulation?  
- What built-in functions help convert characters to uppercase? What type do they return?  
- What’s the proper syntax for printing to the standard output?  
- Do we need to explicitly include a newline "\n" or use std::endl? Why does it matter?  

<details>
<summary>Click to expand example</summary>

```cpp
#include <iostream>
#include <cctype>

int main(int ac, char **av)
{
	int	i;
	int j;
	
	if (ac == 1)
		std::cout << "* I forgot what I was trying to say *" << std::endl;
	else
	{
		for (i = 1; i < ac; i++)
		{
			j = 0;
			while (av[i][j])
			{
				std::cout << static_cast<char>(std::toupper(av[i][j]));
				j++;
			}
		}
		std::cout << std::endl;
	}
	return (0);
}
```
</details> 

---

This exercise is quite concise. The key thing is to become familiarized with C++ syntax and the way functions are called.
If you haven't done it, please check the following links. 

Please check the following links:
- [5_Basic Concepts](CPP_Theory/5_Basics.md)
- [6_Constructors](CPP_Theory/6_Constructors.md)
- [7_Bits on Syntax](CPP_Theory/7_Syntax.md)
- [8_Cout & Cast](CPP_Theory/8_Cout_Cast.md)
- [C++ toupper](https://cplusplus.com/reference/cctype/toupper/)

```
.------------------------------------------------------------------------------------------.
| If any link is broken, there is an error, a typo, or any other issue, please let me know.|
'------------------------------------------------------------------------------------------'  
      ^      (\_/)
      '----- (O.o)
             (> <)
```