/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:35 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/29 12:33:13 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_append(char *s, int i, char thing)
{
	int	x;
	int f;

	x = i - 1;
	if (thing == 'a')
		f = '\'';
	else if (thing == 'v')
		f = '"';
	while (s[++x])
		if (s[x] == f)
			return (1);
	return (0);
}

/* Indica se il carattere nella posizione 'index' nella stringa s e'
dentro o fuori gi apici/ virgolette. Se returna 0 s[index] e'
uguale ad un'apice/virgoletta, se returna 1 s[index] e'
negli apici, se returna -1 e' fuori.
Se 's' o 's[index]' sono uguali a NULL returnano -2.*/
int	werami(char *s, int i, int a, int v)
{
	int	x;

	x = -1;
	if (s == NULL || s[i] == '\0')
		return (-2);
	while (s[++x] != '\0')
	{
		if (s[x] == '"' && a == 0 && v == 0)
			v = 1;
		else if (s[x] == '"' && a == 0 && v == 1)
			v = 0;
		if (s[x] == '\'' && a == 0 && v == 0)
			a = 1;
		else if (s[x] == '\'' && a == 1 && v == 0)
			a = 0;
		if (((s[x] == '\'' && v == 0) || (s[x] == '"' && a == 0)) && x == i)
			return (0);
		if (x == i)
			break ;
	}
	if ((a == 1 && v == 0 && check_append(s, i, 'a') != 0) || \
		(v == 1 && a == 0 && check_append(s, i, 'v') != 0))
		return (1);
	return (-1);
}
