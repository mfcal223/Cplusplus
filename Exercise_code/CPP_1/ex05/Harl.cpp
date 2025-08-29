/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:21:18 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/21 14:21:56 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug(void)
{
	std::cout
		<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger."
		<< std::endl;
	std::cout << BLUE << "[DEBUG]" << ERASE << std::endl;
}

void Harl::info(void)
{
	std::cout
		<< "I cannot believe adding extra bacon costs more money. If you put  enough bacon in my burger, I wouldn’t have to ask for more!"
		<< std::endl;
	std::cout << CYAN << "[INFO]" << ERASE << std::endl;
}

void Harl::warning(void)
{
	std::cout
		<< "I think I deserve to have some extra bacon for free. I’ve been coming for  years whereas you started working here since last month."
		<< std::endl;
	std::cout << YELLOW << "[WARNING]" << ERASE << std::endl;
}

void Harl::error(void)
{
	std::cout
		<< "This is unacceptable! I want to speak to the manager now."
		<< std::endl;
	std::cout << RED << "[ERROR]" << ERASE << std::endl;
}

void Harl::complain(std::string& level)
{
    typedef void (Harl::*Action)(); //pointer-to-member type to avoid repeating

    // lookup tables to avoid if/elses
    const std::string names[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    const Action      funcs[4] = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };

    for (int i = 0; i < 4; ++i) {
        if (level == names[i]) {
            (this->*funcs[i])();
            return;
        }
    }
}