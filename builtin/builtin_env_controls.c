/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_controls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:34:02 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/01 17:04:14 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	control_variable(const char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]) != 0)
		return (perror("not valid identifier"), 0);
	if (var[0] == '_' && var[1] == '=')
		return (0);
	while (var[i] != '=' && var[i] != '+')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '\0')
		{
			perror("not valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

int	new_variable(const char *var, char **env)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (var[n] != '=' && var[n] != '\0')
		n++;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, n) == 0)
			return (0);
		i++;
	}
	return (1);
}
