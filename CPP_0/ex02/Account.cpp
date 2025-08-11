/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:57:08 by mcalciat          #+#    #+#             */
/*   Updated: 2025/08/11 15:02:04 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

/* ---------- Static members ------------------------------------------------ */

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/* ---------- Utils --------------------------------------------------------- */

void Account::_displayTimestamp(void)
{
    std::time_t now = std::time(NULL);
    std::tm *tm = std::localtime(&now);
    char buf[20];

    if (tm && std::strftime(buf, sizeof(buf), "[%Y%m%d_%H%M%S]", tm))
        std::cout << buf << " ";
    else
        std::cout << "[00000000_000000] ";
}

/* ---------- Ctors / Dtor -------------------------------------------------- */

Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts),
      _amount(initial_deposit),
      _nbDeposits(0),
      _nbWithdrawals(0)
{
    _nbAccounts += 1;
    _totalAmount += initial_deposit;

    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";created" << std::endl;
}

Account::~Account(void)
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";closed" << std::endl;
}

/* Private default constructor (declared private in header) */
Account::Account(void)
    : _accountIndex(-1), _amount(0), _nbDeposits(0), _nbWithdrawals(0)
{
    /* Not used */
}

/* ---------- Getters (static) --------------------------------------------- */

int Account::getNbAccounts(void)
{
    return _nbAccounts;
}

int Account::getTotalAmount(void)
{
    return _totalAmount;
}

int Account::getNbDeposits(void)
{
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void)
{
    return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void)
{
    _displayTimestamp();
    std::cout << "accounts:" << getNbAccounts()
              << ";total:" << getTotalAmount()
              << ";deposits:" << getNbDeposits()
              << ";withdrawals:" << getNbWithdrawals()
              << std::endl;
}

/* ---------- Per-account ops ---------------------------------------------- */

void Account::makeDeposit(int deposit)
{
    int p_amount = _amount;

    _amount += deposit;
    _nbDeposits += 1;

    _totalAmount += deposit;
    _totalNbDeposits += 1;

    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << p_amount
              << ";deposit:" << deposit
              << ";amount:" << _amount
              << ";nb_deposits:" << _nbDeposits
              << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
    int p_amount = _amount;

    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << p_amount;

    if (withdrawal > _amount)
    {
        std::cout << ";withdrawal:refused" << std::endl;
        return false;
    }

    _amount -= withdrawal;
    _nbWithdrawals += 1;

    _totalAmount -= withdrawal;
    _totalNbWithdrawals += 1;

    std::cout << ";withdrawal:" << withdrawal
              << ";amount:" << _amount
              << ";nb_withdrawals:" << _nbWithdrawals
              << std::endl;
    return true;
}

int Account::checkAmount(void) const
{
    return _amount;
}

void Account::displayStatus(void) const
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals
              << std::endl;
}