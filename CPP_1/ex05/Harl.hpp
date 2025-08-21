/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:21:25 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/21 14:21:53 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <string>

# define ERASE     	"\033[0m"
# define YELLOW    	"\033[33m"
# define RED       	"\033[31m"      
# define GREEN     	"\033[32m"      
# define MAGENTA   	"\033[35m"
# define BLUE      	"\033[34m"      
# define CYAN      	"\033[36m"  

class Harl {
private: 
	void debug( void );
	void info( void );
	void warning( void );
	void error( void );

public:
	Harl();
	~Harl();
 	void  complain( std::string& level );
};

#endif