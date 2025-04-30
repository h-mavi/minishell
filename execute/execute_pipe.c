/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/30 09:02:38 by mbiagi           ###   ########.fr       */
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

static void	last_command(int *std, t_token *tree, char ***env, int *fd)
{
	int	pid;

	dup2(std[1], 1);
	if (redir_check(tree, 0, std, *env) == 1)
		return ;
	tree = find_comand(tree);
	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (ft_compare(tree->str, "exit") == 0)
			return (ft_exit(tree, *env, std), freemtr(*env), \
			free_lst(tree), close(fd[1]), close(fd[0]), exit(0));
		if (is_builtin(tree, env, std) != 1)
			exec_cmd(tree, *env);
		return (freemtr(*env), free_lst(tree), close(fd[1]), close(fd[0]), \
		exit(0));
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	for_fork(t_token *tree, char ***env, int *std)
{
	int	fd[2];
	int	npipe;
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
			last_command(std, tree, env, fd);
		tree = tree->next;
		while (tree && tree->prev->type != PIPE)
			tree = tree->next;
	}
	while (wait(&w) > 0)
		exit_code(w / 256);
	return (reset_fd(std));
}
//set follow-fork-mode child
//set detach-on-fork off