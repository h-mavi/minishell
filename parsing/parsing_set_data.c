/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_set_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:42:14 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/01 15:34:53 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*tmp;

// 	if (!new)
// 		return ;
// 	if (!lst)
// 		(*lst) = new;
// 	tmp = *lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

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

void	set_cmd_data(t_token **head, char *str)
{
	t_token *cmd;

	cmd = (t_token *)ft_calloc(1 ,sizeof(t_token));
	if (!cmd)
		return ;
    (*cmd).type = COMMAND;
    (*cmd).str = str;
	// cmd->prev = head; come faccio a dare la prev di ognuno?
	lstadd_back(head, cmd);
}

void	set_option_data(t_token **head, char *str)
{
	t_token *opt;

    opt = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!opt)
		return ;
    (*opt).type = FLAG;
    (*opt).str = str;
	// opt->prev = head; come faccio a dare la prev di ognuno?
	lstadd_back(head, opt);
}

void	set_pipe_data(t_token **head, char *str)
{
	t_token *pipe;

	pipe = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!pipe)
		return ;
	(*pipe).type = PIPE;
	(*pipe).str = str;
	// pipe->prev = head; come faccio a dare la prev di ognuno?
	lstadd_back(head, pipe);
}

void	set_redir_data(t_token **head, char *str)
{
	t_token *redir;

	redir = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!redir)
		return ;
	(*redir).type = find_char(str, 0);
	(*redir).str = str;
	// redir->prev = head; come faccio a dare la prev di ognuno?
	lstadd_back(head, redir);
}

void	print_lists(t_token *head)
{
	printf("---------------------\n");
	while (head != NULL)
	{
		printf("Type -> %d\nInput -> %s\nNext -> %s\n---------------------\n", \
		head->type, head->str, (head->next)->str);
		head = head->next;
		if (head->next == NULL)
		{
			printf("Type -> %d\nInput -> %s\nNext -> NULL\n---------------------\n", \
				head->type, head->str);
			break ;
		}
	}
}