# C++ Module 0 - Exercise 01 - Using old tech to learn C++


## TASK
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

---

🧠 Guiding questions  
- How are you going to organize your file structure? (you need *.hpp and *.cpp)
- How can you format columns to a fixed width using stream manipulators?  
- What kind of validation should you do on user input?  
- What are the benefits of using classes here?  
- Why does the contact list have a fixed size?  
- How can you track which contact to overwrite next?  

---

## First step
Try thinking about what files you need to create and what will be included in each of them.  
This is how I organized them:  

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

---

## Header file

As this is one of the first exercises, I think a bit extra help with the examples is needed, here is a rough sample of the `Contact.hpp`  

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

---

## Phonebook files

### the flow inside addContact()

Right now you have something like:

```cpp

void PhoneBook::addContact() {
    Contact c;              // 1. Local temporary Contact created
    // ... set all its fields ...
    contacts[nextIndex] = c; // 2. Assign temp to the array slot
    // ...
} // 3. Local temp `c` goes out of scope here
```

This creates a local variable `c` inside the function.
It’s a full-fledged Contact object that lives on the stack.

`contacts` is an array of already existing Contact objects.  
Doing *contacts[nextIndex] = c;* does not create a new Contact in that slot. Instead, it calls the `copy assignment operator` to copy the contents of c into the already existing Contact in the array.

> Key point: The Contact in contacts[nextIndex] is not destroyed or replaced — it’s updated.

When the function finishes, the local Contact c goes out of scope. Its destructor is called automatically.  

That’s the "Contact destroyed" message you see immediately after Contact saved.

---

### Private members in PhoneBook.hpp  
```cpp
Contact contacts[8];
int contactCount;
int nextIndex;
```

contacts[8] → The fixed-size array holding the 8 Contact objects (already exist when a PhoneBook is created).  

contactCount → Keeps track of how many contacts are currently stored (so we know how many are valid).   

nextIndex → Keeps track of which slot to overwrite next when adding a contact.    
	- Starts at 0.    
	- Increments each time we ADD.  
	- Wraps around to 0 after reaching 7 (using modulo % 8).  


2. Constructor initialization  
```cpp
PhoneBook::PhoneBook() : contactCount(0), nextIndex(0) {}  
: contactCount(0), nextIndex(0) is called a member initializer list. 
```

This sets both integers to 0 before the constructor body executes.  

Equivalent to:  

```cpp
PhoneBook::PhoneBook() {
    contactCount = 0;
    nextIndex = 0;
}
```
but the initializer list is considered better style for basic types.   

No body logic is needed here, so the braces are empty.  

---

## addContact() step-by-step

```cpp
void PhoneBook::addContact()
{
    Contact c;
```

Creates a local Contact object called c.  
This c will be filled with user-provided data and then stored in the contacts[] array.  

```cpp
    c.setFirstName(getNonEmptyInput("Enter first name: "));
    c.setLastName(getNonEmptyInput("Enter last name: "));
    c.setNickname(getNonEmptyInput("Enter nickname: "));
    //(...)
    c.setDarkestSecret(getNonEmptyInput("Enter darkest secret: "));

```
Calls our private helper function `getNonEmptyInput()` for each string field.  
`getNonEmptyInput()` ensures the input is not empty before returning it.

```cpp
    c.setPhoneNumber(getPhoneNumberInput("Enter phone number: "));
``` 
Uses another helper, `getPhoneNumberInput()`, which ensures:
- Input is not empty  
- Every character is a digit  

Then it stores the new contact in the array at nextIndex.
```cpp
    contacts[nextIndex] = c;
    nextIndex = (nextIndex + 1) % 8;
```
`(nextIndex + 1) % 8` ensures the index wraps around after reaching the last slot (circular buffer).

```cpp
    if (contactCount < 8)
        contactCount++;
```
Only increases contactCount until it reaches the maximum (8).

```cpp
    std::cout << "Contact saved." << std::endl;
```
Confirms to the user that the contact was successfully saved.

---

### AddContact() helpers

#### getNonEmptyInput()

`std::string PhoneBook::getNonEmptyInput(const std::string &prompt) const`

- Private member function.  
- `const` means it won’t modify the phonebook’s state.  
- Takes a prompt message as a `const std::string&` (avoids copying).
- Uses a loop to keep asking until the user enters non-empty text.  
- `std::getline` is used to allow spaces in input.  
- Returns the validated string.  
 
#### getPhoneNumberInput()

`std::string PhoneBook::getPhoneNumberInput(const std::string &prompt) const`  

- Similar to getNonEmptyInput() but includes digit-only validation.  
- Includes a bool vari able `bool valid;` that will store the result of the validation check.   
- `site_t i` will be used for iterating through characters.  
- The manual while loop to ensure all characters are digits.  
- The `static_cast<unsigned char>` is needed because `std::isdigit()` expects an unsigned char or EOF — this avoids undefined behavior for negative char values.

---

## searchContacts() method

First, print the table header:  
```cpp
std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
```

Then loop over stored contacts:

```cpp
for (int i = 0; i < contactCount; i++)
{
    std::cout << "|" << std::setw(10) << i
              << "|" << std::setw(10) << truncate(contacts[i].getFirstName())
              << "|" << std::setw(10) << truncate(contacts[i].getLastName())
              << "|" << std::setw(10) << truncate(contacts[i].getNickname())
              << "|" << std::endl;
}
```

Key new thing here: `std::setw(10)` which sets the minimum width for the next output field.

> If the value is shorter, it’s padded (by default with spaces) on the left → right-aligned text.

Combined with truncate(), this ensures each column is exactly 10 chars wide.

What happens in the loop:
`i` → index number (0 to contactCount - 1)

For each contact:
- Call the getter (getFirstName(), etc.)
- Pass result through truncate() so it fits in the table
- Use `std::setw(10)` to print it right-aligned in a 10-char column

Example output:

```yaml
|         0|      Maria|   Sofia|     FloFlo|
```

Prompt for index:
```cpp
std::cout << "Enter index to view full contact: ";
std::string input;
std::getline(std::cin, input);
```

Reads the whole line into input (even if the user types a space or presses Enter).

Convert index string to number:
```cpp
int index = -1;
if (input.length() == 1 && isdigit(input[0]))
    index = input[0] - '0';
```

Only accepts single-digit input ('0' to '9').

Show full contact or error:
```cpp
if (index >= 0 && index < contactCount)
    contacts[index].displayFullInfo();
else
    std::cout << "Invalid index." << std::endl;
```
If index is valid → display the full stored data (no truncation).
Else → print error.

---

## truncate() helper

```cpp
static std::string truncate(const std::string &str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}
```

🔹 Purpose
Ensures that when printing strings in a fixed-width table (10 chars wide),
any string longer than 10 characters is shortened to first 9 characters + ..

🔹 Syntax & behavior
`static` here means the function is only visible in this .cpp file (not callable from other files).  
`const std::string &str` → pass-by-reference, no copy, and promise not to modify.
`str.length()` → returns the number of characters in the string.
`str.substr(0, 9)` → returns a substring from index 0 of length 9.
`+ "."` → appends a dot at the end to signal truncation.

If the string is 10 characters or less, return it unchanged.

Example:
```cpp
truncate("Alexanderson") → "Alexanders."
truncate("Maria")        → "Maria"
```
--- 
##  📊 Program Flowchart

```mermaid
flowchart TD
	A [Program Start] --> B [Display Menu: ADD / SEARCH / EXIT]
	B |ADD| --> C[Create Temp Contact]
			--> D[Get Non-Empty First Name]
			--> E[Get Non-Empty Last Name]
    		--> F[Get Non-Empty Nickname]
			--> G[Get Phone Number (digits only)]
    		--> H[Get Non-Empty Darkest Secret]
    		--> I[Store Contact in Array]
    		--> B

    B |SEARCH| --> J[Display Contacts Table]
   					--> K[Prompt for Index]
    				--> L{Valid Index?}
    					-->|Yes|--> M [Display Full Contact Info]
										--> B
    					-->|No| --> N [Show "Invalid index"]
    									--> B

    B -->|EXIT| --> O [Program End]
```

```
.------------------------------------------------------------------------------------------.
| If any link is broken, there is an error, a typo, or any other issue, please let me know.|
'------------------------------------------------------------------------------------------'  
      ^      (\_/)
      '----- (O.o)
             (> <)
```