/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:45:04 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/19 15:59:58 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "Wrong input. Try: " 
					<< av[0] 
					<< " <filename> <s1> <s2>" 
					<< std::endl;
        return (1);
    }

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];

    if (s1.empty())
    {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return (1);
    }

	std::ifstream infile(filename.c_str()); // Open the input file for reading.
	if (!infile)
    {
        std::cerr << "Error: cannot open input file " << filename << std::endl;
        return 1;
    }

	std::ofstream outfile((filename + ".replace").c_str()); // Create the output file
	if (!outfile)
    {
        std::cerr << "Error: cannot create output file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) //reads input file line by line
    {
        std::string result;
        size_t pos = 0, found;
        while ((found = line.find(s1, pos)) != std::string::npos)
        {
            result += line.substr(pos, found - pos);
            result += s2;
            pos = found + s1.length();
        }
        result += line.substr(pos);
        outfile << result << std::endl;
    }

    return 0;
}
