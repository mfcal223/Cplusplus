/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:00:17 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/18 14:25:55 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <cstdlib> // for atoi

Zombie *zombieHorde(int N, std::string name);

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Input Error. Try: " << av[0] << " <number_of_zombies>" << std::endl;
        return -1;
    }

    int N = std::atoi(av[1]);
    if (N <= 0)
    {
        std::cout << "Number of zombies must be a positive INT." << std::endl;
        return -1;
    }

    Zombie *horde = zombieHorde(N, "HordeGuy");
    for (int i = 0; i < N; i++)
        horde[i].announce();
    delete[] horde;

    return (0);
}
