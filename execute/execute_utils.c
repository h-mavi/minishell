/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:59:35 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/23 15:22:03 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//funzione che serve a gestire gli exit code
void	exit_code(int n)
{
	static int	code = 0;

	if (n == 1000)
	{
		ft_printf("%d", code);
		exit_code(0);
	}
	else
		code = n;
}

//funzione di ausilio per trovarmi subito il comando
t_token	*find_comand(t_token *tree)
{
	while (tree != NULL && tree->type != PIPE)
	{
		if (tree->type == COMMAND)
			break;
		tree = tree->next;
	}
	if (tree != NULL)
		if (tree->type == COMMAND)
			return (tree);
	return (NULL);
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
		if (tree->type == PIPE)
			return (1);
		tree = tree->next;
	}
	return (0);
}

//protegge gli open
int	file_control(int file, int std)
{
	if (file == -1)
	{
		// free_lst(tree);
		perror("filed to open the file");
		exit_code(1);
		return (1);
	}
	dup_file(file, std);
	return (0);
}
