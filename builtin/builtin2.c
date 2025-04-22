/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:43:25 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/18 11:26:39 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin.h"

//devo sempre tornare al nodo iniziale
int	ft_exit(t_token *tree, char **env)
{
	ft_printf("exit\n");
	if (num_argument(tree->next->next) != 0)
	{
		perror("too many arguments");
		exit_code(1);
		return (1);
	}
	free_lst(tree);
	freemtr(env);
	exit(ft_atoi(tree->next->str));
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
			i++;
		}
		tree = tree->next;
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
