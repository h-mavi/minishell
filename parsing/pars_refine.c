/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_refine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:02:23 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/04 19:21:19 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Funzione chiamata da rm_spaces che serve per riscrivere la stringa senza gli spazi in mezzo ai
redir e il loro limiter. */
char *rewrite(char *orig, int i, int x)
{
	int	y;
	char *dest;

	y = -1;
	dest = (char *)ft_calloc(sizeof(char), (ft_strlen(orig) - x) + 1);
	while (orig[++y])
	{
		dest[y] = orig[y];
		if (i == y)
		{
			while (orig[++y + x])
				dest[y] = orig[y + x];
			// y++;
			dest[y] = '\0';
			break ;
		}
	}
	free(orig);
	return (dest);
}

/* Controlla se ci sono casi di redirection, heredoc o pipe attaccati. Nel caso ci siano li
divide con uno spazio tramite la funzione divide, in modo che poi il custom_split
possa dividerli in nodi seprarati.*/
char *here_glued(char *s)
{
	int	x;

	x = -1;
	while (s[++x])
		if ((((x != 0 && s[x] != ' ' && find_char(s, x) == 0 && \
			werami(s, x) == -1) || (s[x] == 39 || s[x] == 34)) && \
			find_char(s, x + 1) != 0 && find_char(s, x + 1) != 3) || (x != 0 && find_char(s, x) == 3 && \
			werami(s, x) == -1 && find_char(s, x - 1) != 3 && find_char(s, x + 1) != 3 && ((s[x - 1] != ' ') || \
			(s[x + 1] != ' ' && s[x + 1] != '\0')) && x != 0))
				s = divide(s, x);
	return (s);
}

/* Funzione richiamata in refine che espande le variabili di sistema */
char	*espand(char *s, char **env)
{
	int		i;
	char 	*tmp;
	char	*path;
	char	*end;

	i = -1;
	path = NULL;
	if (find_dollar(s, 0) != -1)
		tmp = ft_strchr(s, '$') + 1;
	else
		tmp = s;
	while (env[++i])
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
			path = ft_strdup(env[i] + ft_strlen(tmp) + 1);
	if (!path)
	{
		path = (char *)ft_calloc(1, sizeof(char));
		path[0] = '\0';
		return (free(s), path);
	}
	i = 0;
	if (find_dollar(s, 0) != -1)
		while (s[i] != '$')
			i++;
	tmp = (char *)ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, s, i + 1);
	end = ft_strjoin(tmp, path);
	if (!end)
		return (free(s), free(tmp), free(path), NULL);
	return (free(s), free(tmp), free(path), end);
}
