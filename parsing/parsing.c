/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/02 12:52:17 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Controlla se ci sono variabili da espandere e, nel caso sia necessario, toglie apici e virgolette. */
char *refine(char *s, char **env)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	while (s[++i])
	{
		if (s[i] == '$' && werami(s, i) == -1 && werami(s, i + 1) == -1 && \
			((ft_isalpha(s[i + 1]) != 0) || (s[i + 1] == '_')))
			s = espand(s, env);
		else if(s[i] == '"' && s[i + 1] == '$' && \
			((ft_isalpha(s[i + 2]) != 0) || (s[i + 2] == '_')))
		{
			s = rm_app(s);
			s = espand(s, env);
			x++;
		}
		else if (s[i] == '$' && werami(s, i + 1) == 0 && werami(s, i) == -1)
			s = rm_dollar(s);
	}
	if (x == 0)
		s = rm_app(s);
	return (s);
}

/* Controlla se la stringa datagli corrisponde ad un comando */
int	check_if_cmd(char *orig, char **env)
{
	int		i;
	char	*cmd;
	char	*tmp;
	char	**path;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
	}
	if (!path)
		return (-1); //ERROR
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, orig);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (free(cmd), free_arr(path), COMMAND);
		free(cmd);
	}
	return (free_arr(path), 0);
}
