# List of Exercises to fixate OOP core concepts 

## level 0 

### exercise 00
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

### exercise 01
Create a command-line PhoneBook program using C++ classes.
It must be able to store, search, and display up to `8 contacts`, all managed in memory without dynamic allocation.

On launch, the program should wait for the user to type one of the following commands:  
- ADD → Add a new contact  
- SEARCH → Display a contact list and allow selecting one  
- EXIT → Quit the program    

📌 Requirements  
📇 Program must use two classes: PhoneBook and Contact.  
📇 All contacts must be stored using an array — not dynamic memory allocation (no new, no malloc).  
📇 When a 9th contact is added, the oldest one should be replaced.  
📇 Class members should be private where appropriate.  
📇 Input/output must be managed using std::cin and std::cout.  

📖 Behavior rules  
Each contact must contain:  
📓 First name  
📓 Last name  
📓 Nickname  
📓 Phone number  
📓 Darkest secret  
📍 `(None of these fields can be empty.)`  

🔎 When SEARCH is called:  
- A table displays the index, first name, last name, and nickname of all saved contacts.  
- Each column must be exactly 10 characters wide.  
- If the text is longer than 10, truncate and replace the last character with a dot ..  
- All columns must be right-aligned.  
- After the table, the user is prompted to input an index.  
- If the input is valid, display the full contact information.  
- If not, show an appropriate error or fallback behavior.  
- After executing any command (except EXIT), the program must wait for another command.  

🧠 Guiding questions  
- How are you going to organize your file structure? (you need *.hpp and *.cpp)
- How can you format columns to a fixed width using stream manipulators?  
- What kind of validation should you do on user input?  
- What are the benefits of using classes here?  
- Why does the contact list have a fixed size?  
- How can you track which contact to overwrite next?  

<details>
<summary>Click to expand information about file structure </summary>

```cpp
- Header = Think of the header file like a contract or blueprint — it tells the compiler:  
"Here’s the structure of this class, what it can do, and how it can be used."  

💡 Following best practice guideline where I study, No function implementation will be add in the header file. 

- cpp file = the cpp file is the actual construction — how you build it, fulfill that contract, and make it work.  

Contact.hpp  
- Class declaration  
- Private attributes: first name, last name, nickname, etc.  
- Public setters and getters  

Contact.cpp   
- Implementation of Contact methods (e.g., setFirstName(), displayInfo())  

PhoneBook.hpp  
- Class declaration
- Array of 8 Contact objects
- Index tracking  

PhoneBook.cpp  
- Implementation of PhoneBook methods  
- addContact()  
- displayTable()  
- searchContact()  

main.cpp
- Command loop (ADD, SEARCH, EXIT)
- Handles user input and calls methods on a PhoneBook instance

Makefile
- Compiles all .cpp files
- Links into a PhoneBook executable
- Includes all, clean, fclean, re rules
```
</details>


<details>
<summary>Click to expand information class declaration </summary>

```cpp
class Contact
{
private:					//ACTUAL DATA MEMBERS — 
    std::string firstName;	//the variables holding the contact's info.
    std::string lastName;

public:
    Contact();				// 👈 This is the default constructor
							//Without this constructor declared publicly, you wouldn't be able 
							// to create a Contact object like that.
    void setFirstName(const std::string &value);
    void setLastName(const std::string &value);
	/*These are setter functions. You use them to assign a value to the private attributes from outside the class.*/

    std::string getFirstName() const;
    std::string getLastName() const;
	/*These are getter functions. They return the value of the private variable, without letting you change it directly.*/

    void displayFullInfo() const;		//prints all the information of the contact.
};
```

* the `const` at the end of getters means “This function doesn’t change anything in the object.”
(Just reads data — it’s safe.)
</details>


Would you like me to:

Add input validation (e.g. prevent empty fields)?

Add comments to explain each part of the code?

Help you write a tester for this program?