/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:56:13 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/01 15:18:34 by mbiagi           ###   ########.fr       */
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

//una statica in una struttura
char	**export_param(t_token *tree, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_calloc((ft_matrixlen(env) + 2), sizeof(char *));
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = (char *)tree->str;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	ft_export(char ***env, t_token *tree)
{
	if (control_variable(tree->str) == 1)
	{
		if (new_variable(tree->str, *env) == 1)
			*env = export_param(tree, *env);
		// else if (new_variable(tree->str, env) == 0)
		// 	*env = change_param(tree, *env);
	}
	return (1);
}

//una statica in una struttura
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

int	ft_unset(t_token *tree, char ***env)
{
	if (control_variable(tree->str) == 1)
	{
		if (new_variable(tree->str, *env) == 0)
			*env = unset_param(tree, *env);
		else
			perror("cazzi negri");
	}
	return (1);
}