NAME 		= serveur

CC 	 		= clang++ -Wall -Wextra -Werror

DIR_SRC			= srcs/

SRC  		=	main.cpp\
				server.cpp\
				socket.cpp\
				init.cpp\
				util.cpp\
				cmd.cpp\
				cmd_join.cpp\
				cmd_leave.cpp\
				cmd_msg.cpp\
				cmd_nick.cpp\
				cmd_who.cpp\
				ring_buffer.cpp

SRCS		=	$(addprefix $(DIR_SRC), $(SRC))

OBJ  		= $(SRCS:.cpp=.o)

INC_DIR		= ./incs/

all: $(NAME)

$(LIBFT):
	@clear
	@printf "Compiling libft ... "
	@make -C libft/
	@echo "Done"

$(NAME) : 	msg $(OBJ) $(HEADERS) comp
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
			$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
			printf "$(GREEN2)███"

clean:
			@rm -f $(OBJ)
			@echo ${ORANGE}"Cleaning"$(NC)

fclean: clean
			@rm -f $(NAME)
			@echo ${GREEN}"Cleaning EXEC and LIB"$(NC)

re:		clean all

run: re
	@echo $(GREEN)"Start!"$(NC)
	@./$(NAME) localhost:127.0.0.1:0 6667 23

nc:
	@echo $(GREEN)"Enter to server new user"$(NC)
	@nc 127.0.0.1 6667

.PHONY: all, clean, fclean, re, run, nc

.SILENT:

#----END-----#
NC='\033[0m'

#--------Colors---------#
GREEN ='\033[1;32m'
GREEN2 = \033[32m
ORANGE ='\033[1;33m'
BLACK = \033[0;30m
RED = \033[0;31m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[0;37m

#-----------PRINT------#
msg:
	@echo $(ORANGE)"Wait for compilation..."$(NC)

comp:
	@echo $(GREEN)" √ "$(NC)
	@echo $(GREEN)"==> Compile successfully"$(NC)
