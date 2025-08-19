/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_utils.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:05:16 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/18 10:58:48 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iomanip>
#include <cctype>
#include <iostream>

std::string PhoneBook::getNonEmptyInput(const std::string &prompt) const
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, input))
        {
            std::cout << "Input aborted." << std::endl;
            return "";
        }
        if (!input.empty())
            return input;
        std::cout << "This field cannot be empty." << std::endl;
    }
}

std::string PhoneBook::getPhoneNumberInput(const std::string &prompt) const
{
    std::string input;
    bool valid;
    size_t i;

    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, input))
        {
            std::cout << "Input aborted." << std::endl;
            return "";
        }

        valid = !input.empty();
        i = 0;
        while (i < input.length() && valid)
        {
            if (!std::isdigit(static_cast<unsigned char>(input[i])))
                valid = false;
            i++;
        }

        if (valid)
            return input;

        std::cout << "Invalid phone number. Only digits are allowed." << std::endl;
    }
}
