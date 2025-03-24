/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/24 11:31:03 by mfanelli         ###   ########.fr       */
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
