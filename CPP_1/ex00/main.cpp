/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:00:17 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/13 15:00:48 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie *newZombie(std::string name);
void randomChump(std::string name);

int main()
{
    // Stack allocation: created, announces, destroyed automatically at end of scope
    randomChump("Bob");

    // Heap allocation: created, used outside scope, must be deleted manually
    Zombie *jim = newZombie("Jim");
    jim->announce();
    delete jim;

    // Another quick check
    Zombie *ana = newZombie("Ana");
    delete ana; // ensure destructor message prints with the correct name

    return (0);
}