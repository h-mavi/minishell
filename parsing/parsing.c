/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/26 10:33:22 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Controlla se la stringa datagli corrisponde ad un comando
int	check_if_cmd(char *orig, char **env)
{
	int		i;
	char	*cmd;
	char	*tmp;
	char	**path;

	i = -1;
	path = NULL;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = ft_split(env[i] + 5, ':');
	if (!path)
		return (2); //ERROR
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, orig);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (free(cmd), free_arr(path), 1);
		free(cmd);
	}
	free_arr(path);
	return (0);
}

//Crea i token
void	token_inator(char *cmd, char **env)
{
	char	**str;
	// t_token *head;
	int		i;

	i = -1;
	str = custom_split(cmd);
	if (!str)
	{
		printf("Syntax error, even number of \" or  \' \n");
		return ;
	}
	while (str[++i] != NULL)
	{
		if (check_if_cmd(str[i], env) == 1)
		{
			printf("'%s' e' un comando :D\n", str[i]);
			// set_cmd_data(head);
			// while (check_if_pipe(str[i]) != 1)
			// //puppa
			// ;
		}
		else
			printf("'%s' non e' un comando :(\n", str[i]);
		}
	free_arr(str);
}
