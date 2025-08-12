/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:05:02 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/12 16:03:17 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iomanip>
#include <cctype>
#include <iostream>

PhoneBook::PhoneBook() : contactCount(0), nextIndex(0) {}

void PhoneBook::addContact()
{
	Contact c;

	c.setFirstName(getNonEmptyInput("Enter first name: "));
	c.setLastName(getNonEmptyInput("Enter last name: "));
	c.setNickname(getNonEmptyInput("Enter nickname: "));
	c.setPhoneNumber(getPhoneNumberInput("Enter phone number: "));
	c.setDarkestSecret(getNonEmptyInput("Enter darkest secret: "));

	contacts[nextIndex] = c;
	nextIndex = (nextIndex + 1) % 8;
	if (contactCount < 8)
		contactCount++;

	std::cout << "Contact saved." << std::endl;
}
/* at the end of addContact(), contact c goes out of scope so it is destroyed */

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
	{
        std::cout << "Invalid index. Use SEARCH to check valid index" << std::endl;
		std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
	}
}
