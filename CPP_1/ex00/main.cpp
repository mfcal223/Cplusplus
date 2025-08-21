/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:00:17 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/21 12:45:50 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie *newZombie(std::string name);
void randomChump(std::string name);

int main()
{
    // Stack allocation: created, announces, destroyed automatically at end of scope
    std::cout << "-----randomChump = STACK allocation  ----" << std::endl;
    randomChump("Bob");

    std::cout << "-----newZombie = HEAP allocation  ----" << std::endl;
    // Heap allocation: created, used outside scope, must be deleted manually
    Zombie *jim = newZombie("Jim");
    jim->announce();
    delete jim;

    Zombie *ana = newZombie("Ana");
    ana->announce();
    delete ana;

    return (0);
}