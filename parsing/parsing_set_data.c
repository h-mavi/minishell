/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_set_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:42:14 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/02 17:24:59 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	set_data(t_token **head, char *str, int flag)
{
	t_token *node;

	node = (t_token *)ft_calloc(1 ,sizeof(t_token));
	if (!node)
		return ;
    (*node).type = flag;
    (*node).str = str;
	lstadd_back(head, node);
}

void	print_lists(t_token *head)
{
	while (head != NULL)
	{
		if (head->next == NULL && head->prev == NULL)
		{
			printf("\nPrev -> NULL\nType -> %d\nInput -> %s\nNext -> NULL\n\n", \
			head->type, head->str);
			break ;
		}
		else if (head->prev == NULL)
		{
			printf("\nPrev -> NULL\nType -> %d\nInput -> %s\nNext -> %s\n\n", \
			head->type, head->str, (head->next)->str);
			head = head->next;
		}
		else if (head->next == NULL)
		{
			printf("Prev -> %s\nType -> %d\nInput -> %s\nNext -> NULL\n\n", \
			(head->prev)->str, head->type, head->str);
			break ;
		}
		else
		{
			printf("Prev -> %s\nType -> %d\nInput -> %s\nNext -> %s\n\n", \
			(head->prev)->str, head->type, head->str, (head->next)->str);
			head = head->next;
		}
	}
}

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
