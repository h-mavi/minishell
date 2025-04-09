/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:21 by mbiagi            #+#    #+#             */
/*   Updated: 2025/04/09 15:26:20 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Essenziale per riassemblare la stringa per un caso speciale
di espansione */
char	*reassemble(char *first, char *espan, char *after, int len_cmd)
{
	char	*end;
	int		i;
	int		x;

	end = (char *)ft_calloc((ft_strlen(first) - len_cmd + ft_strlen(espan)) \
	+ 1, sizeof(char));
	i = 0;
	x = -1;
	while (++x < find_dollar(first, ft_strlen(first) - len_cmd - \
	ft_strlen(after)))
		end[i++] = first[x];
	x = -1;
	while (espan[++x] != '\0')
		end[i++] = espan[x];
	x = -1;
	while (after[++x] != '\0')
		end[i++] = after[x];
	end[i] = '\0';
	free(first);
	return (end);
}

/* Controlla errori filtrando la lista. */
int	check_error_lst(t_token *head)
{
	t_token	*prima;
	t_token	*dopo;

	prima = head;
	dopo = prima->next;
	if (prima->type == PIPE || prima->str[0] == ';')
		return (error_exit(head, -1, \
		"Syntax Error, unexpected token at the start of input\n", NULL), 0);
	while (dopo != NULL)
	{
		if (dopo->type == PIPE && prima->type == PIPE)
			return (error_exit(head, prima->id, \
			"Syntax Error, unexpected token '|'\n", NULL), 0);
		prima = dopo;
		dopo = prima->next;
	}
	if (prima->type == PIPE)
		return (error_exit(head, -1, \
		"Syntax Error, unexpected token '|' at the end of input\n", NULL), 0);
	return (1);
}

/* Serve a liberare una lista. */
void	free_lst(t_token *head)
{
	t_token	*tmp;

	while (head->next != NULL)
	{
		free((char *)(*head).str);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free((char *)(*head).str);
	free(head);
}

/* Funzione da chiamare in caso di errore! Libera la lista head e
la stringa input e controlla se ci sono heredoc tramite syn.
Se syn != -1 allora gli heredoc sono da aprire (in caso
di errore di sintassi). */
char	*error_exit(t_token *head, int syn, char *str, char *input)
{
	printf("%s", str);
	if (syn != -1 && head != NULL && input == NULL)
		ft_openhd_ls(head, syn);
	else if (syn != -1 && head == NULL && input != NULL)
		ft_openhd_str(input, syn);
	if (input != NULL)
		free(input);
	if (head != NULL)
		free_lst(head);
	return (NULL);
}
