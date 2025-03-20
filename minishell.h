/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:18:52 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/20 09:08:18 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

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

typedef struct s_token
{
	int				type;
	const char		*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

#endif