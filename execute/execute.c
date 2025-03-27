/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:53:27 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/26 12:01:39 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execute.h"

//funzione che crea l' heredoc e lo duplica nello stdin
void	heredoc(t_token *tree)
{
	int		file;
	char	*str;

	file = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		return (perror("failed to open the file"));
	write(1, "> ", 2);
	str = get_next_line(0);
	while (control_str(str, tree->str) == 0)
	{
		ft_putstr_fd(str, file);
		free(str);
		write(1, "> ", 2);
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
//controllo su heredoc e pensa a come controllare se gli elementi sonon comandi
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
			heredoc(&tree);
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
			return (freemtr(path), command);
		free(command);
	}
	return (freemtr(path), NULL);
}

//crea una matrice con cmd e flag
char	**full_cmd(t_token *tree)
{
	t_token	*head;
	char	**mtr;
	int		option;
	int		i;

	i = 0;
	head = tree;
	option = 1;
	while(tree->next)
	{
		if (tree->type == FLAG || tree->type == COMMAND)
			option++;
		tree = tree->next;
	}
	mtr = ft_calloc(option, sizeof(char *));
	tree = head;
	while(tree->next)
	{
		if (tree->type == FLAG || tree->type == COMMAND)
			mtr[i++] = (char *)tree->str;
		tree = tree->next;
	}
	return (mtr);
}

//controllo se il comando e' una builtin e nel caso eseguo
int	is_builtin(t_token *tree, char **env)
{
//devono essere tutte int e non devo usare exit
	if (ft_strncmp(tree->str, "env", 3) == 0)
		return (ft_env(env));
	if (ft_strncmp(tree->str, "export", 7) == 0)
		return (ft_export(&env, tree));
	if (ft_strncmp(tree->str, "exit", 4) == 0)
		return (ft_exit(tree));
	if (ft_strncmp(tree->str, "echo", 4) == 0)
		return (ft_echo(tree));
	if (ft_strncmp(tree->str, "cd", 2) == 0)
		return (ft_cd(tree->next->str));
	if (ft_strncmp(tree->str, "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(tree->str, "unset", 5) == 0)
		return (ft_unset(tree, &env));
	return (0);
}

//funzione che esegue i comandi
void	exec_cmd(t_token *tree, char **env)
{
	char	*path;
	char	**arg;

	path = parse_cmd((char *)tree->str, env);
	arg = full_cmd(tree);
	if (!path)
		path = arg[0];
	execve(path, arg, env);
	perror("command not found");
	return (freemtr(arg), exit(1));
}

//funzione principale che richiama le altre
void	execute(t_token *tree, char **env)
{
	int	pid;
	int	std[2];

	std[0] = dup(0);
	std[1] = dup(1);
	// if (pipe_check(tree) == 1)
	// 	return (for_fork(tree));//PIPE CONTROL IS YET TO BE DONE
	redir_check(*tree);
	tree = find_comand(tree);
	if (is_builtin(tree, env) == 1)
		return (reset_fd(std));
	pid = fork();
	if (pid == 0)
		exec_cmd(tree, env);
	reset_fd(std);
}

int main(int arc, char **arg, char **env)
{
	t_token	*tree;
	int		i;

	i = 0;
	if (arc < 3)
	{
		printf("MA SEI UN COGLIONE?!?!?!");
		exit(1);
	}
	tree = ft_calloc(arc + 1, sizeof(t_token));
	while (arg[++i])
	{
		if (i == 1)
			tree[i].type = REDIR_1;
		else if (i == 2)
			tree[i].type = REDIR_2;
		else if (i == 3)
			tree[i].type = COMMAND;
		else
			tree[i].type = FLAG;
		tree[i].str = arg[i];
		tree[i].next = &tree[i + 1];
		tree[i].prev = &tree[i - 1];
	}
	execute(&tree[1], env);
	// ft_env(env);
	return (0);
}
//cc execute/execute.c execute/execute_utils.c builtin/builtin.c builtin/builtin_env.c libft/libft.a get_next_line/libget_next_line.a -g