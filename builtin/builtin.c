/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:43 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/02 14:36:25 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

//RITORNARE UN VALORE DIVERSO IN CASO DI ERRORE
int	ft_exit(t_token *tree)
{
	(void)tree;
	//liberare la stuttura e tutte cose
	exit(0);
	return (1);
}

int	ft_pwd()
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (1);
}

int	ft_cd(const char	*dir, char **env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = getcwd(NULL, 0);
	if (chdir(dir) == -1)
		perror("no such directory");
	while (env[i])
	{
		if (ft_compare(env[i], "PWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		else if (ft_compare(env[i], "OLDPWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", temp);
		}
		i++;
	}
	return (1);
}

int	is_n(const char *str, char c)
{
	int		i;
	char	*cmp;

	i = 0;
	cmp = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		cmp[i] = c;
		i++;
	}
	if (ft_strncmp(str, cmp, ft_strlen(cmp)) == 0)
		return (free(cmp), 0);
	return (free(cmp), 1);
}

int	ft_echo(t_token *tree)
{
	bool	n;

	n = 1;
	if (tree->str[0] == '-' && tree->str[1] == 'n' && \
	is_n(&tree->str[1], 'n') == 0)
	{
		n = 0;
		tree = tree->next;
	}
	printf("%s", tree->str);
	tree = tree->next;
	while (tree->next)
	{
		if (tree->type == FLAG)
			printf(" %s", tree->str);
		tree = tree->next;
	}
	if (n == 1)
		printf("\n");
	return (1);
}
