/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:11:12 by mbiagi            #+#    #+#             */
/*   Updated: 2025/05/07 18:01:37 by mbiagi           ###   ########.fr       */
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

int	check_redir_out(t_token *tree, int file)
{
	if (tree->type == REDIR_2)
		file = open(tree->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (tree->type == REDIR_3)
		file = open(tree->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file_control(file, 1) == 1)
		return (1);
	return (0);
}

int	redir_check_pipe(t_token *tree, int **n, t_fds fds)
{
	int	file;

	while (tree != NULL && tree->type != PIPE)
	{
		if (tree->type == REDIR_1)
		{
			file = open(tree->str, O_RDONLY);
			if (file_control(file, 0) == 1)
				return (1);
		}
		else if ((tree->type == HEREDOC || tree->type == HEREDOC_2) && \
		g_sigal == 0)
		{
			if (file_control(fds.heredoc[**n], 0) == 1)
				return (1);
			(**n)++;
		}
		else if (tree->type == REDIR_2 || tree->type == REDIR_3)
			if (check_redir_out(tree, file) == 1)
				return (1);
		tree = tree->next;
	}
	return (0);
}

void	closeall(t_fds fds)
{
	int	i;

	i = 0;
	close(fds.pipe[0]);
	close(fds.pipe[1]);
	close(fds.std[0]);
	close(fds.std[1]);
	while (fds.heredoc[i] != 0)
	{
		close(fds.heredoc[i]);
		i++;
	}
}

static int	has_input_redir(t_token *tree)
{
	while (tree->type != PIPE)
		tree = tree->next;
	tree = tree->next;
	while (tree != NULL && tree->type != PIPE)
	{
		if (tree->type == REDIR_1 || tree->type == HEREDOC || \
			tree->type == HEREDOC_2)
			return (0);
		tree = tree->next;
	}
	return (1);
}

void	trick(void)
{
	int	null;

	null = open("/dev/null", O_WRONLY);
	dup2(null, 1);
	close(null);
}

static void	other_command(t_token *tree, char ***env, t_fds fds, int *n)
{
	int	pid;

	if (has_input_redir(tree) == 1)
		dup2(fds.pipe[1], 1);
	else
		trick();
	if (redir_check_pipe(tree, &n, fds) == 1)
		return ;
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
	{
		if (has_input_redir(tree) == 1)
			dup2(fds.pipe[0], 0);
		return((void)close(fds.pipe[0]), (void)close(fds.pipe[1]));
	}
}

static void	last_command(t_fds fds, t_token *tree, char ***env, int *n)
{
	int	pid;

	dup2(fds.std[1], 1);
	if (redir_check_pipe(tree, &n, fds) == 1)
		return ;
	tree = find_comand(tree);
	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (ft_compare(tree->str, "exit") == 0)
			return (ft_exit(tree, *env, fds.std), freemtr(*env), close(1), \
			close(0), free_lst(tree), closeall(fds), exit(0));
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

void	open_heredoc(t_token *tree, t_fds *fds, char **env)
{
	int		file;
	char	*str;
	int		i;

	i = 0;
	fds->heredoc[0] = 0;
	while (tree != NULL && g_sigal == 0)
	{
		if (tree->type != HEREDOC && tree->type != HEREDOC_2)
		{
			tree = tree->next;
			continue ;
		}
		file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			return (perror("failed to open the file"), (void)exit_code(1));
		write(0, "> ", 2);
		signal(SIGQUIT, test);
		signal(SIGINT, test);
		str = get_next_line(0);
		if (g_sigal == 1)
			dup2(fds->std[0], 0);
		heredoc_while(tree, str, env, file, fds->std[0]);
		get_next_line(file);
		close(file);
		file = open("here_doc", O_RDWR, 0777);
		unlink("here_doc");
		fds->heredoc[i] = file;
		tree = tree->next;
		i++;
	}
	fds->heredoc[i] = 0;
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

void	heredoc_while(t_token *tree, char *str, char **env, int file, int std)
{
	while (ctrl_str(str, tree->str) == 0)
	{
		if (tree->type == HEREDOC)
			str = simple_refine(str, env);
		ft_putstr_fd(str, file);
		free(str);
		write(0, "> ", 2);
		str = get_next_line(0);
		if (g_sigal == 1)
			dup2(std, 0);
	}
	free(str);
}
