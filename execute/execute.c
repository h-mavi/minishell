/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:53:27 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/24 15:40:01 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "execute.h"

//funzione che crea l' heredoc e lo duplica nello stdin
void	heredoc(t_token *tree)
{
	int		file;
	char	*str;

	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (file);
	write(1, "> ", 15);
	str = get_next_line(0);
	while (control_str(str, tree->str) == 0)
	{
		ft_putstr_fd(str, file);
		free(str);
		write(1, "> ", 15);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(file);
	close(file);
	file = open("here_doc", O_RDWR, 0777);
	file_control(tree, file, 0);
	unlink("here_doc");
}

//redirige i file
void	redir_check(t_token tree)
{
	int	file;

	while (tree.next)
	{
		if (tree.type == REDIR_1)
		{
			file = open(tree.str, O_RDONLY);
			file_control(&tree, file, 0);
		}
		else if (tree.type == REDIR_2)
		{
			file = open(tree.str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			file_control(&tree, file, 1);
		}
		else if (tree.type == REDIR_3)
		{
			file = open(tree.str, O_WRONLY | O_CREAT | O_APPEND , 0777);
			file_control(&tree, file, 1);
		}
		else if (tree.type == HEREDOC)
			heredoc(&tree);//controllo su heredoc e pensa a come controllare se gli elementi sonon comandi
		tree = *(tree.next);
	}
}

//funzione che trova il path corretto del cmd, se non lo trova retituisce NULL
char	*parse_cmd(char *argv, char **env)
{
	int		i;
	char	*command;
	char	**path;
	char	*temp;

	i = -1;
	path = NULL;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = ft_split(env[i] + 5, ':');
	if (!path)
		return (argv);
	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		command = ft_strjoin(temp, argv);
		free(temp);
		if (access(command, F_OK) == 0)
			return (free(argv), freemtr(path), command);
		free(command);
	}
	return (free(argv), freemtr(path), NULL);
}

//crea una matrice con cmd e flag
char	**full_cmd(t_token tree)
{
	t_token	head;
	char	**mtr;
	int		option;
	int		i;

	i = 0;
	head = tree;
	option = 0;
	while(tree.next)
	{
		if (tree.type == FLAG)
			option++;
		tree = *(tree.next);
	}
	mtr = ft_calloc(option, sizeof(char *));
	head = tree;
	while(tree.next)
	{
		if (tree.type == FLAG)
		{
			mtr[i++] = ft_calloc(ft_strlen(tree.str), sizeof(char));
			ft_strlcpy(mtr[i], tree.str, ft_strlen(tree.str));
		}
		tree = *(tree.next);
	}
}//non e' detto che funzioni al 100%

//controllo se il comando e' una builtin e nel caso eseguo
void	is_builtin(t_token *tree, char **env)
{
	if (ft_strncmp(tree->str, "env", 3) == 0)
		ft_env(env);
	if (ft_strncmp(tree->str, "export", 7) == 0)
		ft_export(env, *(tree));
	if (ft_strncmp(tree->str, "exit", 4) == 0)
		ft_exit(tree);
	if (ft_strncmp(tree->str, "echo", 4) == 0)
		ft_echo(tree);
	if (ft_strncmp(tree->str, "cd", 2) == 0)
		ft_cd(tree->str);
	if (ft_strncmp(tree->str, "pwd", 3) == 0)
		ft_pwd();
}

//funzione che esegue i comandi
void	exec_cmd(t_token *tree, char **env)
{
	char	*path;
	char	**arg;

	is_builtin(tree, env);
	path = parse_cmd(tree->str, env);
	arg = full_cmd(*tree);
	if (!path)
		path = arg[0];
	execve(path, arg, env);
	perror("command not found");
	return (freemtr(arg), exit(1));
}//devo controllare che i comandi non siano builtin

//funzione principale che richiama le altre
void	execute(t_token *tree, char **env)
{
	int	pid;

	if (pipe_check(tree) == 1)
		return (for_fork(tree));//PIPE CONTROL IS YET TO BE DONE
	redir_check(*tree);
	pid = fork();
	if (pid == 0)
	{
		tree = find_comand(tree);
		exec_cmd(tree, env);
	}
}
