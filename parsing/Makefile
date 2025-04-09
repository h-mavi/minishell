# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/04/09 09:40:33 by mfanelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFILE ESCLUSIVO PER IL PARSING

NAME = minishell_pars

SOURCES = pars_main.c parsing.c pars_split.c pars_utils.c pars_set_data.c \
pars_refine.c pars_rm.c pars_heredoc.c pars_extra.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory \
#--suppressions=supp.supp

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		make libft
		make gnl
		$(CC) $(SOURCES) ../libft/libft.a ../get_next_line/libget_next_line.a $(FLAGS) -o $(NAME)

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

libft:
		@echo Compiling Libft...
		make bonus -C ../libft/

gnl:
		@echo Compiling get_next_line...
		make -C ../get_next_line/

.PHONY: all clean fclean re libft gnl
.SILENT:
