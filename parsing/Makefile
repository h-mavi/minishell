# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 11:21:22 by mfanelli          #+#    #+#              #
#    Updated: 2025/04/01 09:14:04 by mfanelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFILE ESCLUSIVO PER IL PARSING

NAME = minishell_pars

SOURCES = pars_main.c parsing.c pars_split.c pars_utils.c parsing_set_data.c \
pars_refine.c
OBJ = $(SOURCES:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ilibft -Llibft -lreadline -lhistory

all : $(NAME)

$(NAME): $(OBJ) $(SOURCES)
		make libft
		$(CC) $(SOURCES) ../libft/libft.a $(FLAGS) -o $(NAME)

clean:
		@echo Cleaning...
		make clean -C ../libft/
		rm -f $(OBJ)

fclean: clean
		@echo fCleaning...
		make fclean -C ../libft/
		rm -f $(NAME)

re : fclean all

libft:
		@echo Compiling Libft...
		make bonus -C ../libft/

.PHONY: all clean fclean re libft
.SILENT:
