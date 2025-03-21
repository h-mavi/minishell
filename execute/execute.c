/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:53:27 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/21 15:26:11 by mbiagi           ###   ########.fr       */
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

//funzione che esegue i comandi
void	exec_cmd(t_token *tree, char **env)
{
	char	*path;
	char	**arg;

	path = parse_cmd(ft_substr(argv[2 + fd.i + fd.here_d], till(\
	argv[2 + fd.i]), find_space(argv[2 + fd.i + fd.here_d])), env);
	arg = ft_split(argv[2 + fd.i + fd.here_d], ' ');
	if (!path)
		path = argv[2 + fd.i];
	execve(path, arg, env);//fare una funzione che ti calcoli il numero di opzioni e che te li mett in una matrice
	return (freemtr(arg), exit(1));
}

//funzione principale che richiama le altre
void	execute(t_token *tree, char **env)
{
	int	pid;

	if (pipe_check(tree) == 1)
		return (for_fork(tree));//da fare in modo che gestisca le pipe
	redir_check(*tree);
	pid = fork();
	if (pid == 0)
	{
		tree = find_comand(tree);
		exec_cmd(tree, env);
	}
}
