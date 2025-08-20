# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 11:07:08 by mcalciat          #+#    #+#              #
#    Updated: 2025/08/19 16:49:50 by mcalciat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= harl

SRC		= main.cpp Harl.cpp

OBJ		= $(SRC:.cpp=.o)

CXX		= c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Removing object files..."
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re