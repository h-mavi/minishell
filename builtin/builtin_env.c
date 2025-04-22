/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:56:13 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/17 12:37:52 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	ft_env(t_token *tree, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (num_argument(tree->next) != 0)
		return (perror("too many argument"), exit_code(1), 1);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				ft_printf("%s\n", env[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_export(char ***env, t_token *tree)
{
	if (tree == NULL)
		return (print_export(*env), 1);
	while (tree)
	{
		if (tree->type == FLAG)
		{
			if (control_variable(tree->str) == 1)
			{
				if (new_variable(tree->str, *env) == 1)
					*env = export_param(tree, *env);
				else
					*env = change_param(tree, *env);
			}
		}
		tree = tree->next;
	}
	return (1);
}

int	ft_unset(t_token *tree, char ***env)
{
	while (tree)
	{
		if (tree->type == FLAG)
		{
			if (control_variable(tree->str) == 1)
			{
				if (new_variable(tree->str, *env) == 0)
					*env = unset_param(tree, *env);
			}
		}
		tree = tree->next;
	}
	return (1);
}
