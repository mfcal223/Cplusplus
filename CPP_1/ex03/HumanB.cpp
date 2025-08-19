/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:22:09 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 12:32:41 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string &n) : name(n), weapon(NULL) {};

void HumanB::setWeapon(Weapon& w) {
	this->weapon = &w;
}

void HumanB::attack() const {
	if (this->weapon)
		std::cout	<< this->name << " attacks with their "
					<< this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " is unarmed." << std::endl;
}

/*
HumanB may be unarmed. So weapon* weapon might be NULL
*/