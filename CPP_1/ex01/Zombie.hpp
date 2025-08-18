/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:58:13 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/18 14:25:01 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>
#include <sstream> // for std::ostringstream

class Zombie
{
private:
    std::string _name;

public:
    Zombie();
    Zombie(std::string name); // constructor with name
    ~Zombie();
    
    void announce(void);
    void setName(const std::string newname);
};

#endif
