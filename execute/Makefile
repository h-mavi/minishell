# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 09:06:57 by mbiagi            #+#    #+#              #
#    Updated: 2025/04/22 12:04:06 by mfanelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#makefile per la parte di esecuzione

NAME = minishell_exec

SOURCES = execute.c execute_utils.c execute_utils2.c execute_pipe.c \
execute_redir.c ../builtin/builtin_env_controls.c ../builtin/builtin.c \
../builtin/builtin_env.c ../builtin/builtin_env_utils.c ../builtin/builtin2.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -Iprintf -Lprintf

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		@echo Compiling...
		make -C ../libft/
		make -C ../get_next_line/
		make -C ../printf/
		$(CC) $(SOURCES) ../libft/libft.a ../get_next_line/libget_next_line.a \
		../printf/libftprintf.a $(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C ../libft/
		make clean -C ../get_next_line/
		make clean -C ../printf/
		rm -f $(OBJ)

fclean: clean
		@echo fCleaning...
		make fclean -C ../libft/
		make fclean -C ../get_next_line/
		make fclean -C ../printf/
		rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re libft get_next_line printf
.SILENT:
