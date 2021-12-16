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

GCC			=			clang++

OBJS        =			$(SRCS:.c=.o)

RM			=			rm -f

FLAGS		=			-Wall -Wextra -Werror -std=c++98

INCLUDE		=			

SRCS		=			main.cpp \

all:	$(NAME)

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:			fclean all

.PHONY: re clean fclean