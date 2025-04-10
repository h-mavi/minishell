/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/10 13:49:04 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execute.h"

int	pipe_number(t_token *tree)
{
	int	i;

	i = 0;
	while (tree)
	{
		if (tree->type == PIPE)
			i++;
		tree = tree->next;
	}
	return (i);
}

void	for_fork(t_token *tree, char ***env, int *std)
{
	int	fd[2];
	int	pid;
	int	npipe;
	int	p;

	npipe = 0;
	p = pipe_number(tree);
	while (tree)
	{
		if (pipe(fd) == -1)
		return (perror("pipe failed"), exit_code(1));
		if (npipe != 0)
			file_control(tree, fd[0], 0);
		if (npipe < p)
		{
			file_control(tree, fd[1], 1);
			redir_check(tree);
			tree = find_comand(tree);
			pid = fork();
			if (pid == 0)
			{
				if (is_builtin(tree, env) != 1)
					exec_cmd(tree, *env);
				return (freemtr(*env), exit (0));
			}
		}
		else
		{
			redir_check(tree);
			tree = find_comand(tree);
			if (is_builtin(tree, env) == 1)
				return (reset_fd(std));
			pid = fork();
			if (pid == 0)
				exec_cmd(tree, *env);
		}
		npipe++;
		tree = tree->next;
		while (tree && tree->prev->type != PIPE)
			tree = tree->next;
		reset_fd(std);
	}
	reset_fd(std);
}
//set follow-fork-mode child
//set detach-on-fork off