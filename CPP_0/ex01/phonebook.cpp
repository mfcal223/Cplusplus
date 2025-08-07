/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:05:02 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/07 14:07:19 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
#include <iomanip>

PhoneBook::PhoneBook() : contactCount(0), nextIndex(0) {}

void PhoneBook::addContact()
{
    Contact c;
    std::string input;

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    c.setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    c.setLastName(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    c.setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    c.setPhoneNumber(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    c.setDarkestSecret(input);

    contacts[nextIndex] = c;
    nextIndex = (nextIndex + 1) % 8;
    if (contactCount < 8)
        contactCount++;

    std::cout << "Contact saved." << std::endl;
}

static std::string truncate(const std::string &str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::searchContacts() const
{
    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
    for (int i = 0; i < contactCount; i++)
    {
        std::cout << "|" << std::setw(10) << i
                  << "|" << std::setw(10) << truncate(contacts[i].getFirstName())
                  << "|" << std::setw(10) << truncate(contacts[i].getLastName())
                  << "|" << std::setw(10) << truncate(contacts[i].getNickname())
                  << "|" << std::endl;
    }

    std::cout << "Enter index to view full contact: ";
    std::string input;
    std::getline(std::cin, input);
    int index = -1;
    if (input.length() == 1 && isdigit(input[0]))
        index = input[0] - '0';
    if (index >= 0 && index < contactCount)
        contacts[index].displayFullInfo();
    else
        std::cout << "Invalid index." << std::endl;
}
