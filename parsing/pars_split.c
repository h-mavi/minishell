/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:52 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/07 12:42:21 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* returna il numero di elementi presenti nell'input */
int	len_arr_split(char *arr)
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

void	frite(char *dest, int start, int len, char *s)
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

char	**fill(char **dest, char *s, int len_arr)
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
		if (s[y] == 34 || s[y] == 39)
		{
			while (s[y] != '\0' && ((werami(s, y) != -1) || \
			(werami(s, y) == -1 && s[y] != ' ')))
			{
				y++;
				conta++;
			}
		}
		else
			while (s[y] != '\0' && s[y++] != ' ')
			{
				conta++;
				if (s[y] == 34 || s[y] == 39)
					while (werami(s, y) != -1 && werami(s, y) != -2)
					{
						y++;
						conta++;
					}
			}
		dest[x] = (char *) malloc(sizeof(char) * (conta + 1));
		if (dest[x] == NULL)
			return (NULL);
		frite(dest[x++], i, conta, s);
		if (s[i] == 34 || s[i] == 39)
			while (s[y] != '\0' && ((werami(s, i) != -1) || \
			(werami(s, i) == -1 && s[i] != ' ')))
				i++;
		else
			while (s[y] != '\0' && s[i++] != ' ')
				if (s[i] == 34 || s[i] == 39)
					while (werami(s, i) != -1  && werami(s, y) != -2)
						i++;
	}
	dest[x] = NULL;
	return (dest);
}

char	**custom_split(char *s)
{
	int		x;
	int		len_arr;
	char	**dest;

	x = 0;
	s = rm_spaces(s);
	if (!s)
		return (NULL);
	s = here_glued(s);
	if (!s || check_error(s) == 0)
		return (NULL);
	len_arr = len_arr_split(s);
	if (len_arr == -1)
		return (error_exit(NULL, NULL, 0, "Syntax Error, odd number of ' or \"\n"), NULL); //numero dispari di virgolette e apici, no here_doc
	dest = (char **) malloc(sizeof(char *) * (len_arr + 1));
	if (!dest)
		return (error_exit(NULL, NULL, 0, "Failed Allocation\n"), NULL); // allocazione fallita, no here_doc
	if (!fill(dest, s, len_arr))
		return (free(s), error_exit(NULL, dest, 0, "Failed Allocation\n"), NULL); //allocazione fallita, no here_doc
	return (free(s), dest);
}

