# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcalciat <mcalciat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 11:07:08 by mcalciat          #+#    #+#              #
#    Updated: 2025/08/19 12:42:40 by mcalciat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= phonebook

SRC		= Phonebook.cpp Contact.cpp main.cpp \
			Phonebook_utils.cpp

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