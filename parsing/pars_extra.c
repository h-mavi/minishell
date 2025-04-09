/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:40:15 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/09 16:35:58 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Chiamata da espand, serve per sistemare la stringa del limiter. */
char	*set_str(char *s)
{
	char	*tmp;

	if (find_dollar(s, 0) != -1)
		tmp = ft_strjoin(ft_strchr(s, '$') + 1, "=");
	else
		tmp = ft_strjoin(s, "=");
	return (tmp);
}

/*Chiamata da espand, serve per settare il path per espandere la variabile.*/
char	*set_path(char *tmp, char **env)
{
	int		i;
	char	*path;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
		{
			path = ft_strdup(env[i] + ft_strlen(tmp));
			break ;
		}
	}
	free(tmp);
	return (path);
}

/* Chiamata len_arr_split, aiuta con la conta delle parole gestendo apici
e virgolette. */
int	len_arr_utils(char *s, int *i, int *x, int app)
{
	if (s[*x] == app)
	{
		if (*x == 0 && s[*x] != ' ')
			(*i)++;
		(*x)++;
		while (s[*x] != app && s[*x] != '\0')
			(*x)++;
		if (s[*x] == '\0')
			return (-1);
	}
	return (1);
}

/* Chiamata da fill nel custom_split, conta la lunghezza di una parola,
gestendo virgolette ed apici */
int	count_len_wrd(char *s, int *y, int conta)
{
	if (s[*y] == 34 || s[*y] == 39)
	{
		while (s[*y] != '\0' && ((werami(s, *y) != -1) || \
		(werami(s, *y) == -1 && s[*y] != ' ')))
		{
			(*y)++;
			conta++;
		}
	}
	else
	{
		while (s[*y] != '\0' && s[(*y)++] != ' ')
		{
			conta++;
			if (s[*y] == 34 || s[*y] == 39)
			{
				while (werami(s, *y) != -1 && werami(s, *y) != -2)
				{
					(*y)++;
					conta++;
				}
			}
		}
	}
	return (conta);
}

char	*smells_goog(char *s, int *i, char **env)
{
	while (s[++(*i)] != '"')
	{
		if (s[*i] == '$' && s[(*i) + 1] == '$')
			*i += 2;
		if ((s[*i] == '$' && werami(s, *i) == 1 && \
			((ft_isalpha(s[(*i) + 1]) != 0) || (s[(*i) + 1] == '_'))))
			s = esp_special_case(s, env, *i);
	}
	return (s);
}
