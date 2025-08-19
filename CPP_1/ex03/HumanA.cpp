/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:02:05 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 12:32:50 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const std::string& n, Weapon& w) : name(n), weapon(w) {};

void HumanA::attack() const {
	std::cout << this->name << " attacks with their " 
				<< this->weapon.getType() << std::endl;
}