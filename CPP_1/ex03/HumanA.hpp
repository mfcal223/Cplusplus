/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:45:09 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:03 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA {
private:
    std::string	name;
	Weapon&		weapon;

public:
	HumanA(const std::string& n, Weapon& w);
	void attack() const;
};

#endif

/*
HumanA will always have a weapon. The weapon HAS to be init with the constructor.
*/