/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:59:27 by mcalciat          #+#    #+#             */
/*   Updated: 2025/09/03 14:28:18 by mcalciat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Forward declaration (bsp.cpp)
bool bsp(Point const a, Point const b, Point const c, Point const p);

// Helper to print a Point as "(x, y)"
static void print_point(std::string const& name, Point const& p) 
{
	std::cout << name << " = (" << p.getX() << ", " << p.getY() << ")" << std::endl;
}

static void run_case(std::string const& title,
						Point const& A, Point const& B, Point const& C,
						Point const& P)
{
	std::cout << "---- " << title << " ----" << std::endl;
	print_point("A", A);
	print_point("B", B);
	print_point("C", C);
	print_point("P", P);

    bool inside = bsp(A, B, C, P);
    std::cout << "bsp(A,B,C,P) => " << (inside ? "true (inside)" : "false (outside or on edge)") << std::endl;
}

int main() {
	std::cout << "---- Triangle Nr 1 ----" << std::endl;
	Point A(1.0f, 1.0f);
	Point B(5.0f, 1.0f);
	Point C(3.0f, 4.0f);

	Point P_inside(3.0f, 2.0f); // clearly inside
	Point P_edge  (3.0f, 1.0f); // on edge AB -> must be false
	Point P_vertex(1.0f, 1.0f); // exactly A   -> must be false
	Point P_out   (0.0f, 0.0f); // outside

	run_case("Inside", A, B, C, P_inside);
	run_case("On edge", A, B, C, P_edge);
	run_case("On vertex", A, B, C, P_vertex);
	run_case("Outside", A, B, C, P_out);

	std::cout << "---- Triangle Nr 2 -----" << std::endl;
	Point D1(0.0f, 0.0f);
	Point D2(2.0f, 2.0f);
	Point D3(4.0f, 4.0f);
	run_case("Degenerate (collinear triangle)", D1, D2, D3, P_inside);

	return (0);
}
