/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:04:36 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/12 16:03:13 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
    Contact contacts[8];
    int contactCount;
    int nextIndex;
    std::string getNonEmptyInput(const std::string &prompt) const;
    std::string getPhoneNumberInput(const std::string &prompt) const;

public:
    PhoneBook();
    void addContact();
    void searchContacts() const;
};

#endif