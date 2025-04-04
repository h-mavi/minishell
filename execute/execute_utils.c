/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:59:35 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/03 10:54:49 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execute.h"

//funzione di ausilio per trovarmi subito il comando
t_token	*find_comand(t_token *tree)
{
	while (tree->type != COMMAND)
		tree = tree->next;
	return(tree);
}

//funzione di  ausilio per duplicare e chiudere i file
void	dup_file(int file, int std)
{
	dup2(file, std);
	close(file);
}

//controlla la presenza di pipe nella stringa di comando
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

//protegge gli open
void	file_control(t_token *tree, int file, int std)
{
	(void)tree;
	if (file == -1)
	{
		// free_list(tree);//da creare ancora
		perror("filed to open the file");
		exit(1);//da cambiare per non far chiudere minishell
	}
	dup_file(file, std);
}

//controlla il limiter dell' heredoc
int	control_str(char *str, const char *limiter)
{
	if (str == NULL)
		return (1);
	if ((ft_strncmp(str, limiter, ft_strlen(limiter)) == 0) && \
	str[ft_strlen(limiter)] == '\n')
		return (1);
	return (0);
}

//funzione ausiliaria che libera la matrice
void	freemtr(char **mtr)
{
	int	i;

	i = 0;
	while (mtr[i])
	{
		free(mtr[i]);
		i++;
	}
	free(mtr[i]);
	free(mtr);
}

//funzione ausiliaria che ripristina le stdfds
void	reset_fd(int *std)
{
	dup2(std[0], 0);
	dup2(std[1], 1);
	close(std[0]);
	close(std[1]);
}

//funzione ausiliaria ch emi serve per comparare il nome dei comandi alle builtin
int	ft_compare(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] == '=' && s2[i] == '\0')
		return (0);
	if (s1[i] != s2[i])
		return (1);
	else
		return (0);
}

int	ft_compare2(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=' && s2[i] != '=' && s2[i] != '+')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if ((s1[i] == '=' || s1[i] == '+') && s2[i] == '_')
		return (0);
	if (s1[i] != s2[i])
		return (1);
	else
		return (0);
}
