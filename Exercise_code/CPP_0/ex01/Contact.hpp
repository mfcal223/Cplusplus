/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:03:35 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/07 14:35:06 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact
{
private:
    std::string firstName;
    std::string lastName;
    std::string nickname;
    std::string phoneNumber;
    std::string darkestSecret;

public:
    Contact();
    ~Contact(); 

    void setFirstName(const std::string &value);
    void setLastName(const std::string &value);
    void setNickname(const std::string &value);
    void setPhoneNumber(const std::string &value);
    void setDarkestSecret(const std::string &value);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    void displayFullInfo() const;
    
};

#endif