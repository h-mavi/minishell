/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:08:14 by mfanelli          #+#    #+#             */
/*   Updated: 2025/05/05 16:25:30 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	test(int sig)
{
	if (sig == SIGQUIT)
	{
		write(0, "\b\b  \b\b", 6);
	}
	if (sig == SIGINT)
	{
		g_sigal = 1;
		exit_code(130);
		close(0);
	}
}

/* Filtra la lista head fino al nodo 'where' 
per trovare gli heredoc da aprire */
static void	ft_openhd_ls(t_token *head, int where)
{
	signal(SIGQUIT, test);
	while (head->id < where)
	{
		if ((head->type == HEREDOC || head->type == HEREDOC_2) && \
		g_sigal == 0)
			here_doc(head->str);
		head = head->next;
	}
}

/* Filtra la stringa str fino all'indice 'where'
per trovare gli heredoc da aprire */
static void	ft_openhd_str(char *str, int where, int i)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	signal(SIGQUIT, test);
	if ((size_t)where == ft_strlen(str) - 1)
		if (find_char(str, where - 1) != 0 && where > 0)
			where -= 1;
	while (str[++i] && i < where)
	{
		if ((find_char(str, i) == HEREDOC || find_char(str, i) == HEREDOC_2) \
		&& g_sigal == 0)
		{
			x = i + 2;
			while (str[x] != ' ' && find_char(str, x) == 0)
				x++;
			if (x > where)
				continue ;
			tmp = ft_substr(str, i, x - i);
			if (find_char(str, i) == HEREDOC_2)
				tmp = rm_app(tmp);
			here_doc(tmp);
			free(tmp);
		}
	}
}

/* Funzione da chiamare in caso di errore! Libera la lista head e
la stringa input e controlla se ci sono heredoc tramite syn.
Se syn != -1 allora gli heredoc sono da aprire (in caso
di errore di sintassi). */
char	*error_exit(t_token *head, int syn, char *str, char *input)
{
	printf("%s", str);
	if (syn != -1)
		exit_code(2);
	if (syn != -1 && head != NULL && input == NULL)
		ft_openhd_ls(head, syn);
	else if (syn != -1 && head == NULL && input != NULL)
		ft_openhd_str(input, syn, -1);
	if (input != NULL)
		free(input);
	if (head != NULL)
		free_lst(head);
	return (NULL);
}
