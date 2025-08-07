/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:04:17 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/07 14:34:53 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

Contact::Contact() {}

void Contact::setFirstName(const std::string &value) { firstName = value; }
void Contact::setLastName(const std::string &value) { lastName = value; }
void Contact::setNickname(const std::string &value) { nickname = value; }
void Contact::setPhoneNumber(const std::string &value) { phoneNumber = value; }
void Contact::setDarkestSecret(const std::string &value) { darkestSecret = value; }

std::string Contact::getFirstName() const { return firstName; }
std::string Contact::getLastName() const { return lastName; }
std::string Contact::getNickname() const { return nickname; }

void Contact::displayFullInfo() const
{
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phoneNumber << std::endl;
    std::cout << "Darkest secret: " << darkestSecret << std::endl;
}

Contact::~Contact()
{
    std::cout << "Contact destroyed" << std::endl;
}