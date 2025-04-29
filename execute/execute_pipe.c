/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/29 15:02:54 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	pipe_number(t_token *tree)
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

static void	other_command(t_token *tree, int *fd, char ***env, int *std)
{
	int	pid;

	dup2(fd[1], 1);
	if (redir_check(tree, 0, std, *env) == 1)
		return ;
	tree = find_comand(tree);
	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(tree, env, std) != 1)
			exec_cmd(tree, *env);
		return (freemtr(*env), free_lst(tree), close(fd[1]), close(fd[0]), \
		exit(0));
	}
	else
	{
		dup_file(fd[0], 0);
		close(fd[1]);
		dup2(std[1], 1);
	}
}

static int	last_command(int *std, t_token *tree, char ***env, int *fd)
{
	int	pid;

	dup2(std[1], 1);
	if (redir_check(tree, 0, std, *env) == 1)
		return (0);
	tree = find_comand(tree);
	if (tree == NULL)
		return (0);
	if (is_builtin(tree, env, std) == 1)
		return (reset_fd(std), close(fd[0]), close(fd[1]), 0);
	pid = fork();
	if (pid == 0)
		exec_cmd(tree, *env);
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (53550);
}

static void	exit_child(int ex, int w)
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
			other_command(tree, fd, env, std);
		else
			ex = last_command(std, tree, env, fd);
		tree = tree->next;
		while (tree && tree->prev->type != PIPE)
			tree = tree->next;
	}
	while (wait(&w) > 0)
		exit_child(ex, w);
	return (reset_fd(std));
}
//set follow-fork-mode child
//set detach-on-fork off