/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:05 by mbiagi            #+#    #+#             */
/*   Updated: 2025/05/05 15:09:49 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*simple_refine(char *s, char **env)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		i = do_skip(s, i);
		if (s[i] == '$' && werami(s, i, 0, 0) == -1 && werami(s, i + 1, 0, 0) == -1 && \
			((ft_isalpha(s[i + 1]) != 0) || (s[i + 1] == '_')))
			s = esp_special_case(s, env, i);
		else if (s[i] == '$' && werami(s, i + 1, 0, 0) == 0 && werami(s, i, 0, 0) == -1)
		{
			s = rm_dollar(s);
			if (i > 0)
				i -= 1;
		}
		if (werami(s, i, 0, 0) == 0 && werami(s, i + 1, 0, 0) == 1)
		{
			i++;
			while (werami(s, i, 0, 0) != 0)
			{
				i = do_skip(s, i);
				if (s[i] == '$' && s[0] == '<' && s[1] == '<')
					i++;
				if ((s[i] == '$' && werami(s, i, 0, 0) == 1 && \
					((ft_isalpha(s[i + 1]) != 0) || (s[i + 1] == '_'))))
				{
					s = esp_special_case(s, env, i);
					i -= 1;
				}
				i++;
			}
		}
		i = do_skip(s, i);
		if (s[0] == '\0')
			return (s);
	}
	return (s);
}

//funzione che crea l' heredoc e lo duplica nello stdin
void	heredoc(t_token *tree, int *std, char **env)
{
	int		file;
	char	*str;

	dup2(std[0], 0);
	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (perror("failed to open the file"), (void)exit_code(1));
	write(0, "> ", 2);
	signal(SIGQUIT, test);
	signal(SIGINT, test);
	str = get_next_line(0);
	if (sigal == 1)
		dup2(std[0], 0);
	while (ctrl_str(str, tree->str) == 0)
	{
		if (tree->type == HEREDOC)
			str = simple_refine(str, env);
		ft_putstr_fd(str, file);
		free(str);
		write(0, "> ", 2);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(file);
	close(file);
	file = open("here_doc", O_RDWR, 0777);
	file_control(file, 0);
	unlink("here_doc");
}

//redirige i file
int	redir_check(t_token *tree, int n, int *std, char **env)
{
	int	file;

	while (tree != NULL && tree->type != PIPE)
	{
		if (tree->type == REDIR_1)
		{
			file = open(tree->str, O_RDONLY);
			n = file_control(file, 0);
		}
		else if ((tree->type == HEREDOC || tree->type == HEREDOC_2) && sigal == 0)
			heredoc(tree, std, env);
		else if (tree->type == REDIR_2 || tree->type == REDIR_3)
		{
			if (tree->type == REDIR_2)
				file = open(tree->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			else if (tree->type == REDIR_3)
				file = open(tree->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
			n = file_control(file, 1);
		}
		if (n == 1 && tree->type != COMMAND && tree->type != FLAG)
			return (1);
		tree = tree->next;
	}
	return (0);
}

void	ctrl_c_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		sigal = 1;
	}
}
