# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/03/20 17:36:45 by mfanelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = minishell.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory

all : $(NAME)

$(NAME): $(OBJ)
		make libft
		$(CC) $(OBJ) libft/libft.a $(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C libft
		rm -f $(OBJ)

fclean: clean
		@echo fCleaning...
		make fclean -C libft
		rm -f $(NAME)

re : fclean all

libft:
		@echo Compiling Libft...
		make -C libft/

.PHONY: all clean fclean re libft
.SILENT:
