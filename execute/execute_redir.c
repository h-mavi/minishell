/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:05 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/23 11:54:03 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//funzione che crea l' heredoc e lo duplica nello stdin
void	heredoc(t_token *tree, int *std)
{
	int		file;
	char	*str;

	dup2(std[0], 0);
	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (perror("failed to open the file"), exit_code(1));
	write(0, "> ", 2);
	str = get_next_line(0);
	while (ctrl_str(str, tree->str) == 0)
	{
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
int	redir_check(t_token *tree, int n, int *std)
{
	int	file;

	while (tree != NULL && tree->type != PIPE)
	{
		if (tree->type == REDIR_1)
		{
			file = open(tree->str, O_RDONLY);
			n = file_control(file, 0);
		}
		else if (tree->type == HEREDOC)
			heredoc(tree, std);
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
