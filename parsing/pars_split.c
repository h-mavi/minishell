/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:52 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/20 10:26:16 by mfanelli         ###   ########.fr       */
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
			x++;
			while (arr[x] != '"' && arr[x] != '\0')
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

static void	frite(char *dest, int i, int conta, char const *s)
{
	int	g;

	g = 0;
	while (g + i < i + conta)
	{
		dest[g] = s[i + (g)];
		g++;
	}
	dest[g] = '\0';
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
		while (s[i] == ' ')
			i++;
		y = i;
		while ((s[y] != '\0' && s[y] != ' ') || (s[i] == '"' && s[y] != '"' && s[y] != '\0'))
		{
			y++;
			conta++;
		}
		dest[x] = (char *) malloc(sizeof(char) * (conta + 1));
		if (dest[x] == NULL)
			return (NULL);
		frite(dest[x++], i, conta - 1, s);
		conta = i;
		i++;
		while ((s[y] != '\0' && s[i] != ' ') || (s[y] != '\0' && s[conta] == '"' && s[i] != '"'))
			i++;
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
	dest = (char **) malloc(sizeof(char *) * (len_arr + 1));
	if (dest == NULL)
		return (NULL);
	if (fill(dest, s, len_arr) == NULL)
	{
		while (x ++ <= len_arr)
			free(dest[x]);
		return (NULL);
	}
	return (dest);
}