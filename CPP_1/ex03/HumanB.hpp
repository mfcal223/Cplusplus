/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:45:06 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 12:25:34 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanB{
private:
	std::string	name;
	Weapon*		weapon;
	
public:
	explicit HumanB(const std::string& n);
	void setWeapon(Weapon &w);
	void attack() const;
};

#endif

/*
HumanB may be unarmed. So weapon* weapon might be NULL
*/