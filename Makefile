# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/04/11 14:51:03 by mbiagi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = minishell.c builtin/builtin_env_controls.c builtin/builtin_env.c builtin/builtin.c \
execute/execute_pipe.c execute/execute_utils.c execute/execute.c parsing/pars_main.c\
parsing/pars_extra.c parsing/pars_heredoc.c parsing/pars_refine.c parsing/pars_rm.c \
parsing/pars_set_data.c parsing/pars_utils.c parsing/pars_split.c parsing/parsing.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		make -C libft/
		make -C get_next_line/
		make -C printf/
		$(CC) $(SOURCES) libft/libft.a get_next_line/libget_next_line.a \
		printf/libftprintf.a $(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C libft/
		make clean -C get_next_line/
		make clean -C printf/
		rm -f $(OBJ)

fclean: clean
		@echo fCleaning...
		make fclean -C libft/
		make fclean -C get_next_line/
		make fclean -C printf/
		rm -f $(NAME)

re : fclean all

libft:
		@echo Compiling Libft...
		make -C libft/

.PHONY: all clean fclean re libft
.SILENT:
