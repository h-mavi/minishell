/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:43 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/25 15:52:08 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

//RITORNARE UN VALORE DIVERSO IN CASO DI ERRORE
int	ft_exit(t_token *tree)
{
	(void)tree;
	//liberare la stuttura e tutte cose
	exit(0);
	return (1);
}

int	ft_pwd()
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (1);
}

int	ft_cd(const char	*dir)
{
	if(chdir(dir) == -1)
		perror("no such directory");
	return (1);
}

int	ft_echo(t_token *tree)
{
	printf("%s", tree->next->str);
	return (1);
}
