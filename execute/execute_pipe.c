/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/05/12 11:22:44 by mbiagi           ###   ########.fr       */
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

void	other_parent(t_token *tree, t_fds fds, char ***env)
{
	if (has_input_redir(tree) == 1 && is_real(tree, *env) == 1)
		dup2(fds.pipe[0], 0);
	return ((void) close(fds.pipe[0]), (void) close(fds.pipe[1]));
}

static void	other_command(t_token *tree, char ***env, t_fds fds, int *n)
{
	int	pid;

	if (has_input_redir(tree) == 1 && is_real(tree, *env) == 1)
		dup2(fds.pipe[1], 1);
	else
		trick();
	if (redir_check_pipe(tree, &n, fds) == 1)
		return (other_parent(tree, fds, env));
	tree = find_comand(tree);
	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		closeall(fds);
		if (is_builtin(tree, env, fds.std) != 1)
			exec_cmd(tree, *env);
		return (freemtr(*env), free_lst(tree), close(1), close(0), exit(0));
	}
	else
		other_parent(tree, fds, env);
}

static void	last_command(t_fds fds, t_token *tree, char ***env, int *n)
{
	int	pid;

	dup2(fds.std[1], 1);
	if (redir_check_pipe(tree, &n, fds) == 1)
		return ((void)close(fds.pipe[0]), (void)close(fds.pipe[1]));
	tree = find_comand(tree);
	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (ft_compare(tree->str, "exit") == 0)
			return (closeall(fds), ft_exit(tree, *env, fds.std), \
			freemtr(*env), close(1), close(0), free_lst(tree), exit(0));
		if (is_builtin(tree, env, fds.std) != 1)
			return (closeall(fds), exec_cmd(tree, *env));
		return (freemtr(*env), free_lst(tree), closeall(fds), close(1), \
		close(0), exit(0));
	}
	else
	{
		close(fds.pipe[0]);
		close(fds.pipe[1]);
	}
}

void	for_fork(t_token *tree, char ***env, t_fds fds)
{
	static int	n;
	int			npipe;
	int			p;
	int			w;

	w = 0;
	n = 0;
	npipe = -1;
	p = pipe_number(tree);
	open_heredoc(tree, &fds, *env);
	while (tree)
	{
		if (pipe(fds.pipe) == -1)
			return (perror("pipe failed"));
		if (++npipe < p)
			other_command(tree, env, fds, &n);
		else
			last_command(fds, tree, env, &n);
		tree = tree->next;
		while (tree && tree->prev->type != PIPE)
			tree = tree->next;
	}
	while (wait(&w) > 0)
		exit_code(w / 256);
	return (reset_fd(fds.std), closeall(fds));
}
