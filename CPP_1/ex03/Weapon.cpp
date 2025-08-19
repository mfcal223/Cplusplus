/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:27:01 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 11:42:39 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

/*
    explicit Weapon(const std::string& type);
    const std::string& getType() const;
    void setType(const std::string& newType);
*/

Weapon::Weapon(const std::string& t) : type(t) {}

const std::string& Weapon::getType() const {
    return this->type;
}

void Weapon::setType(const std::string& newType){
    this->type = newType;
}
