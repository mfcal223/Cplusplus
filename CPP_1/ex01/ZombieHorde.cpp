/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:07:09 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/18 14:44:55 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string baseName)
{
    int i;
    
    if (N <= 0)
    {
        std::cout << "Amount of zombies must be greater than 0" << std::endl;
        return NULL;
    }
    Zombie *horde = new Zombie[N]; // allocate N zombies
    for (i = 0; i < N; i++)
    {
        std::ostringstream oss;
        oss << baseName << "_" << i;
        horde[i].setName(oss.str()); // set unique name
    }
    return (horde);
    
}

