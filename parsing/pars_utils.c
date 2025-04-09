/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/09 10:21:55 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Serve a liberare la memoria di una matrice */
void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/* Indica se il carattere nella posizione 'index' nella stringa s e'
dentro o fuori gi apici/ virgolette. Se returna 0 s[index] e'
uguale ad un'apice/virgoletta, se returna 1 s[index] e'
negli apici, se returna -1 e' fuori.
Se 's' o 's[index]' sono uguali a NULL returnano -2.*/
int	werami(char *s, int i)
{
	int	x;
	int	a;
	int	v;

	x = -1;
	a = 0;
	v = 0;
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
		if ((x == i && a == 1) || (x == i && v == 1))
			return (1);
	}
	return (-1);
}

/* Riconosce se il carattere s[i] e' un carattere speciale:
se returna 3 s[i] == |;
se returna 4 s[i] == <;
se returna 5 s[i] == >;
se returna 6 s[i] && s[i + 1] == >>;
se returna 7 s[i] && s[i + 1] == <<;*/
int	find_char(char *s, int i)
{
	if (s[i] == '|')
		return (3);
	if (s[i] == '<' && s[i + 1] != '<')
		return (4);
	if (s[i] == '>' && s[i + 1] != '>')
		return (5);
	if (s[i] == '>' && s[i + 1] == '>')
		return (6);
	if (s[i] == '<' && s[i + 1] == '<')
		return (7);
	return (0);
}

/* Cerca un carattere '$' nella stringa s partendo
dall'indice i*/
int	find_dollar(char *s, int i)
{
	int	x;

	x = i;
	while (s[x])
	{
		if (s[x] == '$')
			return (x);
		x++;
	}
	return (-1);
}

/* Controlla i seguenti errori: 
|||, <>>a, ><a, >>>a, <<<<a,
<|<a, <;<a, <#<a, <1<a, 
>|>a, >;>a, >#>a, >1>a,
>>|a, >>;a, >>#a, <<|a, <<;a, <<#a,
>;a, >#a, <|a, <;a, <#a, */
int	check_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] == '|' && werami(s, i) == -1)
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token '|'\n", s), 0);
		if (s[i] == '<' && werami(s, i) == -1 && ((s[i + 1] == '|') || \
			(s[i + 1] == ';') || (s[i + 1] == '#') || (s[i + 1] == '<' && \
			((s[i + 2] == '<') || (s[i + 2] == '>'))) || (s[i + 1] == '>') || \
			(s[i + 1] == '>' && s[i + 2] == '>') || \
			(ft_isdigit(s[i + 1]) != 0 && find_char(s, i + 2) != 3 && \
			find_char(s, i + 2) != 0)))
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token\n", s), 0);
		if (s[i] == '>' && werami(s, i) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') || \
			(s[i + 1] == '<') || (s[i + 1] == '>' && s[i + 2] == '>') || \
			(ft_isdigit(s[i + 1]) != 0 && find_char(s, i + 2) != 3 && \
			find_char(s, i + 2) != 0)))
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token\n", s), 0);
	}
	return (1);
}
