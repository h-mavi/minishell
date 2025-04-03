/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_controls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:34:02 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/02 10:51:43 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	control_variable(const char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]) != 0 || var[0] == '=')
		return (perror("not valid identifier"), 0);
	if (var[0] == '_' && var[1] == '=')
		return (0);
	while (var[i] != '=' && var[i] != '+')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '\0')
			return (perror("not valid identifier"), 0);
		i++;
	}
	if (var[i] == '+' && var[i + 1] != '=')
		return (perror("not valid identifier"), 0);
	return (1);
}

int	new_variable(const char *var, char **env)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	while (var[n] != '=' && var[n] != '\0' && var[n] != '+')
		n++;
	str = ft_calloc(n + 1, sizeof(char));
	while (i != n)
	{
		str[i] = var[i];
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (ft_compare(env[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}
