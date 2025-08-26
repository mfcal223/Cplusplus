#ifndef EXAMPLE_HPP
# define EXAMPLE_HPP

#include <string>

class Example
{
	private:
		int			num;
		std::string	name;

    public:
    // Orthodox Canonical Form
    Example();                         		// Default constructor
    Example(const Example& ex);        		// Copy constructor
    Example& operator=(const Example& ex); 	// Copy assignment
    ~Example();                        		// Destructor

    // Small public API for your main()
    void setNum(int n);
    void setName(const std::string& s);
    int getNum() const;
    const std::string& getName() const;
};

#endif