/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:43 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/15 10:27:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

//devo sempre tornare al nodo iniziale
int	ft_exit(t_token *tree, char **env)
{
	free_lst(tree);
	freemtr(env);
	exit(0);
	return (1);
}

int	ft_pwd()
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
	return (1);
}

int	num_argument(t_token *tree)
{
	int	i;

	i = 0;
	while (tree && tree->type != PIPE)
	{
		if (tree->type == FLAG)
			return(1);
		i++;
		tree = tree->next;
	}
	return (0);
}

void	change_dir(char **env, char *temp)
{
	int		i;
	char	*temp2;

	i = 0;
	temp2 = getcwd(NULL, 0);
	while (env[i])
	{
		if (ft_compare(env[i], "PWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", temp2);
			free(temp2);
		}
		else if (ft_compare(env[i], "OLDPWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", temp);
			free(temp);
		}
		i++;
	}
}

int	ft_cd(t_token *tree , char **env)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (tree == NULL || tree->type == PIPE)
	{
		if (chdir("/home/cormax") == -1)//sbagliato eh
			return (perror("no such directory"), free(temp), exit_code(127), 1);
		change_dir(env, temp);
		return (1);
	}
	if (num_argument(tree->next) != 0)
		return (perror("too many argument"), free(temp), exit_code(1), 1);
	if (chdir(tree->str) == -1)
		return (perror("no such directory"), free(temp), exit_code(127), 1);
	change_dir(env, temp);
	return (1);
}

int	is_n(const char *str, char c)
{
	int		i;
	char	*cmp;

	i = 0;
	cmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		cmp[i] = c;
		i++;
	}
	if (ft_strncmp(str, cmp, ft_strlen(cmp)) == 0)
		return (free(cmp), 0);
	return (free(cmp), 1);
}

void	print_option(t_token *tree)
{
	int	i;

	i = 0;
	while (tree && tree->type != PIPE)
	{
		if (tree->type == FLAG)
		{
			if (i != 0)
				ft_printf(" ");
			if (tree->str[0] == '$' && tree->str[1] == '?' && \
			tree->str[2] == '\0')
				exit_code(1000);
			else
				ft_printf("%s", tree->str);
		}
		tree = tree->next;
		i++;
	}
}

int	ft_echo(t_token *tree)
{
	bool	n;

	n = 1;
	while (tree->type != FLAG && tree->type != PIPE && tree->next)
		tree = tree->next;
	while (tree && tree->str[0] == '-' && tree->str[1] == 'n' && \
	is_n(&tree->str[1], 'n') == 0)
	{
		n = 0;
		tree = tree->next;
	}
	print_option(tree);
	if (n == 1)
		ft_printf("\n");
	return (1);
}
