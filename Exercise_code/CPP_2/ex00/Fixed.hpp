
#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
private:
    int                 _raw;
    static const int    _fracBits;

public:
    Fixed();                            // Default constructor
    Fixed(const Fixed& other);          // Copy constructor
    Fixed& operator=(const Fixed& rhs); // Copy assignment
    ~Fixed();                           // Destructor

    int  getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif
