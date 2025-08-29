/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:27:01 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/21 14:10:31 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string& t) : type(t) {}

const std::string& Weapon::getType() const {
    return this->type;
}

void Weapon::setType(const std::string& newType){
    this->type = newType;
}
