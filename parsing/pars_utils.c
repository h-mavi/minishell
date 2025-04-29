/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/29 12:33:08 by mfanelli         ###   ########.fr       */
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
	if (s[i] == '<' && s[i + 1] == '<' && \
		s[i + 2] != '<' && werami(s, i + 2, 0, 0) != 0)
		return (7);
	if (s[i] == '<' && s[i + 1] == '<' && \
		s[i + 2] != '<' && werami(s, i + 2, 0, 0) == 0)
		return (8);
	return (0);
}

/* Cerca un carattere '$' valido nella stringa s partendo
dall'indice i. Con valido si intende un $ che e' poi seguito
da una variabile da espandere.*/
int	find_dollar(char *s, int i)
{
	int	x;

	x = i;
	while (s[x])
	{
		if (s[x] == '$' && s[x + 1] != '$' && \
			((ft_isalpha(s[x + 1]) != 0) || (s[x + 1] == '_')))
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
>;a, >#a, <|a, <;a, <#a */
int	check_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] == '|' && werami(s, i, 0, 0) == -1)
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token '|'\n", s), 0);
		if (s[i] == '<' && werami(s, i, 0, 0) == -1 && ((s[i + 1] == '|') || \
			(s[i + 1] == ';') || (s[i + 1] == '#') || (s[i + 1] == '<' && \
			((s[i + 2] == '<') || (s[i + 2] == '>'))) || (s[i + 1] == '>') || \
			(s[i + 1] == '>' && s[i + 2] == '>') || \
			(ft_isdigit(s[i + 1]) != 0 && find_char(s, i + 2) != 3 && \
			find_char(s, i + 2) != 0)))
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token\n", s), 0);
		if (s[i] == '>' && werami(s, i, 0, 0) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') || \
			(s[i + 1] == '<') || (s[i + 1] == '>' && s[i + 2] == '>') || \
			(ft_isdigit(s[i + 1]) != 0 && find_char(s, i + 2) != 3 && \
			find_char(s, i + 2) != 0)))
			return (error_exit(NULL, i, \
			"Syntax Error, unexpected token\n", s), 0);
	}
	return (1);
}
