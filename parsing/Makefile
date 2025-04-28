# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/04/28 14:34:58 by mbiagi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFILE ESCLUSIVO PER IL PARSING

NAME = minishell_pars

SOURCES = pars_main.c parsing.c pars_split.c pars_utils.c pars_set_data.c \
pars_refine.c pars_rm.c pars_heredoc.c pars_extra.c ../execute/execute.c ../execute/execute_utils.c \
../execute/execute_utils2.c ../execute/execute_pipe.c \
../execute/execute_redir.c ../builtin/builtin_env_controls.c ../builtin/builtin.c \
../builtin/builtin_env.c ../builtin/builtin_env_utils.c ../builtin/builtin2.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		make libft
		make gnl
		make ft_printf
		$(CC) $(SOURCES) ../libft/libft.a ../get_next_line/libget_next_line.a ../printf/libftprintf.a $(FLAGS) -o $(NAME)

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

libft:
		@echo Compiling Libft...
		make bonus -C ../libft/

gnl:
		@echo Compiling get_next_line...
		make -C ../get_next_line/

ft_printf:
		@echo Compiling ft_printf...
		make -C ../printf/

exe:
		make
		make clean
		valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --suppressions=supp.supp --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re libft gnl ft_printf exe
.SILENT:
