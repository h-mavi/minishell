/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:03:23 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/07 09:50:33 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../builtin/builtin.h"

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

void	dup_file(int file, int std);
int		pipe_check(t_token *tree);
void	file_control(t_token *tree, int file, int std);
void	heredoc(t_token *tree);
t_token	*find_comand(t_token *tree);
int		control_str(char *str, const char *limiter);
void	freemtr(char **mtr);
void	reset_fd(int *std);
int		ft_compare(const char *s1, const char *s2);
int		ft_compare2(const char *s1, const char *s2);

#endif