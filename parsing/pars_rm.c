/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:51:08 by mfanelli          #+#    #+#             */
/*   Updated: 2025/05/13 16:50:45 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Funzione che filtra la stringa per vedere se ci sono spazi extra tra le
redir e i loro limiter. */
char	*rm_spaces(char *s)
{
	int	i;
	int	x;

	i = -1;
	while (s[++i])
	{
		if (find_char(s, i) > 3 && s[i + 1] == ' ' && werami(s, i, 0, 0) == -1)
		{
			x = 1;
			while (s[i + x] == ' ')
				x++;
			if (find_char(s, (i + x)) != 0 || s[i + x] == '\0')
				return (error_exit(NULL, i, \
				"Syntax Error, unexpected token\n", s));
			s = rewrite(s, i, x - 1);
		}
		if (find_char(s, i) > 3 && s[i + 1] == '\0' && \
		i > 0 && ((find_char(s, i - 1) == 0) || (find_char(s, i - 1) > 3)))
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token\n", s));
	}
	return (s);
}

/* Serve a togliere gli apici, le virgolette e i back-slash inutili */
char	*rm_app(char *s)
{
	int		i;
	int		x;
	int		len;
	char	*new;

	i = -1;
	len = 0;
	while (s[++i])
		if ((werami(s, i, 0, 0) != 0 && s[i] != 92) || \
		(((werami(s, i, 0, 0) == 0) || (s[i] == 92)) && i != 0 && \
		werami(s, i - 1, 0, 0) == 1 && werami(s, i + 1, 0, 0) == 1))
			len++;
	i = -1;
	x = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	while (s[++i])
		if ((werami(s, i, 0, 0) != 0 && s[i] != 92) || \
		(((werami(s, i, 0, 0) == 0) || (s[i] == 92)) && i != 0 && \
		werami(s, i - 1, 0, 0) == 1 && werami(s, i + 1, 0, 0) == 1))
			new[x++] = s[i];
	new[x] = '\0';
	return (free(s), new);
}

/* Serve a togliere i $ nel caso i cui non vadano stampati, es. $"USER" */
char	*rm_dollar(char *s)
{
	int		i;
	int		x;
	char	*tmp;

	i = -1;
	x = 0;
	while (s[++i])
	{
		x++;
		if (rm_dollar_if(s, i) != 0)
			x--;
	}
	tmp = (char *)ft_calloc(x + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	x = 0;
	while (s[++i])
	{
		if (rm_dollar_if(s, i) != 0)
			i++;
		tmp[x++] = s[i];
	}
	tmp[x] = '\0';
	return (free(s), tmp);
}

char	*rm_square(char *str)
{
	char	*end;
	int		i;
	int		x;

	i = -1;
	x = 0;
	end = (char *)ft_calloc(ft_strlen(str) - 1, sizeof(char));
	while (str[++i] != '\0')
	{
		if (i == 0 && str[i] == '[')
			i++;
		else if (str[i] == ']' && str[i + 1] == '\0')
			break ;
		end[x] = str[i];
		x++;
	}
	return (free(str), end);
}
