/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/02 16:21:07 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./../libft/libft.h"

# include <stdio.h>
# include <signal.h>
# include <ctype.h>
# include <stdlib.h>
# include <strings.h>
# include <string.h>
# include <dirent.h>
# include <bsd/string.h>
# include <fcntl.h>
# include <unistd.h>
# include <linux/stat.h>
# include <sys/stat.h>
# include <stddef.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define COMMAND 1
# define FLAG 2 //option
# define PIPE 3
//<
# define REDIR_1 4
// >
# define REDIR_2 5
// >>
# define REDIR_3 6
# define HEREDOC 7

typedef struct s_token
{
	int				type;
	const char		*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

//in parsing/pars_main.c
void		routine(int sig);
void		token_inator(char *cmd, char **env);
int			parsing(char *pwd, char **env);

//in parsing/pars_refine.c
char		*rewrite(char *orig, int i, int x);
char		*here_glued(char *s);
char		*espand(char *s, char **env);

//in parsing/pars_rm.c
char	 	*rm_spaces(char *s);
char		*rm_app(char *s);
char 		*rm_dollar(char *s);
char		*divide(char *s, int y);

//in parsing/pars_split.c
int			len_arr_split(char const *arr);
void		frite(char *dest, int start, int len, char const *s);
char		**fill(char **dest, char const *s, int len_arr);
char		**custom_split(char const *s);

//in parsing/pars_utils.c
void		free_arr(char **arr);
int 		werami(const char *s, int index);
int 		find_char(char *s, int i);
int			check_error(char *s);

//in parsing/parsing.c
char		*refine(char *s, char **env);
int 		check_if_cmd(char *cmd, char **env);

//in parsing/parsing_set_data.c
void		set_data(t_token **head, char *str, int flag);
void		print_lists(t_token *head);
void		set_prev(t_token **head);

#endif