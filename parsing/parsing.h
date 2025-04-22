/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/22 12:04:45 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "./../execute/execute.h"
# include "token.h"

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

//----------------------------------------------------------------------------
//in parsing/pars_extra.c

char		*set_str(char *s);
char		*set_path(char *tmp, char **env);
int			len_arr_utils(char *s, int *i, int *x, int app);
int			count_len_wrd(char *s, int *y, int conta);
char		*smells_goog(char *s, int *i, char **env);

//----------------------------------------------------------------------------
//in parsing/pars_heredoc.c

void		here_doc(char *input);
void		ft_openhd_ls(t_token *head, int where);
void		ft_openhd_str(char *str, int where);
int			control_str(char *str, char *argv);

//----------------------------------------------------------------------------
//in parsing/pars_main.c

void		routine(int sig);
void		compile_inator(char **str, char **env, t_token **head);
t_token		*token_inator(char *cmd, char **env, t_token *head);
int			parsing(char *pwd, char **env);

//----------------------------------------------------------------------------
//in parsing/pars_refine.c

char		*rewrite(char *orig, int i, int x);
char		*here_glued(char *s);
char		*espand(char *s, char **env);
char		*esp_special_case(char *s, char **env, int i);
char		*refine(char *s, char **env);

//----------------------------------------------------------------------------
//in parsing/pars_rm.c

char		*rm_spaces(char *s);
char		*rm_app(char *s);
char		*rm_dollar(char *s);
int			if_divide(char *s, int i, int y);
char		*divide(char *s, int y);

//----------------------------------------------------------------------------
//in parsing/pars_set_data.c

void		lstadd_back(t_token **lst, t_token *new);
void		set_data(t_token **head, char **str, int flag, int id);
void		print_lists(t_token *head);
void		set_prev(t_token **head);

//----------------------------------------------------------------------------
//in parsing/pars_split.c

int			realigning_i(char *s, int i, int y);
int			len_arr_split(char *arr);
void		frite(char *dest, int start, int len, char *s);
char		**fill(char **dest, char *s, int len_arr, int i);
char		**custom_split(char *s);

//----------------------------------------------------------------------------
//in parsing/pars_utils.c

void		free_arr(char **arr);
int			werami(char *s, int index);
int			find_char(char *s, int i);
int			find_dollar(char *s, int i);
int			check_error(char *s);

//----------------------------------------------------------------------------
//in parsing/parsing.c

char		*reassemble(char *first, char *espan, char *after, int len_cmd);
int			check_error_lst(t_token *head);
void		free_lst(t_token *head);
char		*error_exit(t_token *head, int syn, char *str, char *input);

//----------------------------------------------------------------------------

#endif