/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:59:34 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 13:26:27 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Default constructor: (0, 0)
Point::Point() : _x(0), _y(0) {}

// Copy constructor: initialize const members from source
Point::Point(Point const& other) : _x(other._x), _y(other._y) {}

// Copy assignment: members are const, so nothing to assign
Point& Point::operator=(Point const& rhs) {
    (void)rhs;
    return *this;
}

// Construct from two floats
Point::Point(float const n1, float const n2) : _x(n1), _y(n2) {}

Point::~Point() {}

Fixed const& Point::getX() const { return this->_x; }
Fixed const& Point::getY() const { return this->_y; }

