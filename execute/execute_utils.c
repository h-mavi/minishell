/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:59:35 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/21 10:32:27 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
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
	if (file == -1)
	{
		free_list(tree);//da creare ancora
		perror("filed to open the file");
		exit(1);
	}
	dup_file(file, std);
}

//controlla il limiter dell' heredoc
int	control_str(char *str, char *limiter)
{
	if (str == NULL)
		return (1);
	if ((ft_strncmp(str, limiter, ft_strlen(limiter)) == 0) && \
	str[ft_strlen(limiter)] == '\n')
		return (1);
	return (0);
}
