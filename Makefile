# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/03/18 15:37:06 by mbiagi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = minishell.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory

all : $(NAME)

$(NAME): $(SOURCES)
		make libft
		$(CC) $(SOURCES) libft/libft.a $(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C libft

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
