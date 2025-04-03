/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:56:13 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/03 11:51:27 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

int	ft_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				printf("%s\n", env[i]);
				break;
			}
			j++;
		}
		
		i++;
	}
	return (1);
}

void	print_export(char **env)
{
	int		i;
	int		j;
	char	c; 

	i = 0;
	c = '"';
	while (env[i])
	{
		j = 0;
		write(1, "declaire -x ", 12);
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			if (env[i][j] == '=')
				write(1, &c, 1);
			if (env[i][j + 1] == '\0')
				write(1, &c, 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
	}
}

//funzione che controlla la presenza di "+=" e nel caso leva il '+'
//usata nel caso la variabile che cerchiamo di aggiungere non eista
char	*string_control(const char *str)
{
	int		i;
	int		j;
	char	*nstr;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] != '+')
		return (ft_strdup(str));
	i = 0;
	nstr = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		if (str[i] != '+')
		{
			nstr[j] = str[i];
			j++;
		}
		i++;
	}
	return (nstr);
}

size_t	until(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '+' && str[i] != '\0')
		i++;
	return (i);
}

char	**change_param(t_token *tree, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc((ft_matrixlen(env) + 1), sizeof(char *));
	while (env[i])
	{
		if (ft_compare2(env[i], tree->str) == 0)
		{
			if (tree->str[until(tree->str)] == '+')
				new_env[i] = ft_strjoin(env[i], (tree->str + until(tree->str) + 2));
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

int	ft_export(char ***env, t_token *tree)
{
	if (tree == NULL)
		return (print_export(*env), 1);
	if (control_variable(tree->str) == 1)
	{
		if (new_variable(tree->str, *env) == 1)
			*env = export_param(tree, *env);
		else if (new_variable(tree->str, *env) == 0)
			*env = change_param(tree, *env);
	}
	return (1);
}

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