# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 09:06:57 by mbiagi            #+#    #+#              #
#    Updated: 2025/04/03 09:53:11 by mbiagi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#makefile per la parte di esecuzione

NAME = minishell_exec

SOURCES = execute.c execute_utils.c \
../builtin/builtin_env_controls.c ../builtin/builtin.c ../builtin/builtin_env.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		make -C ../libft/
		make -C ../get_next_line/
		$(CC) $(SOURCES) ../libft/libft.a ../get_next_line/libget_next_line.a \
		$(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C ../libft/
		make clean -C ../get_next_line/
		rm -f $(OBJ)

fclean: clean
		@echo fCleaning...
		make fclean -C ../libft/
		make fclean -C ../get_next_line/
		rm -f $(NAME)

re : fclean all

# libft:
# 		@echo Compiling Libft...
# 		make bonus -C ../libft/

.PHONY: all clean fclean re libft get_next_line
.SILENT:
