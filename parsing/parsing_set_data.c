/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_set_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:42:14 by mfanelli          #+#    #+#             */
/*   Updated: 2025/04/01 09:17:20 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!lst)
		(*lst) = new;
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// void	set_cmd_data(t_token *head, char *str)
// {
// 	t_token *cmd;

// 	cmd = (t_token *)malloc(sizeof(t_token));
// 	if (!cmd)
// 		return ;
//     cmd->type = COMMAND;
//     cmd->str = str; //remove_app(str)
//     cmd -> next = NULL;
// 	// cmd->prev = head; come faccio a dare la prev di ognuno?
// 	lstadd_back(&head, cmd);
// }

// void	set_option_data(t_token *head, char *str)
// {
// 	t_token *opt;

//     check_if_dollar();
//     opt = (t_token *)malloc(sizeof(t_token));
// 	if (!opt)
// 		return ;
//     opt->type = FLAG;
//     opt->str = str; //remove_app(str)
//     opt-> next = NULL;
// 	// opt->prev = head; come faccio a dare la prev di ognuno?
// 	lstadd_back(&head, opt);
// }

// void	set_pipe_data(t_token *head, char *str)
// {
// 	t_token *pipe;

// 	pipe = (t_token *)malloc(sizeof(t_token));
// 	if (!pipe)
// 		return ;
// 	pipe->type = PIPE;
// 	pipe->str = str; //remove_app(str)
//     pipe->next = NULL;
// 	// pipe->prev = head; come faccio a dare la prev di ognuno?
// 	lstadd_back(&head, pipe);
// }

// void	set_redir_data(t_token *head, char *str)
// {
// 	t_token *redir;

// 	if (!is_it_right(&str) != 1)
// 	{
// 		printf("Syntax error, type redir\n");
// 		return ;
// 	}
// 	redir = (t_token *)malloc(sizeof(t_token));
// 	if (!redir)
// 		return ;
// 	redir->type = redir;
// 	redir->str = str;
//     redir->next = NULL;
// 	// redir->prev = head; come faccio a dare la prev di ognuno?
// 	lstadd_back(&head, redir);
// }

void	print_lists(t_token *head)
{
	printf("---------------------\n");
	while (head != NULL)
	{
		printf("Type -> %d\nInput -> %s\n", head->type, head->str);
		head = head->next;
	}
	printf("---------------------\n");
}