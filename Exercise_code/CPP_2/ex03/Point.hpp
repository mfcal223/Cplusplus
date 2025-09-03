/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:59:38 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 13:52:47 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point 
{
private:
	Fixed const _x;
	Fixed const	_y;	
	//anything else useful
	
public:
	Point();
	Point(const Point& other);
	Point& operator=(const Point& rhs);
	~Point();

	Point(float const n1, float const n2); // + x e y as parameters???

	// Accessors
	Fixed const& getX() const;
	Fixed const& getY() const;

};
#endif

/*
Accesors: the return type = fixed const (returns a const reference)
Cannot use accesor from Fixed class as _raw exposes the fixed-point inteder, 
and it's not the scaled “real value”.
*/