/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:56:13 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/25 15:14:21 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

int	ft_export(char **env, t_token tree)
{
	int		i;
	char	**new_env;
	char	**temp;

	i = 0;
	new_env = ft_calloc((ft_matrixlen(env) + 1), sizeof(char *));
	temp = new_env;
	while (env[i])
	{
		new_env[i] = ft_calloc(ft_strlen(env[i]), sizeof(char));
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_calloc(ft_strlen(tree.str), sizeof(char));
	new_env[i] = (char *)tree.str;
	new_env = temp;
	return (1);
}
