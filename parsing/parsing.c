/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/01 09:05:50 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Serve a togliere gli apici, le virgolette e i back-slash inutili */
char	*rm_app(char *s)
{
	int		i;
	int		x;
	int 	len;
	char	*new;

	i = -1;
	len = 0;
	while (s[++i])
		if ((werami(s, i) != 0 && s[i] != 92) || ((werami(s, i) == 0 || \
		s[i] == 92) && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			len++;
	i = -1;
	x = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	while (s[++i])
		if ((werami(s, i) != 0 && s[i] != 92) || ((werami(s, i) == 0 || \
		s[i] == 92) && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			new[x++] = s[i];
	new[x] = '\0';
	return (free(s), new);
}

/* Controlla se ci sono variabili da espandere e, nel caso sia necessario, toglie apici e virgolette. */
char *refine(char *s)
{
	int	i;

	i = -1;
	s = rm_app(s);
	while (s[++i])
	{
		// if (s[i + 1] > '$' &&  s[i + 2] > 64 && s[i + 2] < 91 && ((s[i] == '"') || (werami(s, i) == -1)))
		// 	espand(s);//funzione da fare
	}
	return (s);
}

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
