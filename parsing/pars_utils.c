/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:14:37 by mfanelli          #+#    #+#             */
/*   Updated: 2025/03/24 12:12:36 by mfanelli         ###   ########.fr       */
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

/* Controlla il numero di virgolette e apici e si assicura che non siano dispairi.
In caso di successo returna 1, senno' 0.*/
int	check_app(char *str)
{
	int	i;
	int	virg;
	int	app;

	i = -1;
	app = 0;
	virg = 0;
	while (str[++i])
	{
		if (str[i] == 34 && app % 2 == 0)
			virg++;
		if (str[i] == 39 && virg % 2 == 0)
			app++;
	}
	if ((virg % 2 != 0 && app % 2 != 0) || (virg % 2 != 0) || (app % 2 != 0))
		return (0);
	return (1);
}

//capire come gestire misto ' e " con lo split custom