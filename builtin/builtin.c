/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:43 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/19 13:41:48 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exit(struttura)
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
}

void	ft_cd(const char	*dir)
{
	if(chdir(dir) == -1)
		perror("no such directory");
}