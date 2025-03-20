/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/03/20 10:24:15 by mfanelli         ###   ########.fr       */
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
	int		i = -1;
	
	(void)env;
	str = custom_split(cmd);
	if (!str)
	{
		printf("wtf\n");
		return ;
	}
	while (str[++i] != NULL)
		printf("%s\n", str[i]);
	free_arr(str);
	// if (check_if_cmd(cmd, env) == 1)
	// 	printf("'%s' e' un comando, wow!!\n", cmd);
	// else
	// 	printf("'%s' non e' un comando :(\n", cmd);
}