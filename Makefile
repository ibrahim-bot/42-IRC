# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichougra <ichougra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 12:32:01 by ichougra          #+#    #+#              #
#    Updated: 2021/12/14 12:34:34 by ichougra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=			ircserv

HEADER		=			irc.hpp

SRCS		=			main.cpp

GCC			=			clang++

OBJS        =			$(SRCS:.cpp=.o)

RM			=			rm -rf

FLAGS		=			-Wall -Wextra -Werror -std=c++98

INCLUDE		=			

all:	$(NAME)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: re clean fclean