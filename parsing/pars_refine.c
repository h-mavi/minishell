/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_refine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:02:23 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/01 14:02:26 by mfanelli         ###   ########.fr       */
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
			y++;
			dest[y] = '\0';
			break ;
		}
	}
	free(orig);
	return (dest);
}

/* Funzione che filtra la stringa per vedere se ci sono spazi extra tra le
redir e i loro limiter. */
char *rm_spaces(char *s)
{
	int	i;
	int	x;

	i = -1;
	while (s[++i])
	{
		if (find_char(s, i) > 3 && s[i + 1] == ' ')
		{
			x = 1;
			while (s[i + x] == ' ')
				x++;
			if (find_char(s, (i + x)) != 0 || s[i + x] == '\0')
				return (NULL); //syntax error
			s = rewrite(s, i, x - 1);
		}
		if (find_char(s, i) > 3 && s[i + 1] == '\0')
			return (NULL);
	}
	return (s);
}

/* La funzione chiamata da here_glued che divide redirection, heredoc e pipe attaccati */
char *divide(char *s, int y)
{
	int	i;
	int x;
	int	len;
	char *end;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (((((s[i] != ' ' && find_char(s, i) == 0 && werami(s, i) == -1) || \
		((s[i] == 39 || s[i] == 34) && werami(s, i + 1) != 1)) && \
		find_char(s, i + 1) != 0) || (find_char(s, i) == 3 && \
		werami(s, i) == -1 && s[i + 1] != '|' && s[i - 1] != '|' && \
		((s[i + 1] != ' ') || (s[i - 1] != ' ')))) && i <= y)
			len++;
		len++;
	}
	end = (char *)ft_calloc((len + 1) , sizeof(char));
	if (!end)
		return (NULL);
	i = -1;
	x = 0;
	while (s[++i])
	{
		end[x++] = s[i];
		if (((((s[i] != ' ' && find_char(s, i) == 0 && werami(s, i) == -1) || \
		((s[i] == 39 || s[i] == 34) && werami(s, i + 1) != 1)) && \
		find_char(s, i + 1) != 0) || (find_char(s, i) == 3 && \
		werami(s, i) == -1 && s[i + 1] != '|' && s[i - 1] != '|' && \
		((s[i + 1] != ' ') || (s[i - 1] != ' ')))) && i <= y)
			end[x++] = ' ';
	}
	end[x] = '\0';
	free(s);
	return (end);
}

/* Controlla se ci sono casi di redirection, heredoc o pipe attaccati. Nel caso ci siano li
divide con uno spazio tramite la funzione divide, in modo che poi il custom_split
possa dividerli in nodi seprarati. Inoltre controlla il caso di | o ; a inizio input,
che e' un syntax error*/
char *here_glued(char *s)
{
	int	i;
	int	x;

	i = -1;
	if (s[0] == '|' || s[0] == ';') //gestisce | e ; all'inizio dell'input, che sono syntax error diretti
			return (free(s), NULL); //syntax error
	while (s[++i])
	{
		if (find_char(s, i) == 0)
			continue ;
		if (werami(s, i) == -1 && ft_isdigit(s[i + 1]) != 0 && \
		((s[i] == '<' && s[i + 2] == '<') || (s[i] == '>' && s[i + 2] == '>')))
			return (free(s), NULL);
		x = i;
		if (s[i - 1] == 39 || s[i - 1] == 34)
		{
			while (werami(s, x) != 0 && s[x] != '\0')
				x++;
		}
		while (s[x] != '\0')
		{
			if ((((x != 0 && s[x] != ' ' && s[x] != '>' && \
			werami(s, x) == -1) || (s[x] == 39 || s[x] == 34)) && \
			find_char(s, x + 1) != 0) || (find_char(s, x - 1) == 3 && \
			s[x] != ' ') || (find_char(s, x) == 3))
			{
				s = divide(s, x);
				i = x;
				break ;
			}
			x++;
		}
	}
	return (s);
}

char	*espand(char *s, char **env)
{
	int		i;
	char	*path;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], s + 1, ft_strlen(s) - 1) == 0)
		{
			path = ft_strdup(env[i] + ft_strlen(s));
			break ;
		}
	}
	free(s);
	if (!path)
		return (NULL);
	return (path);
}
