/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/02 12:40:45 by mfanelli         ###   ########.fr       */
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

/* Indica se il carattere nella posizione 'index' nella stringa s e' dentro o fuori
gi apici/ virgolette. Se returna 0 s[index] e' uguale ad un'apice/virgoletta,
se returna 1 s[index] e' negli apici, se returna -1 e' fuori.
Se 's' o 's[index]' sono uguali a NULL returnano -2.*/
int werami(const char *s, int index)
{
	int	x;
	int	app;
	int	virg;

	x = -1;
	app = 0;
	virg = 0;
	if (s == NULL || s[index] == '\0')
		return (-2);
	while (s[++x] != '\0')
	{
	if (s[x] == 34 && app == 0 && virg == 0)
		virg = 1;
	else if (s[x] == 34 && app == 0 && virg == 1)
		virg = 0;
	if (s[x] == 39 && app == 0 && virg == 0)
		app = 1;
	else if (s[x] == 39 && app == 1 && virg == 0)
		app = 0;
	if (((s[x] == 39 && virg == 0) || (s[x] == 34 && app == 0)) && x == index)
		return (0);
	if ((x == index && app == 1) || (x == index && virg == 1))
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
int find_char(char *s, int i)
{
		if (s[i] == '|')
			return (3);
		if (s[i] == '<' && s[i + 1] != '<')
			return (4);
		if (s[i] == '>'&& s[i + 1] != '>')
			return (5);
		if (s[i] == '>' && s[i + 1] == '>')
			return (6);
		if (s[i] == '<' && s[i + 1] == '<')
			return (7);
	return (0);
}

/* Controlla i seguenti errori: 
|||, <>>a, ><a, >>>a, <<<<a,
<|<a, <;<a, <#<a, >|>a, >;>a, >#>a,
>>|a, >>;a, >>#a, <<|a, <<;a, <<#a,
>;a, >#a, <|a, <;a, <#a, */
int	check_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] == '|' && werami(s, i) == -1)
			return (0);
		if (s[i] == '<' && werami(s, i) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') \
			|| (s[i + 1] == '<' && s[i + 2] == '<' && s[i + 3] == '<') || \
			(s[i + 1] == '>' && s[i + 2] == '>')))
			return (0);
		if (s[i] == '>' && werami(s, i) == -1 && \
			((s[i + 1] == '|') || (s[i + 1] == ';') || (s[i + 1] == '#') \
			|| (s[i + 1] == '<') || (s[i + 1] == '>' && s[i + 2] == '>')))
			return (0);
	}
	return (1);
}




//errori da gestire= pipe come ultimo input e' errore, || deve dare errore anche come |          |
//il primo caso di apre una quote, noi semplice erroe, l'altro non fa un cazzo.
//li gestisco una volta che faccio i nodi etc