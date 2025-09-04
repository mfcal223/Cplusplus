/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:02:54 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/04 11:22:45 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

# define ERASE     	"\033[0m"
# define YELLOW    	"\033[1;33m"
# define RED       	"\033[1;31m"      
# define GREEN     	"\033[1;32m"      
# define MAGENTA   	"\033[1;35m"
# define BLUE      	"\033[1;34m"      
# define CYAN      	"\033[1;36m"  

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
