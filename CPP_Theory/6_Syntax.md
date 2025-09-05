# C++ SYNTAX

## In headers

🔹 Class data members (variables)  
    `std::string firstName;`   
| std::string	| firstName; |
|---------------|------------|
|ClassName::MethodName | name of variable |

🔹 Getter functions  
    `std::string getFirstName() const;`  

| std::string	| getFirstName() | const; |
|---------------|----------------|--------|
| ClassName::MethodName	| function name	 | function doesn´t modify any variable  

> getters only read. It is a good practice to add "const"  

🔹 Setter functions  
    `void setFirstName(const std::string &value);`  

| void	| setFirstName | (const  | std::string &value) |
|-------|--------------|---------|---------------------|
| return type | function name    | no modification | identifier "value" passed by reference

> "&value" is a common, neutral choice. It is the local name for incoming data. It could be named "name", "variable", or any other user choice.  

🔹 Constructor & Destructor  
        `Contact();`  
        `~Contact();`  
	Needs same name as class. No return type.  
	Adds "~" as prefix for destructor.  

## In .cpp (implementation) files  

🔹 Constructor definition  
        `Contact::Contact() {}`  
		-------    -------   |----> body is empty  
         |			same name  
	belong to		as class.  
	this class		No return type.  

🔹 Setter  
        `void Contact::setFirstName(const std::string &value)`  
		-----  ------   ---------  -----     ---------------
	return -|   class   function     |		identifier "value" passed by reference    
	type   		          name 	     |				to  avoid unnecessary copy  
							promise not to modify  
							the string passed in  