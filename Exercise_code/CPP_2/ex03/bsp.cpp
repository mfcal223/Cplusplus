/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:08:05 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 14:09:49 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include "Fixed.hpp"

/**
 * cross(AB,AP)=(Bx​−Ax​)*(Py​−Ay​)−(By​−Ay​)*(Px​−Ax​)
 * > 0 → P is left of A->B
 * < 0 → P is right of A->B
 * = 0 → collinear
 */
static Fixed cross(Point const& A, Point const& B, Point const& P) 
{
    Fixed abx = B.getX() - A.getX();
    Fixed aby = B.getY() - A.getY();
    Fixed apx = P.getX() - A.getX();
    Fixed apy = P.getY() - A.getY();
    return (abx * apy - aby * apx);
}


bool bsp(Point const a, Point const b, Point const c, Point const p) 
{
    Fixed const zero(0);

    // Degenerate triangle (area == 0) → no interior
    Fixed area2 = cross(a, b, c);
    if (area2 == zero)				//there is NO triangle
        return false;

    // Side tests relative to each directed edge
    Fixed s1 = cross(a, b, p);
    Fixed s2 = cross(b, c, p);
    Fixed s3 = cross(c, a, p);

    // On an edge or vertex? (strictly inside is required) → false
    if (s1 == zero || s2 == zero || s3 == zero)
        return false;

    // Strict interior if all three have the same sign
    bool hasPos = (s1 > zero) || (s2 > zero) || (s3 > zero);
    bool hasNeg = (s1 < zero) || (s2 < zero) || (s3 < zero);

    return (hasPos != hasNeg);
}
/**
 * After excluding zeros (edge cases), results can be:
 * All positive → hasPos = true, hasNeg = false → returns true.
 * All negative → hasPos = false, hasNeg = true → returns true.
 * Mixed signs → both true → returns false (outside).
 */