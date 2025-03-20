/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:53:27 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/20 17:01:35 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	pipe_check(t_token *tree)
{
	while (tree->next)
	{
		if (tree->type != PIPE)
			return (1);
		tree = tree->next;
	}
	return (0);
}

void	redir_check(t_token *tree)
{
	int	file;

	while (tree->next)
	{
		if (tree->type == REDIR_1)
		{
			file = open(tree->str, O_RDONLY);
			dup2(file, 0);
			close(file);
		}
		else if (tree->type == REDIR_2)
		{
			file = open(tree->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(file, 1);
			close(file);
		}
		else if (tree->type == REDIR_3)
		{
			file = open(tree->str, O_WRONLY | O_CREAT | O_APPEND , 0777);
			dup2(file, 1);
			close(file);
		}
		else if (tree->type == HEREDOC)
			here_doc(tree->next->str);//controllo su heredoc e pensa a come controllare se gli elementi sonon comandi
	}
}

void	for_fork(t_token *tree)
{
	
}

void	execute(t_token *tree, char **env)
{
	int	pid;

	if (pipe_check(tree) == 1)
		return (for_fork(tree));
	redir_check(tree);
	pid = fork();
	if (pid == 0)
	{
		
	}
}
