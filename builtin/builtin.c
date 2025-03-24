/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:43 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/24 13:43:03 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//RITORNARE UN VALORE DIVERSO IN CASO DI ERRORE
void	ft_exit(t_token *tree)
{
	//liberare la stuttura e tutte cose
	exit(0);
}

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	exit(0);
}

void	ft_cd(const char	*dir)
{
	if(chdir(dir) == -1)
		perror("no such directory");
	exit(0);
}

void	ft_echo(t_token *tree)
{
	printf("%s", tree->str);
	exit(0);
}
