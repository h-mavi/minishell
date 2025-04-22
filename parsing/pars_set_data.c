/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_set_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:42:14 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/22 10:49:55 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Funzione che aggiunge il nodo new infondo alla lista di tipo t_token lst */
void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ex;

	ex = NULL;
	if (!new || !lst)
		return ;
	if (*lst && lst[0])
	{
		ex = *lst;
		while (ex->next != NULL)
			ex = ex->next;
		ex->next = new;
	}
	else
		*lst = new;
	return ;
}

/* Setta i dati della lista di tipo t_token */
void	set_data(t_token **head, char **str, int flag, int id)
{
	t_token	*node;

	node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!node)
		return ;
	*str = rm_app(*str);
	(*node).type = flag;
	if (flag == REDIR_1 || flag == REDIR_2)
		(*node).str = ft_strdup(*str + 1);
	else if (flag == REDIR_3 || flag == HEREDOC)
		(*node).str = ft_strdup(*str + 2);
	else
		(*node).str = ft_strdup(*str);
	(*node).id = id + 1;
	lstadd_back(head, node);
}

/* Printa la lista compilata. Utile solo per il debugging */
void	print_lists(t_token *head)
{
	while (head != NULL)
	{
		if (head->next == NULL && head->prev == NULL)
		{
			printf("\nID -> %d\nPrev -> NULL\nType -> %d\nInput -> %s\nNext -> NULL\n\n", \
			head->id, head->type, head->str);
			break ;
		}
		else if (head->prev == NULL)
		{
			printf("\nID -> %d\nPrev -> NULL\nType -> %d\nInput -> %s\nNext -> %s\n\n", \
			head->id, head->type, head->str, (head->next)->str);
			head = head->next;
		}
		else if (head->next == NULL)
		{
			printf("ID -> %d\nPrev -> %s\nType -> %d\nInput -> %s\nNext -> NULL\n\n", \
			head->id, (head->prev)->str, head->type, head->str);
			break ;
		}
		else
		{
			printf("ID -> %d\nPrev -> %s\nType -> %d\nInput -> %s\nNext -> %s\n\n", \
			head->id, (head->prev)->str, head->type, head->str, (head->next)->str);
			head = head->next;
		}
	}
}

/* Setta gli indirizzi dei nodi precedenti per ogni nodo della lista */
void	set_prev(t_token **head)
{
	t_token	*prima;
	t_token	*corr;

	prima = *head;
	corr = prima->next;
	prima->prev = NULL;
	while (corr != NULL)
	{
		corr->prev = prima;
		prima = corr;
		corr = corr->next;
	}
	return ;
}
