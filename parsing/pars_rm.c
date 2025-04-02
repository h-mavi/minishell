/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:51:08 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/02 12:53:12 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		s[i] == 92) && i != 0 && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			len++;
	i = -1;
	x = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	while (s[++i])
		if ((werami(s, i) != 0 && s[i] != 92) || ((werami(s, i) == 0 || \
		s[i] == 92) && i != 0 && werami(s, i - 1) == 1 && werami(s, i + 1) == 1))
			new[x++] = s[i];
	new[x] = '\0';
	return (free(s), new);
}

/* Serve a togliere i $ nel caso i cui non vadano stampati, es. $"USER" */
char *rm_dollar(char *s)
{
	int		i;
	int		x;
	char	*tmp;

	i = -1;
	x = 0;
	while (s[++i])
		if (s[i] != '$')
			x++;
	tmp = (char *)ft_calloc(x + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	x = 0;
	while (s[++i])
		if (s[i] != '$')
			tmp[x++] = s[i];
	tmp[x] = '\0';
	return (free(s), tmp);
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
