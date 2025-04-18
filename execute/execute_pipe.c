/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/18 10:17:50 by mbiagi           ###   ########.fr       */
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

void	other_command(t_token *tree, int *fd, char ***env)
{
	int	pid;

	file_control(fd[1], 1);
	if (redir_check(tree, 0) == 1)
		return ;
	tree = find_comand(tree);
	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(tree, env) != 1)
			exec_cmd(tree, *env);
		return (freemtr(*env), free_lst(tree), exit(1));
	}
}

void	last_command(int *std, t_token *tree, char ***env, int *ex)
{
	int	pid;

	*ex = 0;
	dup2(std[1], 1);
	if (redir_check(tree, 0) == 1)
		return ;
	tree = find_comand(tree);
	if (is_builtin(tree, env) == 1)
	{
		*ex = 0;
		return (reset_fd(std));
	}
	*ex = 53550;
	pid = fork();
	if (pid == 0)
		exec_cmd(tree, *env);
}

void	exit_child(int ex, int w)
{
	if (ex == 0)
		return ;
	else if (ex == 53550)
		exit_code(w / 256);
}

void	for_fork(t_token *tree, char ***env, int *std)
{
	int	fd[2];
	int	npipe;
	int	ex;
	int	p;
	int	w;

	w = 0;
	npipe = -1;
	p = pipe_number(tree);
	while (tree)
	{
		if (pipe(fd) == -1)
			return (perror("pipe failed"));
		if (++npipe < p)
			other_command(tree, fd, env);
		else
			last_command(std, tree, env, &ex);
		file_control(fd[0], 0);
		tree = tree->next;
		while (tree && tree->prev->type != PIPE)
			tree = tree->next;
	}
	while (wait(&w) > 0)
		exit_child(ex, w);
	reset_fd(std);
}
//set follow-fork-mode child
//set detach-on-fork off