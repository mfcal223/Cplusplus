/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:06:51 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/18 10:58:53 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <iostream>

int main()
{
    PhoneBook phonebook;
    std::string command;

    std::cout << "Welcome to the My-80s-incredible-PhoneBook" << std::endl;
    std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);
        if (std::cin.eof())
            break;
        if (command == "ADD")
            phonebook.addContact();
        else if (command == "SEARCH")
            phonebook.searchContacts();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Unknown command." << std::endl;
    }
    std::cout << "All contacts will be deleted. Goodbye!" << std::endl;
    return 0;
}
