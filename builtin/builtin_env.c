/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:56:13 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/28 09:46:40 by mbiagi           ###   ########.fr       */
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
	new_env[i] = (char *)tree->next->str;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	ft_export(char ***env, t_token *tree)
{
	*env = export_param(tree, *env);
	return (1);
}

//da capire come liberare env e capire la questione puntatori per cambiare env
//una statica in una struttura?
char	**unset_param(t_token *tree, char **env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = ft_calloc(ft_matrixlen(env), sizeof(char *));
	while (env[i])
	{
		if (ft_strncmp(env[i], tree->next->str, \
		ft_strlen(tree->next->str)) != 0)
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = env[i];
	return (new_env);
}

int	ft_unset(t_token *tree, char ***env)
{
	*env = unset_param(tree, *env);
	return (1);
}