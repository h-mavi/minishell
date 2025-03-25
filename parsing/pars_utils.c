/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/25 12:02:51 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Serve a liberare la memoria di una matrice
void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/* Indica se il carattere nella posizione 'index' nella stringa s e' dentro o fuori
gi apici/ virgolette, le quali devono essere specificate usando a. Se returna 0
s[index] e' uguale ad a, se returna 1 s[index] e' negli apici, se returna -1 e' fuori.
Se 's' o 's[index]' sono uguali a NULL returnano -2.*/
int werami(const char *s, int index, char a)
{
	int	x;
	int	app;

	x = -1;
	app = 0;
	if (s == NULL || !s[index])
		return (-2);
	while (s[++x] != '\0')
	{
	if (s[x] == a && app == 0)
		app = 1;
	else if (s[x] == a && app == 1)
		app = 0;
	if (s[x] == a && x == index)
		return (0);
	if (x == index && app == 1)
		return (1);
	}
	return (-1);
}

char *divide(char *s)
{
	int	i;
	int x;
	int	len;
	char *end;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] == '<' && s[i - 1] != '<' && i != 0)
			len++;
		len++;
	}
	end = (char *)ft_calloc(len , sizeof(char));
	i = -1;
	x = 0;
	while (s[++i])
	{
		end[x++] = s[i];
		if (s[i] == '<' && s[i - 1] != '<' && i != 0)
			end[x++] = ' ';
	}
	free(s);
	return (end);
}

char *here_glued(char *s)
{
	int	i;
	int	x;

	i = -1;
	if (((s[0] == '|') || (s[0] == '>') || (s[0] == ';')) && s[1] == '<' && s[2] == '<') //gestisce |<<a, ><<a, ;<<a (che sono syntax error solo se sono all'inizio dell'input)
			return (NULL); //syntax error
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<' && s[i + 3] == '<') //gestisce <<<<a
			return (NULL); //syntax error
		if (s[i] != '<')
			continue ;
		if (s[i + 1] == '<')
		{
			x = i;
			while ((s[x] != ' ' && (s[x] != '<' && s[x - 1] == '<') && s[x] != '\0') || (x == i))
			{
				x++;
				if (((s[x] == '|') || (s[x] == '>') || (s[x] == ';') || (s[x] == '#') || (ft_isdigit(s[x]) != 0)) && s[i] == '<' && s[x + 1] == '<')
					return (NULL);
			}
			if (s[x] == '<')
				s = divide(s);
		}
	}
	return (s);
}
