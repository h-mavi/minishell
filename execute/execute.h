/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:03:23 by mbiagi            #+#    #+#             */
/*   Updated: 2025/05/05 15:09:13 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../builtin/builtin.h"
# include "../parsing/parsing.h"
# include "../parsing/token.h"
# include "../printf/ft_printf.h"

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
# define FLAG 2
# define PIPE 3
//<
# define REDIR_1 4
// >
# define REDIR_2 5
// >>
# define REDIR_3 6
# define HEREDOC 7
// << "$USER"
# define HEREDOC_2 8

//----------------------------------------------------------------------------
//in execute/execute_pipe.c (ft 5/5)

void	for_fork(t_token *tree, char ***env, int *std);

//----------------------------------------------------------------------------
//in execute/execute_redir.c (ft 3/5)

void	heredoc(t_token *tree, int *std, char **env);
int		redir_check(t_token *tree, int n, int *std, char **env);
void	ctrl_c_sig(int sig);

//----------------------------------------------------------------------------
//in execute/execute_utils.c (ft 5/5)

int	exit_code(int n);
t_token	*find_comand(t_token *tree);
void	dup_file(int file, int std);
int		pipe_check(t_token *tree);
int		file_control(int file, int std);

//----------------------------------------------------------------------------
//in execute/execute_utils2.c (ft 5/5)

int		ctrl_str(char *str, char *limiter);
void	freemtr(char **mtr);
void	reset_fd(int *std);
int		ft_compare(char *s1, char *s2);
int		ft_compare2(char *s1, char *s2);

//----------------------------------------------------------------------------
//in execute/execute.c (ft 5/5)

int		is_builtin(t_token *tree, char ***env, int *std);
void	exec_cmd(t_token *tree, char **env);
void	execute(t_token *tree, char ***env);

//----------------------------------------------------------------------------

#endif