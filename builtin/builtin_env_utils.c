/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:37:35 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/17 12:38:11 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

char	**unset_param(t_token *tree, char **env)
{
	char	**new_env;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = ft_calloc(ft_matrixlen(env), sizeof(char *));
	temp = ft_strjoin(tree->str, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], temp, \
		ft_strlen(tree->str) + 1) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	free(temp);
	freemtr(env);
	return (new_env);
}

void	print_export(char **env)
{
	int		i;
	int		j;
	bool	n;

	i = -1;
	while (env[++i])
	{
		j = -1;
		n = 0;
		write(1, "declaire -x ", 12);
		while (env[i][++j])
		{
			write(1, &env[i][j], 1);
			if (env[i][j] == '=')
			{
				write(1, "\"", 1);
				n = 1;
			}
			if (env[i][j + 1] == '\0' && n == 1)
				write(1, "\"", 1);
		}
		write (1, "\n", 1);
	}
}

char	**change_param(t_token *tree, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc((ft_matrixlen(env) + 1), sizeof(char *));
	while (env[i])
	{
		if (ft_compare2(tree->str, env[i]) == 0)
		{
			if (tree->str[until(tree->str)] == '+')
				new_env[i] = ft_strjoin(env[i], \
				(tree->str + until(tree->str) + 2));
			else if (tree->str[until(tree->str)] == '=')
				new_env[i] = ft_strdup(tree->str);
			else
				new_env[i] = ft_strdup(env[i]);
		}
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (freemtr(env), new_env);
}

char	**export_param(t_token *tree, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_calloc((ft_matrixlen(env) + 2), sizeof(char *));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = string_control(tree->str);
	new_env[i + 1] = NULL;
	return (freemtr(env), new_env);
}
