/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/31 13:23:59 by mfanelli         ###   ########.fr       */
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
	if (s == NULL || !s[index])
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

/* La funzione chiamata da here_glued che divide redirection, heredoc e pipe attaccati */
char *divide(char *s, int y)
{
	int	i;
	int x;
	int	len;
	char *end;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (((((s[i] != ' ' && find_char(s, i) == 0 && werami(s, i) == -1) || \
		((s[i] == 39 || s[i] == 34) && werami(s, i + 1) != 1)) && \
		find_char(s, i + 1) != 0) || (find_char(s, i) == 3 &&  werami(s, i) == -1 && ((s[i + 1] != ' ') || (s[i - 1] != ' ')))) && i <= y)
		// find_char(s, i + 1) != 0) || (find_char(s, i) == 3 && s[i + 1] != ' ') || (find_char(s, i) == 3 && s[i - 1] != ' ')) && i <= y)
			len++;
		len++;
	}
	end = (char *)ft_calloc((len + 1) , sizeof(char));
	if (!end)
		return (NULL);
	i = -1;
	x = 0;
	while (s[++i])
	{
		end[x++] = s[i];
		if (((((s[i] != ' ' && find_char(s, i) == 0 && werami(s, i) == -1) || \
		((s[i] == 39 || s[i] == 34) && werami(s, i + 1) != 1)) && \
		find_char(s, i + 1) != 0) || (find_char(s, i) == 3 &&  werami(s, i) == -1 && ((s[i + 1] != ' ') || (s[i - 1] != ' ')))) && i <= y)
			end[x++] = ' ';
	}
	end[x] = '\0';
	free(s);
	return (end);
}

/* Controlla se ci sono casi di redirection, heredoc o pipe attaccati. Nel caso ci siano li
divide con uno spazio tramite la funzione divide, in modo che poi il custom_split
possa dividerli in nodi seprarati. Inoltre controlla il caso di | o ; a inizio input,
che e' un syntax error*/
char *here_glued(char *s)
{
	int	i;
	int	x;

	i = -1;
	if (s[0] == '|' || s[0] == ';') //gestisce | e ; all'inizio dell'input, che sono syntax error diretti
			return (free(s), NULL); //syntax error
	while (s[++i])
	{
		if (((s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<' && s[i + 3] == '<') || (s[i] == '>' && s[i + 1] == '<' && s[i + 2] == '<')) && werami(s, i) != 1) //gestisce <<<<a, ><<a
			return (free(s), NULL); //syntax error
		if (find_char(s, i) == 0)
			continue ;
		x = i;
		if (s[i - 1] == 39 || s[i - 1] == 34)
		{
			while (werami(s, x) != 0 && s[x] != '\0')
				x++;
		}
		while (s[x] != '\0')
		{
			if (werami(s, x) != 1 && ((s[x] == '>' && s[x + 1] == '<' && s[x + 2] == '<') || (s[x] == '<' && s[x + 2] == '<' && ((s[x + 1] == '|') || (s[x + 1] == ';') || (s[x + 1] == '#') || (ft_isdigit(s[x + 1]) != 0))) || (s[x] == '<' && s[x + 1] == '<' && ((s[x + 2] == '|') || (s[x + 2] == ';') || (s[x + 2] == '#') || (ft_isdigit(s[x + 2]) != 0)))))
				return (free(s), NULL);
			if ((((x != 0 && s[x] != ' ' && s[x] != '>' && \
			werami(s, x) == -1) || (s[x] == 39 || s[x] == 34)) && \
			find_char(s, x + 1) != 0) || (find_char(s, x - 1) == 3 && \
			s[x] != ' ') || (find_char(s, x) == 3))
			{
				s = divide(s, x);
				i = x;
				break ;
			}
			x++;
		}
	}
	return (s);
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
