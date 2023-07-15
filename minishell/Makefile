# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 09:45:11 by fabperei          #+#    #+#              #
#    Updated: 2023/06/27 14:00:11 by aguezzi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	./src/minishell.c		\
		./src/exe.c 			\
		./src/ft_echo.c			\
		./src/ft_env.c			\
		./src/parsing.c			\
		./src/list.c			\
		./src/command_cd_1.c	\
		./src/command_cd_2.c	\

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

#-fsanitize=address -g
#LDFLAGS = -L $(HOME)/.brew/opt/readline/lib

#CPPFLAGS = -I $(HOME)/.brew/opt/readline/include/readline -I .

all : $(NAME)

$(NAME) :	$(OBJS)
			@echo "Linking $(NAME)..."
			@echo "Compil Libft..."
			@make -C libft
			@$(CC) $(CFLAGS) -Llibft -lft -lreadline -o $(NAME) $(OBJS)
			@echo "$(NAME) created."

.c.o :
			@echo "Compiling $<..."
			@$(CC) $(CFLAGS) -c $< -o $@

clean :
			@echo "Cleaning object files..."
			@rm -f $(OBJS)
			@make clean -C libft

fclean: clean
			@echo "Cleaning $(NAME) and Libft..."
			@rm -f $(NAME)
			@rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re
