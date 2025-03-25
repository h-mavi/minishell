/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:52 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/25 11:49:15 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//return il numero di elementi presenti nell'input
static int	len_arr_split(char const *arr)
{
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (arr[++x] != '\0')
	{
		if (arr[x] == '"')
		{
			if (x == 0 && arr[x] != ' ')
				i++;
			x++;
			while (arr[x] != '"' && arr[x] != '\0')
				x++;
			if (arr[x] == '\0')
				return (-1); //ERROR
		}
		else if (arr[x] == 39)
		{
			if (x == 0 && arr[x] != ' ')
				i++;
			x++;
			while (arr[x] != 39 && arr[x] != '\0')
				x++;
			if (arr[x] == '\0')
				return (-1); //ERROR
		}
		if ((arr[x] == ' ' && arr[x + 1] != ' ' && arr[x + 1] != '\0') || \
		(x == 0 && arr[x] != ' '))
			i++;
	}
	return (i);
}

static void	frite(char *dest, int start, int len, char const *s)
{
	int	i;

	i = 0;
	if (s[start + len - 1])
		len--;
	while (i + start < start + len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
}

static char	**fill(char **dest, char const *s, int len_arr)
{
	int	i;
	int	x;
	int	y;
	int	conta;

	i = 0;
	x = 0;
	y = 0;
	while (x < len_arr)
	{
		conta = 1;
		while (s[i] == 32)
			i++;
		y = i;
		if (s[y] == '"')
		{
			while ((s[y] != '\0' && werami(s, y, '"') != -1) || \
			(s[y] != '\0' && werami(s, y, '"') == -1 && s[y] != ' '))
			{
				y++;
				conta++;
			}
		}
		else if (s[y] == 39)
		{
			while ((s[y] != '\0' && werami(s, y, 39) != -1) || \
			(s[y] != '\0' && werami(s, y, 39) == -1 && s[y] != ' '))
			{
				y++;
				conta++;
			}
		}
		else
			while (s[y] != '\0' && s[y++] != ' ')
			{
				if (s[y] == '"')
					while (werami(s, y++, '"') != -1)
						conta++;
				if (s[y] == 39)
					while (werami(s, y++, 39) != -1)
							conta++;
				conta++;
			}
		dest[x] = (char *) malloc(sizeof(char) * (conta + 1));
		if (dest[x] == NULL)
			return (NULL);
		frite(dest[x++], i, conta, s);
		if (s[i] == '"')
			while ((s[y] != '\0' && werami(s, i, '"') != -1) || \
			(s[y] != '\0' && werami(s, i, '"') == -1 && s[i] != ' '))
				i++;
		else if (s[i] == 39)
			while ((s[y] != '\0' && werami(s, i, 39) != -1) || \
				(s[y] != '\0' && werami(s, i, 39) == -1 && s[i] != ' '))
					i++;
		else
			while (s[y] != '\0' && s[i++] != ' ')
			{
				if (s[i] == '"')
					while (werami(s, i, '"') != -1)
						i++;
			}
	}
	dest[x] = NULL;
	return (dest);
}

char	**custom_split(char const *s)
{
	int		x;
	int		len_arr;
	char	**dest;

	x = 0;
	len_arr = len_arr_split(s);
	if (len_arr == -1)
		return (NULL);
	//controllo sugli heredoc ataccati
	s = here_glued((char *)s);
	if (!s)
		return (NULL);
	dest = (char **) malloc(sizeof(char *) * (len_arr + 1));
	if (!dest)
		return (NULL);
	if (!fill(dest, s, len_arr))
	{
		while (x++ <= len_arr)
			free(dest[x]);
		return (NULL);
	}
	return (dest);
}
